#ifndef _PROJECT_ORGEL_TCMENU_HOME_
#define _PROJECT_ORGEL_TCMENU_HOME_

#include <BaseRenderers.h>
#include "lv_i18n.h"
#include "BLEInterface.h"

#ifndef NRF51
#include "u8g2_wqy_14_project_orgel.h"
#else
#include "ssd1306utf8_Ligconsolata.h"
#include "ssd1306utf8_Icon.h"
#include "ssd1306utf8_wqy14.h"
#endif

class HomePageDrawingHandler : public CustomDrawing
{
private:
    bool isPlaying = false;
    uint16_t lastEncVal = 0;
    uint16_t lastBPM = 0;
#if defined(NRF51)
    uint16_t lastDrawedBPM = 0;
#endif

public:
    ~HomePageDrawingHandler() = default;

    void reset() override
    {
        // if we get here the display has been reset because
        // of a timeout of the user interface for example to
        // take over the display
        renderer.takeOverDisplay();
    }

    void started(BaseMenuRenderer *currentRenderer) override
    {
// take over display has just been called, and we
// now need to do any initial activity
#ifndef NRF51
        gfx.setFontPosBaseline();
#else
        oled.clear();
        oled.setCursor(0, 6);
        oled.setFont(System5x7);
        oled.set2X();
        oled.print(_("BPM"));
        oled.set1X();
#endif
        switches.changeEncoderPrecision(menuBPM.getMaximumValue(), menuBPM.getCurrentValue());
        isPlaying = menuPlay.getBoolean();
        lastEncVal = menuBPM.getCurrentValue();
        lastBPM = menuBPM.getCurrentValue();
        draw();
    }

    void draw(bool drawPlayStatus = true, bool drawBPM = true)
    {
#if defined(NRF51)
        if (drawPlayStatus)
        {
            oled.setCursor(0, 0);
            oled.setFont(ssd1306utf8_wqy14);
            oled.clearToEOL();
            if (menuPlay.getCurrentValue())
            {
                oled.println(_("Playing"));
            }
            else
            {
                oled.println(_("Stopped"));
            }

            oled.setCursor(0, 2);
            oled.setFont(ssd1306utf8_Icon);
            if (menuPlay.getCurrentValue())
            {
                oled.write(0x12);
            }
            else
            {
                oled.write(0x11);
            }
        }

        if (drawBPM)
        {
            oled.setCursor(34, 2);

            uint16_t val = menuBPM.getCurrentValue();
            if ((val < 100 && lastDrawedBPM >= 100) || (val < 10 && lastDrawedBPM >= 10))
            {
                oled.clearToEOL();   // Clear only when digit missing
            }
            
            oled.setFont(ssd1306utf8_Ligconsolata);

            oled.print(val);
            lastDrawedBPM = val;
        }
#else
        gfx.setFontDirection(0);
        gfx.firstPage();
        do
        {
            gfx.setFont(u8g2_font_inr42_mn);
            gfx.setCursor(30, 63);
            gfx.print(menuBPM.getCurrentValue());

            gfx.setFont(u8g2_wqy_14_project_orgel);
            if (menuPlay.getCurrentValue())
            {
                gfx.drawUTF8(0, 13, _("Playing"));
            }
            else
            {
                gfx.drawUTF8(0, 13, _("Stopped"));
            }

            gfx.setFont(u8g2_font_open_iconic_play_4x_t);
            if (menuPlay.getCurrentValue())
            {
                gfx.drawGlyph(0, 50, 0x0045);
            }
            else
            {
                gfx.drawGlyph(0, 50, 0x0044);
            }

            gfx.setFont(u8g2_font_profont17_mr);
            gfx.drawUTF8(3, 62, _("BPM"));

        } while (gfx.nextPage());
#endif
    }

    void renderLoop(unsigned int currentValue, RenderPressMode userClick) override
    {
        // Button Hold: go to menu
        if (userClick == RPRESS_HELD)
        {
            renderer.giveBackDisplay();
        }
        // Button Click: switch status
        else if (userClick == RPRESS_PRESSED)
        {
            menuPlay.setBoolean(!menuPlay.getBoolean());
            isPlaying = menuPlay.getBoolean();
            switches.changeEncoderPrecision(menuBPM.getMaximumValue(), currentValue);
            draw(true, false);
            ble_notify_bpm();
        }
        // Rotate: change speed
        if (lastEncVal != currentValue)
        {
            menuBPM.setCurrentValue(menuBPM.getCurrentValue() + (currentValue - lastEncVal));
            lastEncVal = currentValue;
            lastBPM = menuBPM.getCurrentValue();
            draw(false, true);
            ble_notify_bpm();
        }
        // Value changed from BLE
        if (menuBPM.getCurrentValue() != lastBPM || menuPlay.getBoolean() != isPlaying)
        {
            lastBPM = menuBPM.getCurrentValue();
            isPlaying = menuPlay.getBoolean();
            lastEncVal = lastBPM;
            switches.changeEncoderPrecision(menuBPM.getMaximumValue(), lastBPM);
            draw();
            ble_notify_bpm();
        }
    }
};

static HomePageDrawingHandler homePageDrawingHandler;

void homePage()
{
    renderer.setCustomDrawingHandler(&homePageDrawingHandler);
    renderer.takeOverDisplay();
}

#endif // TCMENU_HOME_PROJ_ORGEL
