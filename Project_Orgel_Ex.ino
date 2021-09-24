#include <TMCStepper.h>
#include <ESPRotary.h>
#include <OneButton.h>
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define ROTARY_Pin1 34   // 旋转编码器#1
#define ROTARY_Pin2 35   // 旋转编码器#2
#define ROTARY_Button 32 // 旋转编码器按键

#define CLICKS_PER_STEP 4 // 旋转编码器每步经过的触发数
#define MIN_POS 0         // BPM最小值
#define MAX_POS 480       // BPM最大值
#define START_POS 120      // 初始值
#define INCREMENT 1       // 每步增量

#define DRIVER_SERIAL Serial2 // 电机驱动硬件串口
#define DRIVER_ADDRESS 0b00 // 电机驱动串口地址
#define R_SENSE 0.11f       // Match to your driver <- ???
#define DIR_Pin 25          // 电机方向控制引脚
#define STEP_Pin 26         // 电机步进控制引脚
#define ENABLE_Pin 33       // 电机使能控制引脚
#define DIAG_Pin 19         // 电机过载指示引脚

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

// 创建旋转编码器对象
ESPRotary rotary = ESPRotary(ROTARY_Pin1, ROTARY_Pin2, CLICKS_PER_STEP, MIN_POS, MAX_POS, START_POS, INCREMENT);

// 创建按键对象
OneButton button = OneButton(ROTARY_Button, true);

// 创建电机对象
TMC2209Stepper driver(&DRIVER_SERIAL, R_SENSE, DRIVER_ADDRESS);

// 创建OLED对象
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);


// 运行时变量
bool playState = false;
int playBPM = 120;
int motorCurrent = 300;

bool redrawRequired = true;

// 初始化函数
void setup()
{
  Serial.begin(9600);
  Serial.println("Orgel Running...");

  // TMC2209
  driverSetup();    // 电机驱动初始化
  setSpeed(0);

  // 旋转编码器
  rotary.setLowerBound(MIN_POS);    // 设置BPM下限
  rotary.setUpperBound(MAX_POS);    // 设置BPM上限
  rotary.setChangedHandler(rotate); // 设置旋转编码器值变化调用函数

  button.attachClick(buttonClick); // 设置旋转编码器按键单击调用函数

  // OLED
  u8g2.begin();
  u8g2.enableUTF8Print();
}

// 运行时循环函数
void loop()
{
  
  rotary.loop();
  button.tick();

  CLI();

  if (redrawRequired){
    homePage();
  }

  if (DIAG_Pin == LOW){
    Serial.println("Stall!");
  }
}

// 编码器变化调用函数
void rotate(ESPRotary &rotary)
{
  playBPM = rotary.getPosition();
  if(playState){
    setSpeed(playBPM);
  }
  redrawRequired = true;
  
}

// 编码器按键单击函数
void buttonClick()
{
  playState = !playState;
  if(playState){
    setSpeed(playBPM);
  }else {
    setSpeed(0);
  }
  redrawRequired = true;
}

void driverSetup(){
  pinMode(STEP_Pin, OUTPUT);     // 控制TMC2209步进引脚为输出模式
  pinMode(DIR_Pin, OUTPUT);      // 控制TMC2209方向引脚为输出模式
  pinMode(ENABLE_Pin, OUTPUT);   // 控制TMC2209使能引脚为输出模式
  pinMode(DIAG_Pin, INPUT);      // 控制TMC2209过载引脚为输入模式
  digitalWrite(ENABLE_Pin, LOW); // 将使能控制引脚设置为低电平从而让电机驱动板进入工作状态
  
  DRIVER_SERIAL.begin(115200);  // 启动串口

  driver.begin();             // 开始通讯
  driver.microsteps(8);       // 设置微步大小

  // 电流设置
  driver.rms_current(300);    // 设置电流大小 (mA)
}

void setSpeed(int BPM){
  if (playState){
    // 电机速度设置
    driver.VACTUAL(- BPM * BPM_CALC_CONST / 0.715);
  
    // 电流设置
    motorCurrent = 950 + 0.2*BPM + 0.0026*BPM*BPM;
    if (motorCurrent < 800){
      motorCurrent = 800;
    }
    else if (motorCurrent > 1650){
      motorCurrent = 1650;
    }
    driver.rms_current(motorCurrent);    // 设置电流大小 (mA)
  } else {
    driver.VACTUAL(0);
    driver.rms_current(300);    // 设置电流大小 (mA)
  }
  
}
