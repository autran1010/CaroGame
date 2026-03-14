#pragma once
#include "raylib.h"

// dữ liệu trạng thái chuột hiện tại
struct MouseState
{
    Vector2 position;
    bool leftPressed;
    bool leftDown;
    bool leftReleased;
};

// Lấy trạng thái chuột hiện tại
MouseState GetMouseStateNow();

// Kiểm tra chuột có đang ở trên hình chữ nhật không
bool IsMouseOverRect(const MouseState& mouse, Rectangle rect);

// Kiểm tra chuột có vừa click vào hình chữ nhật không
bool IsMouseClickedRect(const MouseState& mouse, Rectangle rect);