/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
 */

#ifndef MENU_GENERATED_CODE_H
#define MENU_GENERATED_CODE_H

#include <Arduino.h>
#include <tcMenu.h>
#include "tcMenuU8g2.h"
#include <RuntimeMenuItem.h>
#include <IoAbstraction.h>
#include <ArduinoEEPROMAbstraction.h>

// variables we declare that you may need to access
extern const PROGMEM ConnectorLocalInfo applicationInfo;
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C gfx;
extern GraphicsDeviceRenderer renderer;

// Any externals needed by IO expanders, EEPROMs etc


// Global Menu Item exports
extern ActionMenuItem menuBackToHomepage;
extern TextMenuItem menuAboutText4;
extern TextMenuItem menuAboutText3;
extern TextMenuItem menuAboutText2;
extern TextMenuItem menuAboutText1;
extern BackMenuItem menuBackAbout;
extern SubMenuItem menuAbout;
extern BackMenuItem menuBackWireless;
extern SubMenuItem menuWireless;
extern BooleanMenuItem menuStandbyPowerDown;
extern BooleanMenuItem menuCurrentAutoOptimize;
extern BackMenuItem menuBackCurrent;
extern SubMenuItem menuCurrent;
extern AnalogMenuItem menuDriveRatio;
extern TextMenuItem menuGearText2;
extern TextMenuItem menuGearText1;
extern BackMenuItem menuBackGearSettings;
extern SubMenuItem menuGearSettings;
extern BooleanMenuItem menuDirection;
extern BackMenuItem menuBackMotorStatus;
extern SubMenuItem menuMotorStatus;
extern BackMenuItem menuBackMotor;
extern SubMenuItem menuMotor;
extern BackMenuItem menuBackSettings;
extern SubMenuItem menuSettings;
extern AnalogMenuItem menuBPM;
extern BooleanMenuItem menuPlay;
extern ActionMenuItem menuBackToHomepage;

// Provide a wrapper to get hold of the root menu item and export setupMenu
inline MenuItem& rootMenuItem() { return menuBackToHomepage; }
void setupMenu();

// Callback functions must always include CALLBACK_FUNCTION after the return type
#define CALLBACK_FUNCTION

void CALLBACK_FUNCTION changeMotorDir(int id);
void CALLBACK_FUNCTION setSpeed(int id);
void CALLBACK_FUNCTION switchCurrentAutoOptimize(int id);
void CALLBACK_FUNCTION switchPlayStatus(int id);
void CALLBACK_FUNCTION switchStandbyPowerDown(int id);
void CALLBACK_FUNCTION toHomePage(int id);

#endif // MENU_GENERATED_CODE_H
