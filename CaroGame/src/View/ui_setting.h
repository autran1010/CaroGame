#pragma once
#include "raylib.h"
#include "src/Control/input_mouse.h"
#include "src/Control/menu_data.h"
#include "src/Model/app_settings.h"
#include "src/audio_manager.h"

/*
    File này khai báo phần điều khiển màn hình settings.

    Có 2 phần chính:
    - UpdateSettingsUI(): xử lý click, kéo slider, bật/tắt toggle.
    - DrawSettingsUI(): vẽ toàn bộ giao diện settings.
*/

void UpdateSettingsUI(
    AppSettings& settings,
    const MouseState& mouse,
    ScreenState& currentScreen,
    AudioAssets& audio
);

void DrawSettingsUI(
    Font fontTitle,
    Font fontSmall,
    const AppSettings& settings,
    const MouseState& mouse
);