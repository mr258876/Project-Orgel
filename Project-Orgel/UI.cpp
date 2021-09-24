#include "UI.h"

// 定义静态变量
playVars* UI::pV = nullptr;
bool UI::redrawRequired = true;

UI::UI(U8G2 *screen, struct playVars *vars) {
  u8g2 = screen;
  pV = vars;
}


UI::~UI()
{
}


void UI::tick(){
  if (pV->playStatus != lastPlayStatus){
    redrawRequired = true;
    lastPlayStatus = pV->playStatus;
  }
  if (redrawRequired){
    homePage();
    redrawRequired = !redrawRequired;
  }
}


void UI::init(){
  lastPlayStatus = pV->playStatus;
  homePage();
}

// Diaplay - home page
void UI::homePage()
{
  u8g2 -> setFontDirection(0);
  u8g2 -> firstPage();
  do
  {
    u8g2 -> setFont(u8g2_font_inr42_mn);
    u8g2 -> setCursor(30, 63);
    u8g2 -> print(pV -> playBPM);

    u8g2 -> setFont(u8g2_font_wqy16_t_gb2312a);
    if (pV -> playStatus)
    {
      u8g2 -> drawUTF8(0, 14, "正在播放");
    }
    else
    {
      u8g2 -> drawUTF8(0, 14, "已停止");
    }

    u8g2 -> setFont(u8g2_font_open_iconic_play_4x_t);
    if (pV -> playStatus)
    {
      u8g2 -> drawGlyph(0, 50, 0x0045);
    }
    else
    {
      u8g2 -> drawGlyph(0, 50, 0x0044);
    }

    u8g2 -> setFont(u8g2_font_profont17_mr);
    u8g2 -> drawUTF8(3, 62, "BPM");

  } while (u8g2 -> nextPage());
}

void UI::left() {
  redrawRequired = true;
  pV->playBPM--;
}


void UI::right() {
  redrawRequired = true;
  pV->playBPM++;
}


void UI::click(){

}


void UI::doubleClick(){

}


void UI::hold(){

}
