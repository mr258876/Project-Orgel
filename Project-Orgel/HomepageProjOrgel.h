#ifndef TCMENU_HOME_PROJ_ORGEL
#define TCMENU_HOME_PROJ_ORGEL

#include <BaseRenderers.h>

class HomePageDrawingHandler : public CustomDrawing
{
public:
    //    virtual ~CustomDrawing() = default;

    void reset() override
    {
        // if we get here the display has been reset because
        // of a timeout of the user interface for example to
        // take over the display
        switches.changeEncoderPrecision(menuBPM.getMaximumValue(), menuBPM.getCurrentValue());
        renderer.takeOverDisplay();
    }

    void started(BaseMenuRenderer *currentRenderer) override
    {
        // take over display has just been called, and we
        // now need to do any initial activity
        gfx.setFontDirection(0);
        gfx.firstPage();
        do
        {
            gfx.setFont(u8g2_font_inr42_mn);
            gfx.setCursor(30, 63);
            gfx.print(menuBPM.getCurrentValue());

            gfx.setFont(u8g2_font_wqy16_t_gb2312a);
            if (menuPlay.getCurrentValue())
            {
                gfx.drawUTF8(0, 14, "正在播放");
            }
            else
            {
                gfx.drawUTF8(0, 14, "已停止");
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
            gfx.drawUTF8(3, 62, "BPM");

        } while (gfx.nextPage());
    }

    void renderLoop(unsigned int currentValue, RenderPressMode userClick) override
    {
        // At this point clicked is the status of the select button
        // it can be RPRESS_NONE, RPRESS_PRESSED or RPRESS_HELD
        // encoderValue is the current value of the rotary encoder
        if (userClick == RPRESS_HELD)
        {
            renderer.giveBackDisplay();
        }
        else if (userClick == RPRESS_PRESSED)
        { 
            menuPlay.setBoolean(!menuPlay.getBoolean());
            reset();
        }
        // for example to update a menu based on current value of the encoder.
        // don't forget you could call changePrecision in started(..)
        if (menuBPM.getCurrentValue() != currentValue)
        {
            menuBPM.setCurrentValue(currentValue);
            reset();
        }
    }
} HomePageDrawingHandler;

void homePage()
{
    renderer.setCustomDrawingHandler(&HomePageDrawingHandler);
    renderer.takeOverDisplay();
}

#endif //TCMENU_HOME_PROJ_ORGEL
