#include <EEPROM.h>

#include "Project-Orgel_menu.h"
// default CPP main file for sketch
#include <PlatformDetermination.h>
#include <TaskManagerIO.h>

#include "ThemeProjOrgel.h"
#include "HomepageProjOrgel.h"

#include <TMCStepper.h>
#include <INA226.h>

#define DRIVER_SERIAL Serial2 // TMC2209 Serial Port
#define DRIVER_ADDRESS 0b00   // Serial Address
#define R_SENSE 0.11f         // Match to your driver <- ???
#define ENABLE_Pin 33         // Enable Pin
#define DIAG_Pin 19           // Diag Pin

// 电机内部输出轴旋转一周步数
// const int STEPS_PER_ROTOR_REV = 194; // Nidec 25GBC12 一圈194*八分之一微步
const int STEPS_PER_ROTOR_REV = 1600; // 42电机 一圈1600*八分之一微步
// 输出轴减速比
// const float GEAR_REDUCTION = 12.0; // Nidec 25GBC12 输出轴减速比1:12
const float GEAR_REDUCTION = 1.0; // 42电机 输出轴直出
// 八音盒减速比
// const float ORGEL_REDUCTION = 0.69; // 29齿八音盒齿轮:42齿电机齿轮
const float ORGEL_REDUCTION = 0.48; // 29齿八音盒齿轮:60齿电机齿轮
// 八音盒齿轮周拍
const float ORGEL_BPM_PER_ROUND = 4.516; // 齿轮周长约1.15picm,纸带一拍0.8cm,故八音盒齿轮旋转一周约4.516拍
// 获得BPM计算常数
const float BPM_CALC_CONST = STEPS_PER_ROTOR_REV * GEAR_REDUCTION * ORGEL_REDUCTION / ORGEL_BPM_PER_ROUND / 60;

// Create a Driver Object
TMC2209Stepper driver(&DRIVER_SERIAL, R_SENSE, DRIVER_ADDRESS);
// Power Sensor
INA226 ina;

// Lock for the I2C Bus
SemaphoreHandle_t I2CMutex = xSemaphoreCreateMutex();
// Bus max delay
#define portMAX_DELAY 50

// Variables
bool playStatus = false;
int playBPM = 120;
int motorCurrent = 950;
bool autoCurrentEnabled;
bool motorDirection;

// Current Optimize
int targetWorkload = 70;

void setup()
{
    // TcMenu Initialize
    EEPROM.begin(512);
    setupMenu();
    menuMgr.load();
    installTheme();
    menuBPM.setCurrentValue(120);
    homePage();
    motorDirection = menuDirection.getBoolean();

    // Configure INA226
    ina.begin();
    ina.configure();
    ina.calibrate(0.1, 1.7); // Rshunt = 0.1 ohm, Max current = 1.7A

    Serial.begin(9600);
    Serial.println("Orgel Running...");

    // Init TMC2209 driver
    driverSetup();
    setSpeed(0);

    // Different func. run in two cores
    xTaskCreatePinnedToCore(
        runTcMenu,      // pvTaskCode   Code to run
        "runTcMenu",    // pcName       A name just for humans
        8192,           // usStackDepth This stack size can be checked & adjusted by reading the Stack Highwater
        NULL,           // pvParameters
        2,              // uxPriority   3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
        NULL,           // pxCreatedTask
        1               // tskNO_AFFINITY   Whether to scheduling tasks dynamiclly
        );
    
    xTaskCreatePinnedToCore(
        runFunctions,      // pvTaskCode   Code to run
        "runFunctions",    // pcName       A name just for humans
        8192,           // usStackDepth This stack size can be checked & adjusted by reading the Stack Highwater
        NULL,           // pvParameters
        2,              // uxPriority   3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
        NULL,           // pxCreatedTask
        1               // tskNO_AFFINITY   Whether to scheduling tasks dynamiclly
        );
}

void loop()
{
}

// TcMenu 主题设置
void installTheme()
{
    renderer.setTitleMode(BaseGraphicalRenderer::TITLE_FIRST_ROW);
    renderer.setUseSliderForAnalog(false);
    installMonoInverseTitleTheme(renderer, MenuFontDef(nullptr, 1), MenuFontDef(nullptr, 1), true);
}

// TcMenu 主进程循环函数
void runTcMenu(void *pvParameters)
{
    for (;;)
    {   
        xSemaphoreTake(I2CMutex, portMAX_DELAY);
        taskManager.runLoop();
        xSemaphoreGive(I2CMutex);
    }
}

// 功能、次要进程循环函数
void runFunctions(void *pvParameters)
{
    for (;;)
    {
        getPowerStatus();
        currentOptimize();
    }
}

// TMC2209初始化
void driverSetup()
{
    pinMode(ENABLE_Pin, OUTPUT);   // 控制TMC2209使能引脚为输出模式
    pinMode(DIAG_Pin, INPUT);      // 控制TMC2209过载引脚为输入模式
    digitalWrite(ENABLE_Pin, LOW); // 将使能控制引脚设置为低电平从而让电机驱动板进入工作状态

    DRIVER_SERIAL.begin(115200); // 启动串口

    driver.begin();       // 开始通讯
    driver.microsteps(8); // 设置微步大小

    // 电流设置
    driver.rms_current(50); // 设置电流大小 (mA)
}

// 变更播放状态
void CALLBACK_FUNCTION switchPlayStatus(int id)
{
    if (menuPlay.getBoolean())
    {
        playStatus = true;
        setMotorSpeed(menuBPM.getCurrentValue());
    }
    else
    {
        playStatus = false;
        setMotorSpeed(0);
    }
    menuTargetCurrent.setCurrentValue(motorCurrent);
}

// BPM改变回调
void CALLBACK_FUNCTION setSpeed(int id)
{
    setMotorSpeed(menuBPM.getCurrentValue());
    menuTargetCurrent.setCurrentValue(motorCurrent);
}

// 改变电机速度
void setMotorSpeed(int BPM)
{
    if (playStatus)
    {
        playBPM = BPM;

        // Set Motor Speed
        if (motorDirection)
        {
            driver.VACTUAL(BPM * BPM_CALC_CONST / 0.715);
        }
        else
        {
            driver.VACTUAL(-BPM * BPM_CALC_CONST / 0.715);
        }

        // Set Current
        motorCurrent = 950; // Bset Current I found. Even Better than dynamic current.
        // motorCurrent = 550 + 0.1 * BPM + 0.0015 * BPM * BPM;
        // if (motorCurrent < 600)
        // {
        //     motorCurrent = 600;
        // }
        // else if (motorCurrent > 1000)
        // {
        //     motorCurrent = 1000;
        // }
        driver.rms_current(motorCurrent); // 设置电流大小 (mA)
    }
    else
    {
        driver.VACTUAL(0);
        driver.rms_current(50);
    }
}

// 手动设置电流
void CALLBACK_FUNCTION setMotorCurrent(int id) {
    if(menuTargetCurrent.getCurrentValue() != motorCurrent){
        motorCurrent = menuTargetCurrent.getCurrentValue();
        driver.rms_current(motorCurrent);
    }
}

// 设置电机运行方向
void CALLBACK_FUNCTION changeMotorDir(int id)
{
    motorDirection = !motorDirection;
    setMotorSpeed(menuBPM.getCurrentValue());
}

// 返回首页
void CALLBACK_FUNCTION toHomePage(int id)
{
    menuMgr.save();
    EEPROM.commit();
    renderer.takeOverDisplay();
}

// 电流计读数
void getPowerStatus()
{   
    xSemaphoreTake(I2CMutex, portMAX_DELAY);
    menuSupplyVoltage.setFloatValue(ina.readBusVoltage());
    xSemaphoreGive(I2CMutex);
}

// 电机负载读数、电流PID调整
void currentOptimize()
{
    int workload = driver.SG_RESULT();
    menuSGWorkload.setCurrentValue(workload);
}
