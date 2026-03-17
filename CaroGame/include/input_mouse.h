#pragma once
#include "raylib.h"

struct MouseState
{
    Vector2 position;
    bool leftPressed;
    bool leftDown;
    bool leftReleased;
};

MouseState GetMouseStateNow();
bool IsMouseOverRect(const MouseState& mouse, Rectangle rect);
bool IsMouseClickedRect(const MouseState& mouse, Rectangle rect);

bool GetBoardCellFromMouse(const MouseState& mouse, int& row, int& col);
bool UpdateBoardCursorFromMouse(const MouseState& mouse);