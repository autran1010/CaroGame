#pragma once
#include "raylib.h"
#include "src/Control/input_mouse.h"
#include "src/Control/menu_data.h"
#include "src/Model/app_settings.h"
#include "src/audio_manager.h"

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