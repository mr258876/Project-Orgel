#include "Project-Orgel_menu.h"
// default CPP main file for sketch
#include <PlatformDetermination.h>
#include <TaskManagerIO.h>

#include "ThemeProjOrgel.h"
#include "HomepageProjOrgel.h"

#include <TMCStepper.h>

#define DRIVER_SERIAL Serial2 // TMC2209 Serial Port
#define DRIVER_ADDRESS 0b00   // Serial Address
#define R_SENSE 0.11f         // Match to your driver <- ???
#define ENABLE_Pin 33         // Enable Pin

// 电机内部输出轴旋转一周步数
const int STEPS_PER_ROTOR_REV = 1600; // 42电机 一圈1600*八分之一微步
// 输出轴减速比
// const float GEAR_REDUCTION = 12.0; // Nidec 25GBC12 输出轴减速比1:12
const float GEAR_REDUCTION = 1.0; // 42电机 输出轴直出
// 八音盒减速比
// const float ORGEL_REDUCTION = 0.69; // 29齿八音盒齿轮:42齿电机齿轮
const float ORGEL_GEAR = 29; // 29齿八音盒齿轮
const float MOTOR_GEAR = 60; // 60齿电机齿轮
// 八音盒齿轮周拍
const float ORGEL_BPM_PER_ROUND = 4.516; // 齿轮周长约1.15picm,纸带一拍0.8cm,故八音盒齿轮旋转一周约4.516拍
// 获得BPM计算常数
// const float BPM_CALC_CONST = STEPS_PER_ROTOR_REV * GEAR_REDUCTION * ORGEL_GEAR / MOTOR_GEAR / ORGEL_BPM_PER_ROUND / 60;
float BPM_CALC_CONST = STEPS_PER_ROTOR_REV * GEAR_REDUCTION * ORGEL_GEAR / 1 / ORGEL_BPM_PER_ROUND / 60;

// Create a Driver Object
TMC2209Stepper driver(&DRIVER_SERIAL, R_SENSE, DRIVER_ADDRESS);

// Variables
bool playStatus = false;
int playBPM = 120;
int motorCurrent = 950;
bool autoCurrentEnabled;
bool motorDirection;
int motorGear = 60;

void setup()
{
    // TcMenu Initialize
    setupMenu();
    menuMgr.load();
    installTheme();
    menuBPM.setCurrentValue(120);
    homePage();
    motorDirection = menuDirection.getBoolean();
    motorCurrent = menuCurrent.getCurrentValue();
    motorGear = menuGearTeeth.getCurrentValue();

    Serial.begin(115200);
    Serial.println("Orgel Running...");

    // Init TMC2209 driver
    driverSetup();
    setSpeed(0);
}

void loop()
{
    taskManager.runLoop();
}

// TcMenu 主题设置
void installTheme()
{
    renderer.setTitleMode(BaseGraphicalRenderer::TITLE_FIRST_ROW);
    renderer.setUseSliderForAnalog(false);
    installMonoInverseTitleTheme(renderer, MenuFontDef(u8g2_font_wqy14_t_gb2312b, 1), MenuFontDef(u8g2_font_wqy14_t_gb2312b, 1), true);
    gfx.enableUTF8Print();    // 启用UTF-8以支持多语言
    gfx.setFontPosBaseline(); // 设置字体基线
}

// 电机初始化
void driverSetup()
{
    pinMode(ENABLE_Pin, OUTPUT);   // 控制TMC2209使能引脚为输出模式
    digitalWrite(ENABLE_Pin, LOW); // 将使能控制引脚设置为低电平从而让电机驱动板进入工作状态

    DRIVER_SERIAL.begin(115200); // 启动串口

    driver.begin();       // 开始通讯
    driver.microsteps(8); // 设置微步大小

    // 电流设置
    driver.rms_current(50); // 设置电流大小 (mA)
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
            driver.VACTUAL(BPM * BPM_CALC_CONST / motorGear / 0.715);
        }
        else
        {
            driver.VACTUAL(-BPM * BPM_CALC_CONST / motorGear / 0.715);
        }

        // Set Current
        driver.rms_current(motorCurrent); // 设置电流大小 (mA)
    }
    else
    {
        driver.VACTUAL(0);
        driver.rms_current(50);
    }
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
}

// BPM改变回调
void CALLBACK_FUNCTION setSpeed(int id)
{
    setMotorSpeed(menuBPM.getCurrentValue());
}

// 设置电机运行方向
void CALLBACK_FUNCTION changeMotorDir(int id)
{
    motorDirection = !motorDirection;
}

// 返回首页
void CALLBACK_FUNCTION toHomePage(int id)
{
    menuMgr.save();
    EEPROM.commit();
    renderer.takeOverDisplay();
}

// 设置齿轮齿数回调
void CALLBACK_FUNCTION setGearTeeth(int id)
{
    // TODO - your menu change code
    motorGear = menuGearTeeth.getCurrentValue();
    setMotorSpeed(menuBPM.getCurrentValue());
}

// 电流数值改变回调函数
void CALLBACK_FUNCTION setCurrent(int id) {
    // TODO - your menu change code
    motorCurrent = menuCurrent.getCurrentValue();
    setMotorSpeed(menuBPM.getCurrentValue());
}
