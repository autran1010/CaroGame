#include "../../include/Model.h"

// ĐỊNH NGHĨA BIẾN TOÀN CỤC TẠI ĐÂY (Chỉ 1 lần duy nhất)
_POINT _A[BOARD_SIZE][BOARD_SIZE];
bool _TURN;
int _COMMAND;
int _X, _Y;

void ResetData() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            _A[i][j].x = OFFSET_X + j * CELL_SIZE;
            _A[i][j].y = OFFSET_Y + i * CELL_SIZE;
            _A[i][j].c = 0;
        }
    }
    _TURN = true; // X đi trước
}

void GarbageCollect() {
    // Dọn dẹp tài nguyên nếu có khai báo con trỏ
}