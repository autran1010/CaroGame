#pragma once
#include "raylib.h"
#include "src/Control/input_mouse.h"
#include "src/Control/menu_data.h"
#include "src/Model/app_settings.h"
#include "src/audio_manager.h"

/*
    File này khai báo phần điều khiển menu chính.

    Có 2 phần chính:
    - UpdateMainMenuUI(): xử lý tương tác và animation.
    - DrawMainMenuUI(): vẽ giao diện menu chính.

    Ý nghĩa:
    - Tách update và draw để code dễ đọc hơn.
*/

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