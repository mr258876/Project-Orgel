#include "pinouts.h"

#include "Project-Orgel_menu.h"
// default CPP main file for sketch
#include <PlatformDetermination.h>
#include <TaskManagerIO.h>

#include "ThemeProjOrgel.h"
#include "HomepageProjOrgel.h"

#include <HardwareSerial.h>
#include <TMCStepper.h>

#include "lv_i18n.h"

#include <NimBLEDevice.h> // Bluetooth
#include "BLEInterface.h"

#include "PowerManager.h"

#ifndef NRF51
#include "u8g2_wqy_14_project_orgel.h"
#endif

#if SOC_UART_NUM > 2
#define DRIVER_SERIAL Serial2 // TMC2209 Serial Port
#elif SOC_UART_NUM > 1
#define DRIVER_SERIAL Serial1 // ESP32C3 have only 2 serial ports
#else
#define DRIVER_SERIAL Serial // nRF51 have only 1 serial port
#endif

#define DRIVER_ADDRESS 0b00 // Serial Address

#ifndef NRF51
#define R_SENSE 0.11f // Match to your driver <- Refer "Selecting Sense Resistors" section in datasheet
#else
#define R_SENSE 0.12f // Refer to schema
#endif

// 电机内部输出轴旋转一周步数
#define STEPS_PER_ROTOR_REV 200 // 42电机 一圈200
#define DRIVER_MICROSTEPS 8
// 输出轴减速比
#define GEAR_REDUCTION 1.0f // 42电机 输出轴直出
// 八音盒减速比
#define ORGEL_GEAR 29 // 29齿八音盒齿轮
// 八音盒齿轮周拍
#define ORGEL_BPM_PER_ROUND 4.51603944f // 齿轮周长约1.15picm,纸带一拍0.8cm,故八音盒齿轮旋转一周约4.516拍
// 获得BPM计算常数
// const double BPM_CALC_CONST = STEPS_PER_ROTOR_REV * GEAR_REDUCTION * ORGEL_GEAR / MOTOR_GEAR / ORGEL_BPM_PER_ROUND / 60;
const float BPM_CALC_CONST = STEPS_PER_ROTOR_REV * DRIVER_MICROSTEPS * GEAR_REDUCTION * ORGEL_GEAR / ORGEL_BPM_PER_ROUND / 60; // <- 电机齿轮现在由菜单赋值并在设置BPM时计算齿轮比

// Create a Driver Object
TMC2209Stepper driver(&DRIVER_SERIAL, R_SENSE, DRIVER_ADDRESS);

// Power Manager
PowerManager pm(CH224K_PG_Pin, CH224K_CFG1_Pin, CH224K_CFG2_Pin, CH224K_CFG3_Pin);

// Variables
bool playStatus = false;
int16_t playBPM = 120;
int16_t motorCurrent = 500;
bool autoCurrentEnabled;
bool motorDirection;
int16_t motorGear = 60;
bool lastPowerStatus = false;

////////// FUNCTION PROTOTYPES //////////
static void syncValuesFromBluetooth();
static void storeNvsDefaults();
static void installTheme();
static void powerSetup();
static void checkPowerStatus();
static void driverSetup();
static void updateMotorParams();

////////// FUNCTIONS ///////////
void setup()
{
#if defined(ESP_PLATFORM)
    EEPROM.begin(512);
    Serial.begin(115200);
#elif defined(NRF51)
    // EEPROM.begin();
    Wire.setPins(DISPLAY_I2C_SDA_Pin, DISPLAY_I2C_SCL_Pin); // Have to change pin here since nrf51 dont have Wire.begin(SDA, SCL)
    Wire.begin();
    Wire.setClock(400000L);

    // force 12v power for now
    pinMode(4, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);

    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);
#else
#error unsupported platform!
#endif

    // Init locale engine first, or gfx crashes
    lv_i18n_init(lv_i18n_language_pack);
    lv_i18n_set_locale(lv_i18n_language_pack[0]->locale_name);

    // TcMenu Initialize
    setupMenu();
    menuMgr.load(0xfade, storeNvsDefaults);

    // Reset language base on value loaded
    lv_i18n_set_locale(lv_i18n_language_pack[menuLanguage.getCurrentValue()]->locale_name);

    // Init Bluetooth
    setBluetoothOn(25);

    // Continue TcMenu Init
    installTheme();
    homePage();

    motorDirection = menuDirection.getBoolean();
    motorCurrent = menuCurrent.getCurrentValue();
    motorGear = menuGearTeeth.getCurrentValue();

    // Set serial pinout
#if defined(ESP_PLATFORM)
    DRIVER_SERIAL.begin(115200, SERIAL_8N1, MOTOR_SERIAL_RX_Pin, MOTOR_SERIAL_TX_Pin);
#elif defined(NRF51)
    DRIVER_SERIAL.setPins(MOTOR_SERIAL_RX_Pin, MOTOR_SERIAL_TX_Pin);
    DRIVER_SERIAL.begin(115200);
    vTaskDelay(100);
#else
#error unsupported platform!
#endif

    // Init TMC2209 driver
    powerSetup();
    driverSetup();
    setSpeed(0);
}

void loop()
{
    taskManager.runLoop();
    syncValuesFromBluetooth();
    checkPowerStatus();
}

// TcMenu 主题设置
static void installTheme()
{
#ifndef NRF51
    renderer.setTitleMode(BaseGraphicalRenderer::TITLE_FIRST_ROW);
    renderer.setUseSliderForAnalog(false);
    installMonoInverseTitleTheme(renderer, MenuFontDef(u8g2_wqy_14_project_orgel, 1), MenuFontDef(u8g2_wqy_14_project_orgel, 1), true);
    gfx.enableUTF8Print();    // 启用UTF-8以支持多语言
    gfx.setFontPosBaseline(); // 设置字体基线
#endif
}

// 向NVS中写入初始值
static void storeNvsDefaults()
{
#if defined(NRF51)
    EEPROM.format();
#endif

    menuMgr.save();
}

/*
    @brief Init power manager
*/
static void powerSetup()
{
    pm.begin();
    pm.acquireVoltage(menuVoltage.getCurrentValue());

    lastPowerStatus = false;
    menuPWRStatus.setCurrentValue(1);   // Set to "Error"
}

/*
    @brief Poll PG signal
*/
static void checkPowerStatus()
{
    uint8_t pg = pm.powerGood();
    if (lastPowerStatus != pg)
    {
        menuPWRStatus.setCurrentValue(pg + 1);
        lastPowerStatus = pg;
    }
}

/*
    @brief Init stepper driver
*/
static void driverSetup()
{
    pinMode(MOTOR_ENABLE_Pin, OUTPUT);    // 控制TMC2209使能引脚为输出模式
    digitalWrite(MOTOR_ENABLE_Pin, HIGH); // 将使能控制引脚设置为低电平从而让电机驱动板进入工作状态

    DRIVER_SERIAL.begin(115200); // 启动串口

    driver.begin();                       // 开始通讯
    driver.microsteps(DRIVER_MICROSTEPS); // 设置微步大小

    // 电流设置
    driver.rms_current(50); // 设置电流大小 (mA)

    digitalWrite(MOTOR_ENABLE_Pin, LOW); // 将使能控制引脚设置为低电平从而让电机驱动板进入工作状态
}

/*
    @brief Update motor operation params with UART
*/
static void updateMotorParams()
{
    if (playStatus)
    {
        // Set Motor Speed
        if (motorDirection)
        {
            driver.VACTUAL(playBPM * BPM_CALC_CONST / motorGear / 0.715);
        }
        else
        {
            driver.VACTUAL(-playBPM * BPM_CALC_CONST / motorGear / 0.715);
        }

        // Set Current
        driver.rms_current(motorCurrent); // 设置电流大小 (mA)
    }
    else
    {
        driver.VACTUAL(0);
        driver.rms_current(5);
    }
}

static void syncValuesFromBluetooth()
{
    if (ble_new_value_received)
    {
        menuBPM.setCurrentValue(ble_bpm_received);
        menuPlay.setBoolean(ble_play_status_received);
        ble_new_value_received = false;
    }
}

// 变更播放状态
void CALLBACK_FUNCTION switchPlayStatus(int id)
{
    if (menuPlay.getBoolean())
    {
        playStatus = true;
        updateMotorParams();
    }
    else
    {
        playStatus = false;
        updateMotorParams();
    }
}

// BPM改变回调
void CALLBACK_FUNCTION setSpeed(int id)
{
    playBPM = menuBPM.getCurrentValue();
    updateMotorParams();
}

// 设置电机运行方向
void CALLBACK_FUNCTION changeMotorDir(int id)
{
    motorDirection = !motorDirection;
    updateMotorParams();
}

// 返回首页
void CALLBACK_FUNCTION toHomePage(int id)
{
    menuMgr.save();

#if defined(ESP_PLATFORM)
    EEPROM.commit();
#endif
    renderer.takeOverDisplay();
}

// 设置齿轮齿数回调
void CALLBACK_FUNCTION setGearTeeth(int id)
{
    // TODO - your menu change code
    motorGear = menuGearTeeth.getCurrentValue();
    updateMotorParams();
}

// 电流数值改变回调函数
void CALLBACK_FUNCTION setCurrent(int id)
{
    motorCurrent = menuCurrent.getCurrentValue();
    updateMotorParams();
}

/*
    @brief  Callback function of menuLanguage
*/
void CALLBACK_FUNCTION setLanguage(int id)
{
    lv_i18n_set_locale(lv_i18n_language_pack[menuLanguage.getCurrentValue()]->locale_name);

    menuMgr.save();

#if defined(ESP_PLATFORM)
    EEPROM.commit();
#endif
    menuMgr.resetMenu(false);
}

/*
    @brief  Callback function of menuBluetooth
*/
void CALLBACK_FUNCTION setBluetoothOn(int id)
{
    if (menuBluetooth.getBoolean())
    {
        ble_on();
    }
    else
    {
        ble_off();
    }

    menuMgr.save();

#if defined(ESP_PLATFORM)
    EEPROM.commit();
#endif
}

/*
    @brief  Callback function of menuVoltage
*/
void CALLBACK_FUNCTION setPowerVoltage(int id)
{
    pm.acquireVoltage(menuVoltage.getCurrentValue());
#if defined(ESP_PLATFORM)
    EEPROM.commit();
#endif
}
current power supply is unable to provide the required voltage