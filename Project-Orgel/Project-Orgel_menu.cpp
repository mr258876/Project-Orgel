/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#include <tcMenu.h>
#include "Project-Orgel_menu.h"

// Global variable declarations
const PROGMEM  ConnectorLocalInfo applicationInfo = { "Project-Orgel", "b17605de-fb70-4e86-93dc-73130cb2c43e" };
ArduinoEEPROMAbstraction glArduinoEeprom(&EEPROM);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C gfx(U8G2_R0, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE);
U8g2Drawable gfxDrawable(&gfx);
GraphicsDeviceRenderer renderer(30, applicationInfo.name, &gfxDrawable);

// Global Menu Item declarations
RENDERING_CALLBACK_NAME_INVOKE(fnAboutText3RtCall, textItemRenderFn, "Mr258876", -1, NO_CALLBACK)
TextMenuItem menuAboutText3(fnAboutText3RtCall, 8, 1, NULL);
RENDERING_CALLBACK_NAME_INVOKE(fnAboutText2RtCall, textItemRenderFn, "By", -1, NO_CALLBACK)
TextMenuItem menuAboutText2(fnAboutText2RtCall, 23, 1, &menuAboutText3);
RENDERING_CALLBACK_NAME_INVOKE(fnAboutText1RtCall, textItemRenderFn, "Project-Orgel", -1, NO_CALLBACK)
TextMenuItem menuAboutText1(fnAboutText1RtCall, 7, 1, &menuAboutText2);
RENDERING_CALLBACK_NAME_INVOKE(fnAboutRtCall, backSubItemRenderFn, "About", -1, NO_CALLBACK)
const PROGMEM SubMenuInfo minfoAbout = { "About", 6, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackAbout(fnAboutRtCall, &menuAboutText1);
SubMenuItem menuAbout(&minfoAbout, &menuBackAbout, NULL);
const PROGMEM AnalogMenuInfo minfoCurrent = { "Current", 22, 5, 2047, setCurrent, 0, 1, "mA" };
AnalogMenuItem menuCurrent(&minfoCurrent, 0, NULL);
const PROGMEM AnalogMenuInfo minfoGearTeeth = { "Gear Teeth", 21, 3, 255, setGearTeeth, 0, 1, "" };
AnalogMenuItem menuGearTeeth(&minfoGearTeeth, 0, &menuCurrent);
const PROGMEM BooleanMenuInfo minfoDirection = { "Direction", 19, 2, 1, changeMotorDir, NAMING_TRUE_FALSE };
BooleanMenuItem menuDirection(&minfoDirection, false, &menuGearTeeth);
RENDERING_CALLBACK_NAME_INVOKE(fnMotorRtCall, backSubItemRenderFn, "Motor", -1, NO_CALLBACK)
const PROGMEM SubMenuInfo minfoMotor = { "Motor", 4, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackMotor(fnMotorRtCall, &menuDirection);
SubMenuItem menuMotor(&minfoMotor, &menuBackMotor, &menuAbout);
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsRtCall, backSubItemRenderFn, "Settings", -1, NO_CALLBACK)
const PROGMEM SubMenuInfo minfoSettings = { "Settings", 3, 0xffff, 0, NO_CALLBACK };
BackMenuItem menuBackSettings(fnSettingsRtCall, &menuMotor);
SubMenuItem menuSettings(&minfoSettings, &menuBackSettings, NULL);
const PROGMEM AnalogMenuInfo minfoBPM = { "BPM", 2, 0xffff, 511, setSpeed, 0, 1, "" };
AnalogMenuItem menuBPM(&minfoBPM, 0, &menuSettings);
const PROGMEM BooleanMenuInfo minfoPlay = { "play", 1, 0xffff, 1, switchPlayStatus, NAMING_ON_OFF };
BooleanMenuItem menuPlay(&minfoPlay, false, &menuBPM);
const PROGMEM AnyMenuInfo minfoBackToHomepage = { "Back and Save", 20, 0xffff, 0, toHomePage };
ActionMenuItem menuBackToHomepage(&minfoBackToHomepage, &menuPlay);

void setupMenu() {
    // First we set up eeprom and authentication (if needed).
    menuMgr.setEepromRef(&glArduinoEeprom);
    // Now add any readonly, non-remote and visible flags.
    menuAboutText3.setReadOnly(true);
    menuAboutText1.setReadOnly(true);
    menuAboutText2.setReadOnly(true);

    // Code generated by plugins.
    gfx.begin();
    renderer.setUpdatesPerSecond(25);
    switches.initialise(internalDigitalIo(), true);
    menuMgr.initForEncoder(&renderer, &menuBackToHomepage, 34, 35, 32);
}

