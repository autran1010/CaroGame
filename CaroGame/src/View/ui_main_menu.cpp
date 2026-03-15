#include "ui_main_menu.h"
#include "src/View/ui_background.h"
#include "src/View/ui_button.h"
#include "src/View/ui_panel.h"
#include "src/View/ui_fx.h"
#include "src/Model/colors.h"
#include "src/audio_manager.h"
#include <algorithm>

static bool gWasHover[32] = {};

void UpdateMainMenuUI(
    const MouseState& mouse,
    float dt,
    int& selectedIndex,
    ScreenState& currentScreen,
    float hoverAnim[],
    float clickAnim[],
    bool& shouldClose,
    AudioAssets& audio,
    const AppSettings& settings
)
{
    for (int i = 0; i < gButtonCount; ++i)
    {
        bool mouseHover = IsButtonHovered(gButtons[i], mouse);

        if (mouseHover && !gWasHover[i])
        {
            PlayMenuHover(audio);
        }

        gWasHover[i] = mouseHover;


        float target = mouseHover ? 1.0f : 0.0f;
        float speed = mouseHover ? 8.5f : 6.0f;

        hoverAnim[i] += (target - hoverAnim[i]) * std::min(1.0f, dt * speed);

        if (IsButtonClicked(gButtons[i], mouse))
        {
            clickAnim[i] = 1.0f;
            selectedIndex = i;
            PlayMenuClick(audio, settings);

            switch (gButtons[i].id)
            {
            case BTN_PLAY:
                currentScreen = SCREEN_PLAY;
                break;
            case BTN_ABOUT:
                currentScreen = SCREEN_ABOUT;
                break;
            case BTN_SETTING:
                currentScreen = SCREEN_SETTING;
                break;
            case BTN_EXIT:
                shouldClose = true;
                break;
            }
        }

        clickAnim[i] = std::max(0.0f, clickAnim[i] - dt * 3.8f);
    }
}

void DrawMainMenuUI(
    Font fontTitle,
    Font fontSmall,
    const MouseState& mouse,
    float hoverAnim[],
    float clickAnim[]
)
{
    DrawBackgroundScene();
    DrawMainMenuSidePanel(fontTitle, fontSmall);

    DrawTextEx(fontTitle, "QUANTUM CARO:", Vector2{ 500, 92 }, 44.0f, 2.0f, COLOR_TEXT_MAIN);
    DrawTextEx(fontTitle, "PROTOCOL 5", Vector2{ 900, 92 }, 44.0f, 2.0f, COLOR_TEXT_MAIN);
    DrawTextEx(fontSmall, "X O X X O", Vector2{ 810, 152 }, 24.0f, 4.0f, FadeColorEx(COLOR_NEON_CYAN, 0.9f));

    for (int i = 0; i < gButtonCount; ++i)
    {
        DrawNeonButton(
            gButtons[i],
            false,
            mouse,
            hoverAnim[i],
            clickAnim[i],
            fontTitle,
            fontSmall
        );
    }
}