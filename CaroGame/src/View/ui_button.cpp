#include "ui_button.h"
#include "src/Model/colors.h"
#include "ui_fx.h"
#include <cmath>

/*
    File này dùng để xử lý và vẽ từng button trong menu.

    File này làm:
    - Kiểm tra chuột có hover vào button không.
    - Kiểm tra chuột có click vào button không.
    - Vẽ nền, viền, chữ và hiệu ứng neon cho button.
    - Thêm hiệu ứng khi hover và khi click.

    Cách hoạt động:
    - ui_main_menu.cpp truyền một NeonButton vào đây.
    - File này sẽ dựa vào hoverAnim và clickAnim để quyết định nút sáng bao nhiêu,
      viền mạnh bao nhiêu, có sweep hay scanline hay không.

    Ý nghĩa:
    - Tách riêng cách vẽ button ra khỏi logic màn hình chính.
*/

// Kiểm tra chuột có đang hover lên nút không.
bool IsButtonHovered(const NeonButton& btn, const MouseState& mouse)
{
    return IsMouseOverRect(mouse, btn.rect);
}

// Kiểm tra chuột có click vào nút không.
bool IsButtonClicked(const NeonButton& btn, const MouseState& mouse)
{
    return IsMouseClickedRect(mouse, btn.rect);
}

// Vẽ phần nền của nút.
// Nền sẽ sáng hơn khi hoverAnim tăng.
static void DrawButtonFill(Rectangle rect, Color tint, float hoverAnim)
{
    Color fill1 = Color{
        static_cast<unsigned char>(10 + hoverAnim * 12),
        static_cast<unsigned char>(18 + hoverAnim * 12),
        static_cast<unsigned char>(36 + hoverAnim * 18),
        242
    };

    Color fill2 = Color{
        static_cast<unsigned char>(6 + hoverAnim * 4),
        static_cast<unsigned char>(10 + hoverAnim * 5),
        static_cast<unsigned char>(20 + hoverAnim * 8),
        250
    };

    
    DrawRectangleRounded(rect, 0.02f, 12, fill1);

    Rectangle inner{
        rect.x + 2.0f,
        rect.y + 2.0f,
        rect.width - 4.0f,
        rect.height - 4.0f
    };

    DrawRectangleRounded(inner, 0.02f, 12, fill2);

    DrawRectangleGradientH(
        static_cast<int>(inner.x),
        static_cast<int>(inner.y),
        static_cast<int>(inner.width),
        static_cast<int>(inner.height),
        FadeColorEx(tint, 0.05f + hoverAnim * 0.10f),
        FadeColorEx(BLACK, 0.0f)
    );

    DrawHudPattern(
        Rectangle{ inner.x + 10.0f, inner.y + 10.0f, inner.width - 20.0f, inner.height - 20.0f },
        tint,
        0.04f + hoverAnim * 0.05f,
        12.0f
    );
}

// Vẽ phần viền của nút.
// Hover càng cao thì viền càng sáng, click thì có cảm giác nhấn xuống.
static void DrawButtonFrame(Rectangle rect, Color color, float hoverAnim, float clickAnim)
{
    float outer = 1.5f + hoverAnim * 1.6f + clickAnim * 0.2f;
    float inner = 0.8f + hoverAnim * 0.5f;

    DrawCutCornerFrame(rect, 12.0f, outer, color, 0.82f + hoverAnim * 0.12f);

    Rectangle innerRect{
        rect.x + 5.0f,
        rect.y + 5.0f,
        rect.width - 10.0f,
        rect.height - 10.0f
    };

    DrawCutCornerFrame(innerRect, 8.0f, inner, color, 0.28f + hoverAnim * 0.20f);
    DrawCornerBrackets(rect, color, 0.18f + hoverAnim * 0.35f);
}

// Vẽ chữ chính và chữ phụ của nút.
// ClickAnim làm chữ lệch xuống nhẹ để tạo cảm giác bấm.
static void DrawButtonText(
    const NeonButton& btn,
    Rectangle drawRect,
    float hoverAnim,
    float clickAnim,
    Font fontTitle,
    Font fontSub
)
{
    float titleSize = 24.0f + hoverAnim * 1.6f;
    float subSize = 15.0f + hoverAnim * 0.4f;
    float textX = drawRect.x + 24.0f;
    float titleY = drawRect.y + 18.0f + clickAnim * 2.0f;
    float subY = titleY + 38.0f;

    DrawTextEx(
        fontTitle,
        btn.title.c_str(),
        Vector2{ textX + 2.0f, titleY + 2.0f },
        titleSize,
        1.5f,
        FadeColorEx(btn.mainColor, 0.16f + hoverAnim * 0.16f)
    );

    DrawTextEx(
        fontTitle,
        btn.title.c_str(),
        Vector2{ textX, titleY },
        titleSize,
        1.5f,
        COLOR_TEXT_MAIN
    );

    if (!btn.subtitle.empty())
    {
        DrawTextEx(
            fontSub,
            btn.subtitle.c_str(),
            Vector2{ textX, subY },
            subSize,
            1.2f,
            FadeColorEx(COLOR_TEXT_SUB, 0.72f + hoverAnim * 0.18f)
        );
    }
}

// Vẽ hoàn chỉnh một nút neon.
// Hàm này ghép nền + viền + glow + sweep hover + scanline click + text.
void DrawNeonButton(
    const NeonButton& btn,
    bool forceFocus,
    const MouseState& mouse,
    float hoverAnim,
    float clickAnim,
    Font fontTitle,
    Font fontSub
)
{
    bool hovered = IsButtonHovered(btn, mouse) || forceFocus;

    float pulse = 0.5f + 0.5f * std::sin(static_cast<float>(GetTime()) * 2.4f);
    float pressOffset = clickAnim * 3.5f;

    Rectangle drawRect{
        btn.rect.x,
        btn.rect.y + pressOffset,
        btn.rect.width,
        btn.rect.height
    };

    Color glow = hovered ? AddColor(btn.mainColor, 25) : btn.mainColor;

    DrawGlowRect(drawRect, glow, hovered ? 8 : 5, 0.02f, 3.2f + hoverAnim);
    DrawButtonFill(drawRect, btn.mainColor, hoverAnim);
    DrawButtonFrame(drawRect, btn.mainColor, hoverAnim + pulse * 0.15f, clickAnim);

    DrawRectangleRounded(
        Rectangle{ drawRect.x + 10.0f, drawRect.y + 8.0f, drawRect.width - 20.0f, 7.0f },
        0.5f,
        8,
        FadeColorEx(WHITE, 0.02f + hoverAnim * 0.05f)
    );

    if (hoverAnim > 0.01f)
    {
        float sweepT = std::fmod(static_cast<float>(GetTime()) * 0.85f, 1.0f);
        DrawHoverSweep(drawRect, btn.mainColor, 0.08f + hoverAnim * 0.10f, sweepT);
    }

    if (clickAnim > 0.01f)
    {
        float scanOffset = (1.0f - clickAnim) * drawRect.height;
        DrawScanLines(drawRect, clickAnim * 0.8f, scanOffset);
    }

    DrawButtonText(btn, drawRect, hoverAnim, clickAnim, fontTitle, fontSub);
}