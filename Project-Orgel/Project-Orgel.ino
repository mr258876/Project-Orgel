#include "Project-Orgel_menu.h"
// default CPP main file for sketch
#include <PlatformDetermination.h>
#include <TaskManagerIO.h>

#include "ThemeProjOrgel.h"
#include "HomepageProjOrgel.h"

#include <TMCStepper.h>

#define DRIVER_SERIAL Serial2 // 电机驱动硬件串口
#define DRIVER_ADDRESS 0b00   // 电机驱动串口地址
#define R_SENSE 0.11f         // Match to your driver <- ???
#define ENABLE_Pin 33         // 电机使能控制引脚
#define DIAG_Pin 19           // 电机过载指示引脚

// 电机内部输出轴旋转一周步数
//const int STEPS_PER_ROTOR_REV = 194; // Nidec 25GBC12 一圈194*八分之一微步
const int STEPS_PER_ROTOR_REV = 1600; // 42电机 一圈1600*八分之一微步
// 输出轴减速比
//const float GEAR_REDUCTION = 12.0; // Nidec 25GBC12 输出轴减速比1:12
const float GEAR_REDUCTION = 1.0; // 42电机 输出轴直出
// 八音盒减速比
//const float ORGEL_REDUCTION = 0.69; // 29齿八音盒齿轮:42齿电机齿轮
const float ORGEL_REDUCTION = 0.48; // 29齿八音盒齿轮:60齿电机齿轮
// 八音盒齿轮周拍
const float ORGEL_BPM_PER_ROUND = 4.516; // 齿轮周长约1.15picm,纸带一拍0.8cm,故八音盒齿轮旋转一周约4.516拍
// 获得BPM计算常数
const float BPM_CALC_CONST = STEPS_PER_ROTOR_REV * GEAR_REDUCTION * ORGEL_REDUCTION / ORGEL_BPM_PER_ROUND / 60;

// 创建电机对象
TMC2209Stepper driver(&DRIVER_SERIAL, R_SENSE, DRIVER_ADDRESS);


int motorCurrent = 300;

void setup()
{
    setupMenu();
    installTheme();
    homePage();

    Serial.begin(9600);
    Serial.println("Orgel Running...");

    // TMC2209
    driverSetup(); // 电机驱动初始化
    setSpeed(0);
}


void loop()
{
    taskManager.runLoop();
}


void installTheme(){
    renderer.setTitleMode(BaseGraphicalRenderer::TITLE_FIRST_ROW);
    renderer.setUseSliderForAnalog(false);
    installMonoInverseTitleTheme(renderer, MenuFontDef(nullptr, 1), MenuFontDef(nullptr, 1), true);
}


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


void CALLBACK_FUNCTION switchPlayStatus(int id)
{
    if (menuPlay.getBoolean())
    {
        setMotorSpeed(menuBPM.getCurrentValue());
    }
    else
    {
        setMotorSpeed(0);
    }
}


void CALLBACK_FUNCTION setSpeed(int id) {
    setMotorSpeed(menuBPM.getCurrentValue());
}


void setMotorSpeed(int BPM)
{
    if (menuPlay.getBoolean())
    {
        // 电机速度设置
        driver.VACTUAL(-BPM * BPM_CALC_CONST / 0.715);

        // 电流设置
        motorCurrent = 950 + 0.2 * BPM + 0.0026 * BPM * BPM;
        if (motorCurrent < 800)
        {
            motorCurrent = 800;
        }
        else if (motorCurrent > 1650)
        {
            motorCurrent = 1650;
        }
        driver.rms_current(motorCurrent); // 设置电流大小 (mA)
    }
    else
    {
        driver.VACTUAL(0);
        driver.rms_current(50); // 设置电流大小 (mA)
    }
}


void CALLBACK_FUNCTION switchCurrentAutoOptimize(int id) {
    // TODO - your menu change code
}


void CALLBACK_FUNCTION switchStandbyPowerDown(int id) {
    // TODO - your menu change code
}