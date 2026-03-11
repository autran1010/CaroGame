#pragma once
#include "raylib.h"
#include <string>

// Cấu trúc dữ liệu cho một nút trong menu chính
struct NeonButton
{
    Rectangle rect;
    std::string title;
    std::string subtitle;
    Color mainColor;
    int id;
};

// Định danh cho các nút trong menu chính
enum ButtonId
{
    BTN_INSTANT_MATCH = 0,
    BTN_VS_FRIEND,
    BTN_VS_AI,
    BTN_USER_PROFILE,
    BTN_CHALLENGE,
    BTN_CONFIG,
    BTN_EXIT
};

// Trạng thái màn hình
enum ScreenState
{
    SCREEN_MAIN_MENU,
    SCREEN_INSTANT_MATCH,
    SCREEN_VS_FRIEND,
    SCREEN_VS_AI,
    SCREEN_PROFILE,
    SCREEN_CHALLENGE,
    SCREEN_SETTING
};

// Dữ liệu cho các nút trong menu chính
extern NeonButton gButtons[];
// Số lượng nút trong menu
extern int gButtonCount;