#pragma once
#include "raylib.h"
#include "src/Control/input_mouse.h"
#include "src/Control/menu_data.h"
#include "src/Model/app_settings.h"
#include "src/audio_manager.h"

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
);

void DrawMainMenuUI(
    Font fontTitle,
    Font fontSmall,
    const MouseState& mouse,
    float hoverAnim[],
    float clickAnim[]
);