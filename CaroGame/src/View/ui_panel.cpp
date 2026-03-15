#include "ui_panel.h"
#include "src/Model/colors.h"
#include "src/View/ui_fx.h"

// Vẽ khung panel ( chỉ cái khung viền bên ngoài )
void DrawNeonPanelFrame(Rectangle outer, Rectangle inner, Color glowColor, Color lineColor)
{
    DrawGlowRect(outer, glowColor, 7, 0.025f, 4.0f);
    DrawRectangleRounded(outer, 0.025f, 12, FadeColorEx(COLOR_PANEL_FILL_1, 0.96f));
    DrawRectangleRounded(inner, 0.025f, 12, FadeColorEx(COLOR_PANEL_FILL_2, 0.98f));

    DrawCutCornerFrame(outer, 14.0f, 2.0f, lineColor, 0.88f);
    DrawCutCornerFrame(inner, 10.0f, 1.0f, COLOR_NEON_CYAN, 0.28f);
}
// Vẽ một ô thông tin với tiêu đề bên trái và giá trị bên phải
void DrawInfoCell(Font font, Rectangle rect, const char* left, const char* right, Color accent)
{
    DrawRectangleRec(rect, FadeColorEx(Color{ 8, 16, 30, 255 }, 0.96f));
    DrawCutCornerFrame(rect, 8.0f, 1.2f, accent, 0.65f);

    DrawTextEx(
        font,
        left,
        Vector2{ rect.x + 12.0f, rect.y + 8.0f },
        17.0f,
        1.0f,
        FadeColorEx(COLOR_TEXT_DIM, 0.95f)
    );

    DrawTextEx(
        font,
        right,
        Vector2{ rect.x + rect.width * 0.50f, rect.y + 8.0f },
        17.0f,
        1.0f,
        FadeColorEx(COLOR_TEXT_MAIN, 0.95f)
    );
}

void DrawSectionTitle(Font font, const char* text, Vector2 pos)
{
    DrawTextEx(font, text, pos, 24.0f, 1.2f, COLOR_TEXT_MAIN);

    DrawLineEx(
        Vector2{ pos.x, pos.y + 30.0f },
        Vector2{ pos.x + 220.0f, pos.y + 30.0f },
        2.0f,
        FadeColorEx(COLOR_NEON_CYAN, 0.55f)
    );
}

void DrawValueBox(Font font, Rectangle rect, const std::string& text, Color accent, bool hovered)
{
    DrawGlowRect(rect, accent, hovered ? 6 : 4, 0.02f, 2.2f);
    DrawRectangleRounded(rect, 0.18f, 10, FadeColorEx(Color{ 8, 16, 30, 255 }, 0.96f));
    DrawCutCornerFrame(rect, 8.0f, 1.4f, accent, hovered ? 0.90f : 0.72f);

    Rectangle inner{ rect.x + 3.0f, rect.y + 3.0f, rect.width - 6.0f, rect.height - 6.0f };
    DrawRectangleRounded(inner, 0.16f, 10, FadeColorEx(Color{ 5, 10, 18, 255 }, 0.98f));

    DrawTextEx(
        font,
        text.c_str(),
        Vector2{ rect.x + 16.0f, rect.y + 8.0f },
        18.0f,
        1.0f,
        COLOR_TEXT_MAIN
    );
}

void DrawMainMenuSidePanel(Font fontTitle, Font fontSmall)
{
    Rectangle outer{ 82, 120, 320, 580 };
    Rectangle inner{ 90, 128, 304, 564 };

    DrawNeonPanelFrame(outer, inner, COLOR_NEON_BLUE, COLOR_PANEL_LINE);

    DrawTextEx(fontTitle, "QUANTUM", Vector2{ 118, 155 }, 42.0f, 2.0f, COLOR_TEXT_MAIN);
    DrawTextEx(fontTitle, "MODES", Vector2{ 140, 208 }, 42.0f, 2.0f, COLOR_TEXT_MAIN);

    DrawLineEx(Vector2{ 115, 285 }, Vector2{ 355, 285 }, 2.0f, FadeColorEx(COLOR_NEON_CYAN, 0.70f));
    DrawLineEx(Vector2{ 115, 292 }, Vector2{ 315, 292 }, 1.0f, FadeColorEx(COLOR_NEON_BLUE, 0.55f));

    DrawTextEx(fontTitle, "X  O  X", Vector2{ 145, 340 }, 28.0f, 4.0f, FadeColorEx(COLOR_NEON_CYAN, 0.95f));
    DrawTextEx(fontTitle, "O  X  O", Vector2{ 145, 381 }, 28.0f, 4.0f, FadeColorEx(COLOR_NEON_PINK, 0.92f));
    DrawTextEx(fontTitle, "X  X  O", Vector2{ 145, 422 }, 28.0f, 4.0f, FadeColorEx(COLOR_NEON_CYAN, 0.95f));

    DrawInfoCell(fontSmall, Rectangle{ 108, 500, 250, 36 }, "SYSTEM", "ONLINE", COLOR_NEON_CYAN);
    DrawInfoCell(fontSmall, Rectangle{ 108, 545, 250, 36 }, "USER", "GUEST-01", COLOR_NEON_BLUE);
    DrawInfoCell(fontSmall, Rectangle{ 108, 590, 250, 36 }, "GRID", "19 x 19", COLOR_NEON_PINK);
    DrawInfoCell(fontSmall, Rectangle{ 108, 635, 250, 36 }, "MODE", "Mouse", COLOR_NEON_CYAN);
}