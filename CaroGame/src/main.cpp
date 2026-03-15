#include "../include/Common.h"
#include "raylib.h"
#include <iostream>

// --- KHAI BÁO CÁC HÀM TỪ FILE KHÁC ĐỂ MAIN THẤY ---
// (Sau này nhóm làm xong file .h thì bỏ mấy dòng khai báo này đi)
extern void ResetData();
extern int CheckBoard(int pX, int pY);
extern int TestBoard(int lastRow, int lastCol);

// --- HÀM VẼ TẠM THỜI ---
void DrawBoardTemp() {
    for (int i = 0; i <= BOARD_SIZE; i++) {
        DrawLine(OFFSET_X, OFFSET_Y + i * CELL_SIZE, OFFSET_X + BOARD_SIZE * CELL_SIZE, OFFSET_Y + i * CELL_SIZE, BLACK);
        DrawLine(OFFSET_X + i * CELL_SIZE, OFFSET_Y, OFFSET_X + i * CELL_SIZE, OFFSET_Y + BOARD_SIZE * CELL_SIZE, BLACK);
    }
}

void DrawPiecesTemp() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (_A[i][j].c == -1) DrawText("X", _A[i][j].x + 10, _A[i][j].y + 5, 30, RED);
            if (_A[i][j].c == 1)  DrawText("O", _A[i][j].x + 10, _A[i][j].y + 5, 30, BLUE);
        }
    }
}

// --- HÀM MAIN CHÍNH ---
int main() {
    // 1. Khởi tạo cửa sổ Raylib
    InitWindow(600, 600, "Caro - Test Logic - Linh");
    SetTargetFPS(60);

    // 2. Khởi tạo dữ liệu mảng 
    ResetData();

    int winner = 0; // 0: chưa ai thắng, -1: X thắng, 1: O thắng, 2: Hòa

    // 3. Vòng lặp Game
    while (!WindowShouldClose()) {

        // --- XỬ LÝ INPUT VÀ LOGIC ---
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && winner == 0) {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            // Gọi hàm của Linh
            int piece = CheckBoard(mouseX, mouseY);

            if (piece != 0) {
                int col = (mouseX - OFFSET_X) / CELL_SIZE;
                int row = (mouseY - OFFSET_Y) / CELL_SIZE;

                // Gọi hàm Radar của Linh
                winner = TestBoard(row, col);

                if (winner == 0) _TURN = !_TURN; // Đổi lượt nếu chưa ai thắng
            }
        }

        // --- VẼ LÊN MÀN HÌNH ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawBoardTemp();
        DrawPiecesTemp();

        // In thông báo thắng thua
        if (winner == -1) DrawText("X THANG!", 200, 10, 40, RED);
        else if (winner == 1) DrawText("O THANG!", 200, 10, 40, BLUE);
        else if (winner == 2) DrawText("HOA CO!", 200, 10, 40, GRAY);
        else DrawText(_TURN ? "Luot cua X" : "Luot cua O", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}