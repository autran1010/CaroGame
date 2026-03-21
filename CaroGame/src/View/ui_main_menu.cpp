#include "ui_main_menu.h"
#include "src/View/ui_background.h"
#include "src/View/ui_button.h"
#include "src/View/ui_panel.h"
#include "src/View/ui_fx.h"
#include "src/Model/colors.h"
#include "src/audio_manager.h"
#include <algorithm>

/*
    File này điều khiển toàn bộ màn hình menu chính.

    File này làm:
    - Kiểm tra hover và click của từng nút.
    - Phát âm thanh hover và click.
    - Cập nhật animation hover/click.
    - Chuyển màn hình khi bấm nút.
    - Vẽ nền, panel trái, tiêu đề và toàn bộ button.

    Cách hoạt động:
    - UpdateMainMenuUI() duyệt qua tất cả gButtons.
    - Nếu chuột mới đi vào nút thì phát hover sound.
    - Nếu click vào nút thì phát click sound và đổi màn hình.
    - DrawMainMenuUI() chỉ lo phần hiển thị.

    Muốn sửa ở đâu:
    - Muốn đổi hành vi khi bấm nút: sửa switch trong UpdateMainMenuUI().
    - Muốn đổi cách vẽ menu chính: sửa DrawMainMenuUI().
*/

// Lưu trạng thái hover của từng nút ở frame trước.
// Mục đích: chỉ phát tiếng hover 1 lần khi chuột vừa đi vào nút.
static bool gWasHover[32] = {};

// Xử lý logic của menu chính.
// Duyệt từng nút để kiểm tra hover/click, cập nhật animation,
// phát âm thanh và chuyển currentScreen khi cần.
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

// Vẽ toàn bộ menu chính.
// Gồm background, panel trái, tiêu đề game và danh sách nút.
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