#include "audio_manager.h"

/*
    File này quản lý âm thanh của chương trình.

    File này làm:
    - Khởi tạo thiết bị âm thanh.
    - Load nhạc nền, click sound, hover sound nếu file tồn tại.
    - Cập nhật volume mỗi frame theo AppSettings.
    - Phát tiếng click và hover.
    - Giải phóng tài nguyên âm thanh khi thoát.

    Cách hoạt động:
    - main.cpp gọi InitGameAudio() lúc bắt đầu.
    - Mỗi frame gọi UpdateGameAudio().
    - File menu và settings gọi PlayMenuClick()/PlayMenuHover() khi có tương tác.
    - Khi thoát gọi ShutdownGameAudio().

    Muốn sửa ở đâu:
    - Muốn đổi file âm thanh: sửa đường dẫn trong InitGameAudio().
    - Muốn đổi cách phát click/hover: sửa PlayMenuClick() hoặc PlayMenuHover().
*/

// Khởi tạo audio device và load các file âm thanh nếu có.
void InitGameAudio(AudioAssets& audio)
{
    InitAudioDevice();

    if (FileExists("assets/audio/menu_music.mp3"))
    {
        audio.bgMusic = LoadMusicStream("assets/audio/menu_music.mp3");
        audio.musicLoaded = true;
        PlayMusicStream(audio.bgMusic);
    }

    if (FileExists("assets/audio/menu_click.ogg"))
    {
        audio.clickSound = LoadSound("assets/audio/menu_click.ogg");
        audio.clickLoaded = true;
    }

    if (FileExists("assets/audio/menu_hover.ogg"))
    {
        audio.hoverSound = LoadSound("assets/audio/menu_hover.ogg");
        audio.hoverLoaded = true;
    }
}

// Cập nhật stream nhạc nền và volume theo settings hiện tại.
void UpdateGameAudio(AudioAssets& audio, const AppSettings& settings)
{
	// Cập nhật âm nhạc nền
    if (audio.musicLoaded)
    {
        UpdateMusicStream(audio.bgMusic);
        SetMusicVolume(audio.bgMusic, settings.musicVolume);
    }
	// Cập nhật âm thanh click
    if (audio.clickLoaded)
    {
        SetSoundVolume(audio.clickSound, settings.sfxVolume);
    }
	// Cập nhật âm thanh hover
	if (audio.hoverLoaded)
    {
        SetSoundVolume(audio.hoverSound, settings.sfxVolume);
    }
}

// Giải phóng tài nguyên âm thanh trước khi thoát chương trình.
void ShutdownGameAudio(AudioAssets& audio)
{
    if (audio.musicLoaded)
    {
        StopMusicStream(audio.bgMusic);
        UnloadMusicStream(audio.bgMusic);
    }

    if (audio.clickLoaded)
    {
        UnloadSound(audio.clickSound);
    }

    CloseAudioDevice();
}

// Phát tiếng click menu nếu settings cho phép và sound đã load.
void PlayMenuClick(AudioAssets& audio, const AppSettings& settings)
{
    if (!settings.menuClickSound) return;
    if (!audio.clickLoaded) return;

    StopSound(audio.clickSound);
    PlaySound(audio.clickSound);
}

// Phát tiếng hover nếu hover sound đã load.
// Có kiểm tra để tránh phát chồng quá nhiều lần liên tục.
void PlayMenuHover(AudioAssets& audio)
{
    if (!audio.hoverLoaded) return;

    if (!IsSoundPlaying(audio.hoverSound))
    {
        PlaySound(audio.hoverSound);
    }
}