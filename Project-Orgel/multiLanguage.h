#ifndef _PROJECT_ORGEL_MULTI_LANGUAGE_
#define _PROJECT_ORGEL_MULTI_LANGUAGE_

#include <Arduino.h>
#include "langdef.h"
#include "lang_en-US.h"
#include "lang_zh-Hans.h"
const PROGMEM char **lang[] = {enUS, zhHans};

#include <tcMenu.h>
// 用于支持多语言的menuinfo子类
struct AnyMenuInfo_ML : AnyMenuInfo {
	AnyMenuInfo_ML(const char *&a, int b, int c, int d, MenuCallbackFn e){
		strcpy(AnyMenuInfo::name, a);
		AnyMenuInfo::id = b;
		AnyMenuInfo::eepromAddr = c;
		AnyMenuInfo::maxValue = d;
		AnyMenuInfo::callback = e;
	}
};

struct AnalogMenuInfo_ML : AnalogMenuInfo {
	AnalogMenuInfo_ML(const char *&a, int b, int c, int d, MenuCallbackFn e, int f, int g, char h[5]){
		strcpy(AnalogMenuInfo::name, a);
		AnalogMenuInfo::id = b;
		AnalogMenuInfo::eepromAddr = c;
		AnalogMenuInfo::maxValue = d;
		AnalogMenuInfo::callback = e;
    AnalogMenuInfo::offset = f;
		AnalogMenuInfo::divisor = g;
		strcpy(AnalogMenuInfo::unitName, h);
	}
};

struct EnumMenuInfo_ML : EnumMenuInfo {
	EnumMenuInfo_ML(const char *&a, int b, int c, int d, MenuCallbackFn e, const char * const *f){
		strcpy(EnumMenuInfo::name, a);
		EnumMenuInfo::id = b;
		EnumMenuInfo::eepromAddr = c;
		EnumMenuInfo::maxValue = d;
	    EnumMenuInfo::callback = e;
        EnumMenuInfo::menuItems = f;
	}
};

struct BooleanMenuInfo_ML : BooleanMenuInfo {
	BooleanMenuInfo_ML(const char *&a, int b, int c, int d, MenuCallbackFn e, BooleanNaming f){
		strcpy(BooleanMenuInfo::name, a);
		BooleanMenuInfo::id = b;
		BooleanMenuInfo::eepromAddr = c;
		BooleanMenuInfo::maxValue = d;
		BooleanMenuInfo::callback = e;
        BooleanMenuInfo::naming = f;
	}
};

struct SubMenuInfo_ML : SubMenuInfo {
	SubMenuInfo_ML(const char *&a, int b, int c, int d, MenuCallbackFn e){
		strcpy(SubMenuInfo::name, a);
		SubMenuInfo::id = b;
		SubMenuInfo::eepromAddr = c;
		SubMenuInfo::maxValue = d;
		SubMenuInfo::callback = e;
	}
};

struct FloatMenuInfo_ML : FloatMenuInfo {
	FloatMenuInfo_ML(const char *&a, int b, int c, int d, MenuCallbackFn e){
		strcpy(FloatMenuInfo::name, a);
		FloatMenuInfo::id = b;
		FloatMenuInfo::eepromAddr = c;
		FloatMenuInfo::numDecimalPlaces = d;
		FloatMenuInfo::callback = e;
	}
};

// 用于支持多语言的菜单项invoke
#define RENDERING_CALLBACK_NAME_INVOKE_ML(fnName, parent, namepgm, eepromPosition, invoke) \
int fnName(RuntimeMenuItem* item, uint8_t row, RenderFnMode mode, char* buffer, int buffSize) { \
	switch(mode) { \
	case RENDERFN_NAME: \
		safeProgCpy(buffer, namepgm, buffSize); \
		return true; \
    case RENDERFN_INVOKE: \
		invokeIfSafe(invoke, item); \
		return true; \
	case RENDERFN_EEPROM_POS: \
		return eepromPosition; \
	default: \
		return parent(item, row, mode, buffer, buffSize); \
	} \
}

#endif
