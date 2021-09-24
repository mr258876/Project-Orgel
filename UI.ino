// OLED - 主页
void homePage()
{
  redrawRequired = false;

  u8g2.setFontDirection(0);
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_inr42_mn);
    u8g2.setCursor(30, 63);
    u8g2.print(playBPM);

    u8g2.setFont(u8g2_font_wqy16_t_gb2312a);
    if (playState)
    {
      u8g2.drawUTF8(0, 14, "正在播放");
    }
    else
    {
      u8g2.drawUTF8(0, 14, "已停止");
    }

    u8g2.setFont(u8g2_font_open_iconic_play_4x_t);
    if (playState)
    {
      u8g2.drawGlyph(0, 50, 0x0045);
    }
    else
    {
      u8g2.drawGlyph(0, 50, 0x0044);
    }

    u8g2.setFont(u8g2_font_profont17_mr);
    u8g2.drawUTF8(3, 62, "BPM");

  } while (u8g2.nextPage());
}

char s;
int value = 0;
byte command = 0;
void CLI()
{
  while (Serial.available() > 0) {
    s = (char)Serial.read();
    switch (s) {
      case 'r':
        command = 1;
        break;
      case 'i':
        command = 2;
        break;
      case 's':
        command = 3;
        break;
      case '\n':
        switch (command) {
          case 1:
            setSpeed(value);
            Serial.print("BPM->");
            break;
          case 2:
            driver.rms_current(value);
            Serial.print("Current->");
            break;
          case 3:
            buttonClick();
            Serial.print("Start/Stop!");
        }
        Serial.println(value);
        command = 0;
        value = 0;
        break;
      default:
        value = value * 10 + (s - '0');
        break;
    }
  }
}
