#include "src/Control/menu_data.h"
#include "src/Model/colors.h"

/*
    File này chứa dữ liệu thật của các nút menu chính.

    File này làm:
    - Gán vị trí, kích thước, chữ và màu cho từng nút.
    - Tính số lượng nút hiện có.

    Cách hoạt động:
    - ui_main_menu.cpp sẽ duyệt qua gButtons để update và draw từng nút.

    Muốn sửa ở đâu:
    - Muốn đổi vị trí nút: sửa Rectangle.
    - Muốn đổi chữ trên nút: sửa title.
    - Muốn đổi màu nút: sửa mainColor.
    - Muốn thêm nút mới: thêm một phần tử mới vào gButtons.
*/

// Danh sách các nút đang có ở menu chính.
NeonButton gButtons[] =
{
    { Rectangle{520, 340, 360, 100},  "PLAY",      "", COLOR_NEON_CYAN, BTN_PLAY },
    { Rectangle{1000, 340, 360, 100}, "ABOUT", "", COLOR_NEON_CYAN, BTN_ABOUT },
    { Rectangle{520, 530, 360, 100},  "SETTINGS",  "", COLOR_NEON_CYAN, BTN_SETTING },
    { Rectangle{1000, 530, 360, 100}, "EXIT",      "", COLOR_NEON_PINK, BTN_EXIT }
};

// Tự tính số lượng nút hiện có trong menu.
int gButtonCount = sizeof(gButtons) / sizeof(gButtons[0]);