#include "Project-Orgel_menu.h"
// default CPP main file for sketch
#include <PlatformDetermination.h>
#include <TaskManagerIO.h>

#include "ThemeProjOrgel.h"
#include "HomepageProjOrgel.h"

#include <AccelStepper.h>

#define ENABLE_Pin  33      // Enable Pin
#define DIR_Pin     25      // Direction Pin    
#define STEP_Pin    26      // Step Pin

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

// Create a Stepper Object
AccelStepper stepper(1, STEP_Pin, DIR_Pin);

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
    stepper.runSpeed();
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
    pinMode(STEP_Pin, OUTPUT);      // 步进引脚输出模式
    pinMode(DIR_Pin, OUTPUT);       // 方向引脚输出模式
    pinMode(ENABLE_Pin, OUTPUT);    // 使能引脚输出模式
    digitalWrite(ENABLE_Pin, LOW);  // 将使能控制引脚设置为低电平从而让电机驱动板进入工作状态

    stepper.setMaxSpeed(10240.0);     // 设置电机最大速度300 
    stepper.setAcceleration(20.0);  // 设置电机加速度20.0  
    setMotorSpeed(playBPM);
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
            stepper.setSpeed(BPM * BPM_CALC_CONST / motorGear);
        }
        else
        {
            stepper.setSpeed(-BPM * BPM_CALC_CONST / motorGear);
        }
    }
    else
    {
        stepper.setSpeed(0);
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
