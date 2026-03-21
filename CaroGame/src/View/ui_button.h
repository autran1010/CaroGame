#pragma once
#include "raylib.h"
#include "src/Control/menu_data.h"
#include "src/Control/input_mouse.h"

/*
    File này khai báo phần xử lý và vẽ button của menu.

    File này làm:
    - Khai báo hàm kiểm tra hover.
    - Khai báo hàm kiểm tra click.
    - Khai báo hàm vẽ button neon.

    Ý nghĩa:
    - ui_main_menu.cpp chỉ cần gọi các hàm này cho từng button.
*/

// Giao diện vẽ nút trong menu chính
bool IsButtonHovered(const NeonButton& btn, const MouseState& mouse);
// Kiểm tra xem nút có đang được click hay không
bool IsButtonClicked(const NeonButton& btn, const MouseState& mouse);
// Vẽ một nút với hiệu ứng neon, dựa trên trạng thái hover và click
void DrawNeonButton(
    const NeonButton& btn,
    bool forceFocus,
    const MouseState& mouse,
    float hoverAnim,
    float clickAnim,
    Font fontTitle,
    Font fontSub
);