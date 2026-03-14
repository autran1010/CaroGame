#pragma once
#include "raylib.h"
#include "Model/app_settings.h"

struct AudioAssets
{
    Music bgMusic{};
    Sound clickSound{};
    Sound hoverSound{};

    bool musicLoaded = false;
    bool clickLoaded = false;
    bool hoverLoaded = false;
};

void InitGameAudio(AudioAssets& audio);
void UpdateGameAudio(AudioAssets& audio, const AppSettings& settings);
void ShutdownGameAudio(AudioAssets& audio);

void PlayMenuClick(AudioAssets& audio, const AppSettings& settings);
void PlayMenuHover(AudioAssets& audio);