/*
 * Copyright (c) 2018 https://www.thecoderscorner.com (Dave Cherry).
 * This product is licensed under an Apache license, see the LICENSE file in the top-level directory.
 *
 */

/**
 * @file SSD1306UTF8.h
 *
 *  SSD1306UTF8 renderer that renders menus onto this type of display. This file is a plugin file and should not
 * be directly edited, it will be replaced each time the project is built. If you want to edit this file in place,
 * make sure to rename it first.
 *
 * This plugin allows rendering to the SSD1306UTF8 library. It is a low memory ascii renderer that
 * provides text based functions.
 *
 * LIBRARY REQUIREMENT
 * This renderer is designed for use with this library: https://github.com/mr258876/SSD1306UTF8
 */

#ifndef _TCMENU_SSD1306UTF8_DRIVER
#define _TCMENU_SSD1306UTF8_DRIVER

#ifdef NRF51

#include "tcMenu.h"
#include "BaseRenderers.h"
#include <SSD1306UTF8.h>
#include <BaseDialog.h>

/**
 * A renderer that can renderer onto a LiquidCrystal display and supports the concept of single level
 * sub menus, active items and editing.
 */
class SSD1306UTF8Renderer : public BaseMenuRenderer {
private:
	SSD1306UTF8* ssd1306;
	uint8_t backChar;
	uint8_t forwardChar;
	uint8_t editChar;
    const uint8_t* fontTitle;
    const uint8_t* fontItem;
public:

	SSD1306UTF8Renderer(uint8_t dimX, const uint8_t* titleFont, const uint8_t* itemFont);
	~SSD1306UTF8Renderer() override;
	void setGraphicsDevice(SSD1306UTF8* ssd1306) { this->ssd1306 = ssd1306; }

	void render() override;
	void setEditorChars(char back, char forward, char edit);

    SSD1306UTF8* getDisplay() {return ssd1306;}
    BaseDialog* getDialog() override;

    const uint8_t* getItemFont() { return fontItem; }
    const uint8_t* getTitleFont() { return fontTitle; }
private:
    uint8_t drawMenuCursor(MenuItem* item);
    void renderTitle();
	void renderMenuItem(uint8_t row, MenuItem* item);
	void renderList(uint8_t titleHeight);
};

class SSD1306UTF8Dialog : public BaseDialog {
public:
    explicit SSD1306UTF8Dialog(SSD1306UTF8Renderer* renderer) {
        bitWrite(flags, DLG_FLAG_SMALLDISPLAY, 0);
    }
protected:
    void internalRender(int currentValue) override;
};

#endif  // NRF51

#endif // _TCMENU_SSD1306UTF8_DRIVER
