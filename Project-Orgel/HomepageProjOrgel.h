#ifndef _PROJECT_ORGEL_TCMENU_HOME_
#define _PROJECT_ORGEL_TCMENU_HOME_

#include <BaseRenderers.h>
#include "lv_i18n.h"
#include "BLEInterface.h"
#include "u8g2_wqy_14_project_orgel.h"

class HomePageDrawingHandler : public CustomDrawing
{
private:
    bool isPlaying = false;
    uint16_t lastEncVal = 0;
    uint16_t lastBPM = 0;

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
        gfx.setFontPosBaseline();
        switches.changeEncoderPrecision(menuBPM.getMaximumValue(), menuBPM.getCurrentValue());
        isPlaying = menuPlay.getBoolean();
        lastEncVal = menuBPM.getCurrentValue();
        lastBPM = menuBPM.getCurrentValue();
        draw();
    }

    void draw()
    {   
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
            draw();
            ble_notify_bpm();
        }
        // Rotate: change speed
        if (lastEncVal != currentValue)
        {
            menuBPM.setCurrentValue(menuBPM.getCurrentValue() + (currentValue - lastEncVal));
            lastEncVal = currentValue;
            lastBPM = menuBPM.getCurrentValue();
            draw();
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
