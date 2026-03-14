#include "src/Control/menu_data.h"
#include "src/Model/colors.h"

NeonButton gButtons[] =
{
    { Rectangle{520, 340, 360, 100},  "PLAY",      "", COLOR_NEON_CYAN, BTN_PLAY },
    { Rectangle{1000, 340, 360, 100}, "ABOUT", "", COLOR_NEON_CYAN, BTN_ABOUT },
    { Rectangle{520, 530, 360, 100},  "SETTINGS",  "", COLOR_NEON_CYAN, BTN_SETTING },
    { Rectangle{1000, 530, 360, 100}, "EXIT",      "", COLOR_NEON_PINK, BTN_EXIT }
};

int gButtonCount = sizeof(gButtons) / sizeof(gButtons[0]);