#ifndef COMMON_H
#define COMMON_H

// Không include thư viện hệ thống ở đây để tránh conflict

// --- CÁC HẰNG SỐ CỦA BÀN CỜ ---
#define BOARD_SIZE 12  // Kích thước bàn cờ (12x12)
#define CELL_SIZE 40   // Kích thước mỗi ô vuông (40x40 pixel)
#define OFFSET_X 100   // Khoảng cách từ mép trái màn hình đến bàn cờ (pixel)
#define OFFSET_Y 100   // Khoảng cách từ mép trên màn hình đến bàn cờ (pixel)
#define LEFT 3
#define TOP 1

// --- CẤU TRÚC DỮ LIỆU ---
struct _POINT {
    int x, y; // Tọa độ pixel để nhóm View vẽ 
    int c;    // Trạng thái ô cờ: 0 (Trống), -1 (Quân X), 1 (Quân O)
};

// --- BIẾN TOÀN CỤC (Khai báo extern để các file .cpp dùng chung) ---
extern _POINT _A[BOARD_SIZE][BOARD_SIZE]; // Mảng 2 chiều chứa dữ liệu bàn cờ
extern bool _TURN;                        // Lượt đi: true (X), false (O)
extern int _COMMAND;
extern int _X, _Y;

#endif