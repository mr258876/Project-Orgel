#ifndef _UI_H__
#define _UI_H__
#include <U8g2lib.h>

struct playVars {
bool playStatus;
int playBPM;
int motorCurrent;
};

class UI
{
private:
    U8G2 *u8g2;
    static struct playVars *pV;
    static bool redrawRequired;
    bool lastPlayStatus;
public:
    UI(U8G2 *screen, struct playVars *vars);
    ~UI();

    // Loop Function
    void tick();

    // Display Functions
    void init();
    void homePage();

    // Conltol Functions
    static void left();
    static void right();
    void click();
    void doubleClick();
    void hold();
};

#endif
