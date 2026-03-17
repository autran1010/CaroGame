#include "../../include/input_mouse.h"
#include "../../include/Common.h"

MouseState GetMouseStateNow()
{
    MouseState mouse{};
    mouse.position = GetMousePosition();
    mouse.leftPressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    mouse.leftDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    mouse.leftReleased = IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
    return mouse;
}

bool IsMouseOverRect(const MouseState& mouse, Rectangle rect)
{
    return (mouse.position.x >= rect.x &&
        mouse.position.x <= rect.x + rect.width &&
        mouse.position.y >= rect.y &&
        mouse.position.y <= rect.y + rect.height);
}

bool IsMouseClickedRect(const MouseState& mouse, Rectangle rect)
{
    return IsMouseOverRect(mouse, rect) && mouse.leftPressed;
}

bool GetBoardCellFromMouse(const MouseState& mouse, int& row, int& col)
{
    const int startX = 100;
    const int startY = 80;
    const int cellSize = 30;

    float mx = mouse.position.x;
    float my = mouse.position.y;

    if (mx < startX || my < startY) return false;
    if (mx >= startX + BOARD_SIZE * cellSize) return false;
    if (my >= startY + BOARD_SIZE * cellSize) return false;

    col = (int)((mx - startX) / cellSize);
    row = (int)((my - startY) / cellSize);

    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
        return false;

    return true;
}

bool UpdateBoardCursorFromMouse(const MouseState& mouse)
{
    int row, col;
    if (!GetBoardCellFromMouse(mouse, row, col))
        return false;

    _ROW = row;
    _COL = col;
    _X = 100 + _COL * 30;
    _Y = 80 + _ROW * 30;

    return true;
}