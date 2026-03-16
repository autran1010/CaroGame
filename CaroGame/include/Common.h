#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <Windows.h>
#include <conio.h>

// --- CÁC HẰNG SỐ CỦA BÀN CỜ ---
#define BOARD_SIZE 12  // Kích thước bàn cờ (12x12)
#define CELL_SIZE 40   // Kích thước mỗi ô vuông (40x40 pixel)
#define OFFSET_X 100   // Khoảng cách từ mép trái màn hình đến bàn cờ (pixel)
#define OFFSET_Y 100   // Khoảng cách từ mép trên màn hình đến bàn cờ (pixel)
#define LEFT 3
#define TOP 1

// --- CẤU TRÚC DỮ LIỆU CỦA ĐỘI LOGIC ---
struct _POINT {
    int x, y; // Tọa độ pixel để nhóm View vẽ 
    int c;    // Trạng thái ô cờ: 0 (Trống), -1 (Quân X), 1 (Quân O)
};

// --- BIẾN TOÀN CỤC CHUNG ---
extern char _BOARD[BOARD_SIZE][BOARD_SIZE]; // Mảng trạng thái bàn cờ kéo từ master xuống (Để mảng master không bị lỗi rác)
extern bool _TURN;                          // Lượt đi: true (X), false (O)
extern int _COMMAND;
extern int _X, _Y;
extern int _COL, _ROW;
extern short XScore;
extern short OScore;
extern short NumberOfRounds;

// ------ Cấu trúc lưu trữ tiến trình game (dùng để lưu vào file) ------
#pragma pack(push, 1)
struct Progress
{
    // Thông tin về tên ván chơi (người chơi đặt) và những người chơi
    char gameName[50];
    char playerXName[50];
    char playerOName[50];

    // Thông tin trận đấu
    short playerXScore;
    short playerOScore;
    short numberOfRounds;

    // Trạng thái bàn cờ
    char boardState[BOARD_SIZE][BOARD_SIZE];
    bool isXTurn;
};
#pragma pack(pop) // <--- QUAN TRỌNG: Phải có cái này để trả lại bộ nhớ bình thường

#endif