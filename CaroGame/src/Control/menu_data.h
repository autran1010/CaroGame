#pragma once
#include "raylib.h"
#include <string>

/*
    File này chứa dữ liệu dùng cho menu chính.

    File này làm:
    - Tạo struct cho nút menu.
    - Định nghĩa id của từng nút.
    - Định nghĩa trạng thái các màn hình.
    - Lưu mảng các nút menu chính.
    - Lưu số lượng nút hiện có.

    File này không làm:
    - Không tự kiểm tra chuột.
    - Không tự vẽ nút.
    - Không tự chuyển màn hình.

    Luồng hoạt động:
    - ui_main_menu.cpp sẽ đọc gButtons để biết có những nút nào.
    - Khi click vào nút, chương trình dựa vào id để biết phải chuyển sang màn hình nào.

    Muốn sửa gì thì sửa ở đâu:
    - Muốn thêm / bớt nút: sửa gButtons.
    - Muốn đổi vị trí nút: sửa rect trong gButtons.
    - Muốn đổi tên nút: sửa title trong gButtons.
*/

// Cấu trúc dữ liệu của một nút menu.
// rect: vùng bấm của nút
// title: chữ chính
// subtitle: chữ phụ
// mainColor: màu nhấn của nút
// id: dùng để phân biệt nút này là PLAY, ABOUT, SETTINGS hay EXIT
struct NeonButton
{
    Rectangle rect;
    std::string title;
    std::string subtitle;
    Color mainColor;
    int id;
};

// Mã định danh của từng nút menu.
enum ButtonId
{
    BTN_PLAY = 0,
    BTN_ABOUT,
    BTN_SETTING,
    BTN_EXIT
};

// Trạng thái màn hình hiện tại của chương trình.
enum ScreenState
{
    SCREEN_MAIN_MENU,
    SCREEN_PLAY,
    SCREEN_ABOUT,
    SCREEN_SETTING
};

// Mảng chứa toàn bộ nút ở menu chính.
extern NeonButton gButtons[];
// Số lượng nút hiện có trong gButtons.
extern int gButtonCount;