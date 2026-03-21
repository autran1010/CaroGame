#include "raylib.h"
#include "Model/config.h"
#include "Model/colors.h"
#include "Model/app_settings.h"
#include "Control/menu_data.h"
#include "Control/input_mouse.h"
#include "View/ui_main_menu.h"
#include "View/ui_setting.h"
#include "audio_manager.h"
#include <algorithm>

/*
    File này là nơi chạy chính của chương trình.

    File này làm:
    - Khởi tạo cửa sổ game.
    - Load font.
    - Tạo settings và audio ban đầu.
    - Chạy vòng lặp game chính.
    - Gọi hàm update và draw theo màn hình hiện tại.
    - Giải phóng tài nguyên khi thoát.

    Cách hoạt động:
    - Mỗi frame lấy MouseState từ input_mouse.
    - Update logic trước.
    - Sau đó BeginDrawing() rồi mới vẽ giao diện.
    - currentScreen quyết định đang ở menu chính, settings, play hay about.

    Muốn sửa ở đâu:
    - Muốn đổi luồng chuyển màn hình: sửa switch(currentScreen).
    - Muốn đổi font: sửa LoadFontSafe() hoặc FONT_PATH.
    - Muốn thêm màn hình mới: thêm state và thêm case update/draw.
*/

// Load font an toàn.
// Nếu file font tồn tại thì load font ngoài.
// Nếu không có thì dùng font mặc định của raylib để tránh crash.   
static Font LoadFontSafe(const char* path, int size)
{
    if (FileExists(path))
        return LoadFontEx(path, size, 0, 0);

    return GetFontDefault();
}

// Hàm main điều khiển toàn bộ chương trình.
// Đây là nơi nối các file lại với nhau:
// input -> update logic -> draw giao diện -> giải phóng tài nguyên.

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Quantum Caro");
    SetTargetFPS(TARGET_FPS);

    Font fontTitle = LoadFontSafe(FONT_PATH, 64);
    Font fontSmall = LoadFontSafe(FONT_PATH, 28);

    float hoverAnim[32] = {};
    float clickAnim[32] = {};
    int selectedIndex = 0;

    AppSettings appSettings;
    AudioAssets audio;
    InitGameAudio(audio);

    ScreenState currentScreen = SCREEN_MAIN_MENU;
    bool shouldClose = false;

    while (!WindowShouldClose() && !shouldClose)
    {
        MouseState mouse = GetMouseStateNow();
        float dt = GetFrameTime();

        UpdateGameAudio(audio, appSettings);

        switch (currentScreen)
        {
        case SCREEN_MAIN_MENU:
            UpdateMainMenuUI(
                mouse,
                dt,
                selectedIndex,
                currentScreen,
                hoverAnim,
                clickAnim,
                shouldClose,
                audio,
                appSettings
            );
            break;

        case SCREEN_SETTING:
            UpdateSettingsUI(appSettings, mouse, currentScreen, audio);
            break;

        case SCREEN_PLAY:
        case SCREEN_ABOUT:
            if (mouse.leftPressed)
            {
                currentScreen = SCREEN_MAIN_MENU;
            }
            break;
        }

        BeginDrawing();

        switch (currentScreen)
        {
        case SCREEN_MAIN_MENU:
            DrawMainMenuUI(fontTitle, fontSmall, mouse, hoverAnim, clickAnim);
            break;

        case SCREEN_SETTING:
            DrawSettingsUI(fontTitle, fontSmall, appSettings, mouse);
            break;

        case SCREEN_PLAY:
            ClearBackground(BLACK);
            DrawTextEx(fontTitle, "PLAY MENU - TEMP", Vector2{ 560, 200 }, 44.0f, 2.0f, RAYWHITE);
            DrawTextEx(fontSmall, "click anywhere to go back", Vector2{ 620, 280 }, 24.0f, 1.0f, GRAY);
            break;

        case SCREEN_ABOUT:
            ClearBackground(BLACK);
            DrawTextEx(fontTitle, "CHALLENGE MENU - TEMP", Vector2{ 470, 200 }, 44.0f, 2.0f, RAYWHITE);
            DrawTextEx(fontSmall, "click anywhere to go back", Vector2{ 620, 280 }, 24.0f, 1.0f, GRAY);
            break;
        }

        EndDrawing();
    }

    ShutdownGameAudio(audio);

    if (FileExists(FONT_PATH))
    {
        UnloadFont(fontTitle);
        UnloadFont(fontSmall);
    }

    CloseWindow();
    return 0;
}