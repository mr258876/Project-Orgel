/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#include <tcMenu.h>
#include "Project-Orgel_menu.h"
#include "pinouts.h"

// Global variable declarations
const PROGMEM  ConnectorLocalInfo applicationInfo = { "Project-Orgel", "b17605de-fb70-4e86-93dc-73130cb2c43e" };
ArduinoEEPROMAbstraction glArduinoEeprom(&EEPROM);
#if defined(ESP_PLATFORM)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C gfx(U8G2_R0, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE);
#elif defined(NRF51)
U8G2_SSD1306_128X64_NONAME_1_HW_I2C gfx(U8G2_R0, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE);
#endif
U8g2Drawable gfxDrawable(&gfx);
GraphicsDeviceRenderer renderer(30, applicationInfo.name, &gfxDrawable);

// Global Menu Item declarations
const PROGMEM AnyMenuInfo minfoAboutText3 = { "Version", 23, 0xffff, 0, NO_CALLBACK };
TextMenuItem menuAboutText3(&minfoAboutText3, "0.3.1", 5, nullptr, INFO_LOCATION_PGM);
const PROGMEM AnyMenuInfo minfoAboutText2 = { "By Mr258876", 8, 0xffff, 0, NO_CALLBACK };
TextMenuItem menuAboutText2(&minfoAboutText2, "", 1, &menuAboutText3, INFO_LOCATION_PGM);
const PROGMEM AnyMenuInfo minfoAboutText1 = { "Project-Orgel", 7, 0xffff, 0, NO_CALLBACK };
TextMenuItem menuAboutText1(&minfoAboutText1, "", 1, &menuAboutText2, INFO_LOCATION_PGM);
const PROGMEM SubMenuInfo minfoAbout = { "About", 6, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackAbout(&minfoAbout, &menuAboutText1, INFO_LOCATION_PGM);
SubMenuItem menuAbout(&minfoAbout, &menuBackAbout, nullptr, INFO_LOCATION_PGM);
const char enumStrLanguage_0[] PROGMEM = "ENG";
const char enumStrLanguage_1[] PROGMEM = "CHS";
const char* const enumStrLanguage[] PROGMEM  = { enumStrLanguage_0, enumStrLanguage_1 };
const PROGMEM EnumMenuInfo minfoLanguage = { "Language", 24, 7, 1, setLanguage, enumStrLanguage };
EnumMenuItem menuLanguage(&minfoLanguage, 0, &menuAbout, INFO_LOCATION_PGM);
const PROGMEM AnalogMenuInfo minfoCurrent = { "Current", 22, 5, 2047, setCurrent, 0, 1, "mA" };
AnalogMenuItem menuCurrent(&minfoCurrent, 0, nullptr, INFO_LOCATION_PGM);
const PROGMEM AnalogMenuInfo minfoGearTeeth = { "Gear Teeth", 21, 3, 255, setGearTeeth, 0, 1, "" };
AnalogMenuItem menuGearTeeth(&minfoGearTeeth, 0, &menuCurrent, INFO_LOCATION_PGM);
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
const PROGMEM AnyMenuInfo minfoBackToHomepage = { "Back", 20, 0xffff, 0, toHomePage };
ActionMenuItem menuBackToHomepage(&minfoBackToHomepage, &menuPlay, INFO_LOCATION_PGM);

void setupMenu() {
    // First we set up eeprom and authentication (if needed).
    setSizeBasedEEPROMStorageEnabled(false);
    menuMgr.setEepromRef(&glArduinoEeprom);
    // Now add any readonly, non-remote and visible flags.
    menuAboutText1.setReadOnly(true);
    menuAboutText3.setReadOnly(true);
    menuAboutText2.setReadOnly(true);
    menuBPM.setVisible(false);
    menuPlay.setVisible(false);

    // Code generated by plugins and new operators.
    gfx.begin();
    renderer.setUpdatesPerSecond(30);
    switches.init(internalDigitalIo(), SWITCHES_POLL_EVERYTHING, true);
    menuMgr.initForEncoder(&renderer, &menuBackToHomepage, ENCODER_A_Pin, ENCODER_B_Pin, ENCODER_OK_Pin);
}

