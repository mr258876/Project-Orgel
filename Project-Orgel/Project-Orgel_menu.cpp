/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#include <tcMenu.h>
#include <EEPROM.h>
#include "Project-Orgel_menu.h"
#include "pinouts.h"

// Global variable declarations
#if defined(NRF51)
const PROGMEM  ConnectorLocalInfo applicationInfo = { "Project-Orgel-LITE", "b17605de-fb70-4e86-93dc-73130cb2c43e" };
#else
const PROGMEM  ConnectorLocalInfo applicationInfo = { "Project-Orgel", "b17605de-fb70-4e86-93dc-73130cb2c43e" };
#endif
#if defined(NRF51)
#include "nrfEEPROMAbstraction.h"
NrfEEPROMAbstraction glArduinoEeprom(&EEPROM);  // the EEPROM.read() in n-able-nRF behave different from the original Arduino EEPROM, so we use get/put only.
#else
ArduinoEEPROMAbstraction glArduinoEeprom(&EEPROM);
#endif

#if defined(NRF51)
#include "ssd1306utf8_wqy14.h"
SSD1306UTF8Wire oled;
SSD1306UTF8Renderer renderer(20, ssd1306utf8_wqy14, ssd1306utf8_wqy14);
#else
U8G2_SSD1306_128X64_NONAME_F_HW_I2C gfx(U8G2_R0, DISPLAY_I2C_SCL_Pin, DISPLAY_I2C_SDA_Pin, DISPLAY_I2C_RST_Pin);
U8g2Drawable gfxDrawable(&gfx);
GraphicsDeviceRenderer renderer(30, applicationInfo.name, &gfxDrawable);
#endif

// Global Menu Item declarations
const PROGMEM AnyMenuInfo minfoAboutText3 = { "Version", 23, 0xffff, 0, NO_CALLBACK };
TextMenuItem menuAboutText3(&minfoAboutText3, "0.3.4", 5, nullptr, INFO_LOCATION_PGM);
const PROGMEM AnyMenuInfo minfoAboutText2 = { "By Mr258876", 8, 0xffff, 0, NO_CALLBACK };
TextMenuItem menuAboutText2(&minfoAboutText2, "", 1, &menuAboutText3, INFO_LOCATION_PGM);
#if defined(NRF51)
const PROGMEM AnyMenuInfo minfoAboutText1 = { "Project-Orgel-LITE", 7, 0xffff, 0, NO_CALLBACK };
#else
const PROGMEM AnyMenuInfo minfoAboutText1 = { "Project-Orgel", 7, 0xffff, 0, NO_CALLBACK };
#endif
TextMenuItem menuAboutText1(&minfoAboutText1, "", 1, &menuAboutText2, INFO_LOCATION_PGM);
const PROGMEM SubMenuInfo minfoAbout = { "About", 6, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackAbout(&minfoAbout, &menuAboutText1, INFO_LOCATION_PGM);
SubMenuItem menuAbout(&minfoAbout, &menuBackAbout, nullptr, INFO_LOCATION_PGM);
const char enumStrLanguage_0[] PROGMEM = "ENG";
const char enumStrLanguage_1[] PROGMEM = "CHS";
const char* const enumStrLanguage[] PROGMEM  = { enumStrLanguage_0, enumStrLanguage_1 };
const PROGMEM EnumMenuInfo minfoLanguage = { "Language", 24, 7, 1, setLanguage, enumStrLanguage };
EnumMenuItem menuLanguage(&minfoLanguage, 0, &menuAbout, INFO_LOCATION_PGM);
const char enumStrPWRStatus_0[] PROGMEM = "Unknown";
const char enumStrPWRStatus_1[] PROGMEM = "Error";
const char enumStrPWRStatus_2[] PROGMEM = "Good";
const char* const enumStrPWRStatus[] PROGMEM  = { enumStrPWRStatus_0, enumStrPWRStatus_1, enumStrPWRStatus_2 };
const PROGMEM EnumMenuInfo minfoPWRStatus = { "PWR Status", 27, 0xffff, 2, NO_CALLBACK, enumStrPWRStatus };
EnumMenuItem menuPWRStatus(&minfoPWRStatus, 0, nullptr, INFO_LOCATION_PGM);
const char enumStrVoltage_0[] PROGMEM = "5V";
const char enumStrVoltage_1[] PROGMEM = "9V";
const char enumStrVoltage_2[] PROGMEM = "12V";
const char enumStrVoltage_3[] PROGMEM = "15V";
const char enumStrVoltage_4[] PROGMEM = "20V";
const char* const enumStrVoltage[] PROGMEM  = { enumStrVoltage_0, enumStrVoltage_1, enumStrVoltage_2, enumStrVoltage_3, enumStrVoltage_4 };
const PROGMEM EnumMenuInfo minfoVoltage = { "PWR Voltage", 26, 10, 4, setPowerVoltage, enumStrVoltage };
EnumMenuItem menuVoltage(&minfoVoltage, 2, &menuPWRStatus, INFO_LOCATION_PGM);
const PROGMEM AnalogMenuInfo minfoCurrent = { "Current", 22, 5, 2047, setCurrent, 0, 1, "mA" };
AnalogMenuItem menuCurrent(&minfoCurrent, 1023, &menuVoltage, INFO_LOCATION_PGM);
const PROGMEM AnalogMenuInfo minfoGearTeeth = { "Gear Teeth", 21, 3, 255, setGearTeeth, 0, 1, "" };
AnalogMenuItem menuGearTeeth(&minfoGearTeeth, 60, &menuCurrent, INFO_LOCATION_PGM);
const PROGMEM BooleanMenuInfo minfoDirection = { "Reversed", 19, 2, 1, changeMotorDir, NAMING_CHECKBOX };
BooleanMenuItem menuDirection(&minfoDirection, false, &menuGearTeeth, INFO_LOCATION_PGM);
const PROGMEM SubMenuInfo minfoMotor = { "Motor", 4, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackMotor(&minfoMotor, &menuDirection, INFO_LOCATION_PGM);
SubMenuItem menuMotor(&minfoMotor, &menuBackMotor, &menuLanguage, INFO_LOCATION_PGM);
const PROGMEM BooleanMenuInfo minfoBluetooth = { "Bluetooth", 25, 9, 1, setBluetoothOn, NAMING_ON_OFF };
BooleanMenuItem menuBluetooth(&minfoBluetooth, false, &menuMotor, INFO_LOCATION_PGM);
const PROGMEM AnalogMenuInfo minfoBPM = { "BPM", 2, 0xffff, 511, setSpeed, 0, 1, "" };
AnalogMenuItem menuBPM(&minfoBPM, 120, &menuBluetooth, INFO_LOCATION_PGM);
const PROGMEM BooleanMenuInfo minfoPlay = { "play", 1, 0xffff, 1, switchPlayStatus, NAMING_TRUE_FALSE };
BooleanMenuItem menuPlay(&minfoPlay, false, &menuBPM, INFO_LOCATION_PGM);
const PROGMEM AnyMenuInfo minfoBackToHomepage = { "Back and Save", 20, 0xffff, 0, toHomePage };
ActionMenuItem menuBackToHomepage(&minfoBackToHomepage, &menuPlay, INFO_LOCATION_PGM);

void setupMenu() {
    // First we set up eeprom and authentication (if needed).
    setSizeBasedEEPROMStorageEnabled(false);
    menuMgr.setEepromRef(&glArduinoEeprom);
    // Now add any readonly, non-remote and visible flags.
    menuPWRStatus.setReadOnly(true);
    menuAboutText1.setReadOnly(true);
    menuAboutText3.setReadOnly(true);
    menuAboutText2.setReadOnly(true);
    menuBPM.setVisible(false);
    menuPlay.setVisible(false);

    // Code generated by plugins and new operators.
    #if defined(NRF51)
    oled.begin(&Adafruit128x64, 0x3C);
    renderer.setGraphicsDevice(&oled);
    #else
    menuVoltage.setVisible(false);
    gfx.begin();
    renderer.setUpdatesPerSecond(30);
    #endif
    switches.init(internalDigitalIo(), SWITCHES_NO_POLLING, true);
    menuMgr.initForEncoder(&renderer, &menuBackToHomepage, ENCODER_A_Pin, ENCODER_B_Pin, ENCODER_OK_Pin);
}

