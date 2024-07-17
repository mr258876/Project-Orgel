/*
 * Copyright (c) 2018 https://www.thecoderscorner.com (Dave Cherry).
 *
 * Modified by mr258876 (c) 2024
 *
 * This product is licensed under an Apache license, see the LICENSE file in the top-level directory.
 *
 */

/**
 * @file ssd1306ascii.h
 *
 *  ssd1306ascii renderer that renders menus onto this type of display. This file is a plugin file and should not
 * be directly edited, it will be replaced each time the project is built. If you want to edit this file in place,
 * make sure to rename it first.
 *
 * This plugin allows rendering to the Ssd1306Ascii library. It is a low memory ascii renderer that
 * provides text based functions.
 *
 * LIBRARY REQUIREMENT
 * This renderer is designed for use with this library: https://github.com/mr258876/SSD1306Ascii
 */
/**
 * @history
 *  
 *  @mr258876   Jul 10, 2023    Fixed row height when not using System5x7 for menu items 
 *  @mr258876   Jul 13, 2023    Fill rows as title background, taking advtange of modded library
 *  @mr258876   Jul 17, 2023    i18n support with mr258876/SSD1306Ascii and lvgl/lv_i18n
 */
#ifdef NRF51

#include "ssd1306asciiRenderer.h"
#include "lv_i18n.h"

extern const ConnectorLocalInfo applicationInfo;

SSD1306AsciiRenderer::SSD1306AsciiRenderer(uint8_t dimX, const uint8_t* titleFont, const uint8_t* itemFont) : BaseMenuRenderer(dimX) {
	this->backChar = '<';
	this->forwardChar = '>';
	this->editChar = '=';
	this->ssd1306 = nullptr;
    this->fontTitle = titleFont;
    this->fontItem = itemFont;
}

SSD1306AsciiRenderer::~SSD1306AsciiRenderer() {
    delete this->buffer;
    delete dialog;
}

void SSD1306AsciiRenderer::setEditorChars(char back, char forward, char edit) {
	backChar = back;
	forwardChar = forward;
	editChar = edit;
}

void SSD1306AsciiRenderer::renderList(uint8_t titleRows) {
	auto runList = reinterpret_cast<ListRuntimeMenuItem*>(menuMgr.getCurrentMenu());

	uint8_t maxY = min((ssd1306->displayRows() - titleRows), runList->getNumberOfParts());
	uint8_t currentActive = runList->getActiveIndex();

	uint8_t offset = 0;
	if (currentActive >= maxY) {
		offset = (currentActive+1) - maxY;
	}

	for (int i = 0; i < maxY; i++) {
		uint8_t current = offset + i;
		RuntimeMenuItem* toDraw = (current==0) ? runList->asBackMenu() : runList->getChildItem(current - 1);
		renderMenuItem(i + titleRows, toDraw);
	}

	// reset the list item to a normal list again.
	runList->asParent();
}

void SSD1306AsciiRenderer::renderTitle() {
    size_t bufSz;
    if(menuMgr.getCurrentMenu() == menuMgr.getRoot()) {
        bufSz = safeProgCpy(buffer, applicationInfo.name, bufferSize);
    }
    else {
        bufSz = menuMgr.getCurrentMenu()->copyNameToBuffer(buffer, bufferSize);
    }
    buffer[bufSz] = 0;
    ssd1306->setFont(fontTitle);
    ssd1306->setClearFiller(0xFF);
    ssd1306->clearToEOL();
    ssd1306->setClearFiller(0);
    ssd1306->setInvertMode(true);
    ssd1306->setCursor(0,0);
    // write a space for better looking
    ssd1306->write(' ');
    // write localized title directly
    ssd1306->print(_(buffer));
    ssd1306->setInvertMode(false);
}

void SSD1306AsciiRenderer::render() {
	uint8_t locRedrawMode = redrawMode;
	redrawMode = MENUDRAW_NO_CHANGE;

	countdownToDefaulting();

    ssd1306->setFont(fontTitle);
    int titleRows = ssd1306->fontRows();
	if (locRedrawMode == MENUDRAW_COMPLETE_REDRAW) {
        ssd1306->clear();
		renderTitle();
        taskManager.yieldForMicros(0);
	}

	if (menuMgr.getCurrentMenu()->getMenuType() == MENUTYPE_RUNTIME_LIST ) {
		if (menuMgr.getCurrentMenu()->isChanged() || locRedrawMode != MENUDRAW_NO_CHANGE) {
			renderList(titleRows);
		}
	} else {
        int cnt = titleRows;
		MenuItem* item = menuMgr.getCurrentMenu();

		// first we find the first currently active item in our single linked list
        int activeOffs = offsetOfCurrentActive(item);
        
        ssd1306->setFont(fontItem);
        int rowsAvailable = (ssd1306->displayRows() - titleRows) / ssd1306->fontRows();
		if (activeOffs >= rowsAvailable) {
			uint8_t toOffsetBy = (activeOffs - rowsAvailable) + 1;

			if (lastOffset != toOffsetBy) locRedrawMode = MENUDRAW_COMPLETE_REDRAW;
			lastOffset = toOffsetBy;

			while (item != nullptr && toOffsetBy) {
                if(item->isVisible()) toOffsetBy = toOffsetBy - 1;
				item = item->getNext();
			}
		} else {
			if (lastOffset != 0xff) locRedrawMode = MENUDRAW_COMPLETE_REDRAW;
			lastOffset = 0xff;
		}

		// and then we start drawing items until we run out of screen or items
		while (item && cnt < ssd1306->displayRows()) {
            if(item->isVisible())
            {
                if (locRedrawMode != MENUDRAW_NO_CHANGE || item->isChanged()) {
                    renderMenuItem(cnt, item);
                }
                cnt += ssd1306->fontRows();
            }
			item = item->getNext();
		}
	}
}

uint8_t SSD1306AsciiRenderer::drawMenuCursor(MenuItem* item) {
    if (item->getMenuType() == MENUTYPE_BACK_VALUE) {
		ssd1306->write(item == activeItem ? (char)backChar : ' ');
		ssd1306->write(backChar);
	}
	else {
		ssd1306->write(char(item == menuMgr.getCurrentEditor() ? editChar : (item == activeItem ? forwardChar : ' ')));
	}
    return 0;
}

void SSD1306AsciiRenderer::renderMenuItem(uint8_t row, MenuItem* item) {
	if (item == nullptr || row > ssd1306->displayRows()) return;

	item->setChanged(false);
	ssd1306->setCursor(0, row);

    uint8_t offs = drawMenuCursor(item);

    uint8_t finalPos = 0;
	if (item->getMenuType() == MENUTYPE_BACK_VALUE) {
        uint8_t ret = safeProgCpy(buffer + offs, _("Back"), bufferSize - offs);
        finalPos = ret + offs;
	}
	else {
        finalPos = item->copyNameToBuffer(buffer, offs, bufferSize);
        buffer[finalPos] = 0;
        finalPos = strlcpy(buffer, _(buffer), bufferSize);
	}
    
	// for(uint8_t i = finalPos; i < bufferSize; ++i)  buffer[i] = 32;
	// buffer[bufferSize] = 0;

    ssd1306->setFont(fontItem);
    ssd1306->clearToEOL();
	if (isItemActionable(item)) {
        ssd1306->print(buffer);
        ssd1306->setCol(127 - ssd1306->charWidth(' ') - ssd1306->charWidth(forwardChar));
        ssd1306->write(forwardChar);
    }
	else {
        char sz[20];
        copyMenuItemValue(item, sz, sizeof sz);
        uint8_t count = strlen(sz);
        if(count < 0 || count > bufferSize) {
            return;
        }
        int cpy = (bufferSize - count) - 1;
        
        // print menu name first
        ssd1306->print(buffer);
        auto hints = menuMgr.getEditorHints();
        if(menuMgr.getCurrentEditor() && hints.getEditorRenderingType() != CurrentEditorRenderingHints::EDITOR_REGULAR && item==menuMgr.getCurrentEditor()) {
            int startIndex = min(count, hints.getStartIndex());
            int endIndex = min(count, hints.getEndIndex());
            
            ssd1306->setCol(127 - ssd1306->charWidth(' ') - ssd1306->strWidth(sz));
            //part before hint
            strncpy(buffer, sz, startIndex);
            ssd1306->print(buffer);
            // hint part
            if(startIndex != endIndex) {
                ssd1306->setInvertMode(true);
                strncpy(buffer, &sz[startIndex], endIndex - startIndex);
                buffer[endIndex - startIndex] = 0;
                ssd1306->print(buffer);
                ssd1306->setInvertMode(false);
            }
            // things after hint
            strncpy(buffer, &sz[endIndex], bufferSize);
            buffer[bufferSize-1]=0;
            ssd1306->print(buffer);
        } else {
            // print lozalized value
            strlcpy(buffer, _(sz), bufferSize);
            ssd1306->setCol(127 - ssd1306->charWidth(' ') - ssd1306->strWidth(buffer));
            ssd1306->print(buffer);
        }
    }
}

BaseDialog* SSD1306AsciiRenderer::getDialog() {
    if(dialog == nullptr) {
        dialog = new SSD1306AsciiDialog(this);
    }
    return dialog;
}

// dialog

void SSD1306AsciiDialog::internalRender(int currentValue) {
    SSD1306AsciiRenderer* lcdRender = ((SSD1306AsciiRenderer*)MenuRenderer::getInstance());
    SSD1306Ascii* display = lcdRender->getDisplay();

    if(needsDrawing == MENUDRAW_COMPLETE_REDRAW) {
        display->clear();
    }

    char data[20];
    strncpy_P(data, headerPgm, sizeof(data));
    data[sizeof(data)-1]=0;
    display->setFont(lcdRender->getTitleFont());
    display->setCursor(0,0);
    display->print(data);
    display->setCursor(0, display->fontRows());

    display->setFont(lcdRender->getItemFont());
        display->print(lcdRender->getBuffer());

    if(button1 != BTNTYPE_NONE) {
        copyButtonText(data, 0, currentValue);
        display->setCursor(0, display->displayRows() - display->fontRows());
        display->setInvertMode(currentValue == 0);
        display->print(data);
        display->setInvertMode(false);
    }
    if(button2 != BTNTYPE_NONE) {
        copyButtonText(data, 1, currentValue);
        display->setInvertMode(currentValue == 1);
        int startX = int(lcdRender->getBufferSize() - strlen(data)) * display->fontWidth();
        display->setCursor(startX, display->displayRows() - display->fontRows());
        display->print(data);
        display->setInvertMode(false);
    }
}

#endif