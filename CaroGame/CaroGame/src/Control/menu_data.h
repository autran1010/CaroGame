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
    BTN_PLAY = 0,
    BTN_ABOUT,
    BTN_SETTING,
    BTN_EXIT
};

// Trạng thái màn hình
enum ScreenState
{
    SCREEN_MAIN_MENU,
    SCREEN_PLAY,
    SCREEN_ABOUT,
    SCREEN_SETTING
};

// Dữ liệu cho các nút trong menu chính
extern NeonButton gButtons[];
// Số lượng nút trong menu
extern int gButtonCount;