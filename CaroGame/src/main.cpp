#include <raylib.h>
#include <iostream>
#include "../include/Common.h"
#include "../include/Model.h"

using namespace std;

// --- HÀM MOCK GIAO DIỆN RAYLIB ĐỂ BẠN TỰ TEST LOGIC ---
int main() {
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Caro Game - Raylib Mock");
    SetTargetFPS(60);

    // Kích thước ô cờ (cell size) tuỳ chỉnh cho khớp màn hình
    float cellSize = (float)(screenWidth - 100) / BOARD_SIZE;
    float offsetX = 50.0f;
    float offsetY = 50.0f;

    // Khởi tạo bàn cờ trắng (Gọi Data.cpp nếu bạn có file Data, nếu không thì ghi đè luôn)
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            _BOARD[i][j] = 0;

    _TURN = true; // Bắt đầu là X
    int gameState = 2; // 2 = Đang chơi

    while (!WindowShouldClose()) {
        // Cập nhật Logic
        if (gameState == 2) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();

                // Xác định click chuột có nằm trong khu vực bàn cờ hay không
                if (mousePos.x >= offsetX && mousePos.x <= offsetX + BOARD_SIZE * cellSize &&
                    mousePos.y >= offsetY && mousePos.y <= offsetY + BOARD_SIZE * cellSize) {

                    int clickedCol = (int)((mousePos.x - offsetX) / cellSize);
                    int clickedRow = (int)((mousePos.y - offsetY) / cellSize);

                    // Đưa tọa độ vào biến toàn cục cho Logic xử lý
                    _COL = clickedCol;
                    _ROW = clickedRow;

                    if (_ROW >= 0 && _ROW < BOARD_SIZE && _COL >= 0 && _COL < BOARD_SIZE) {
                        // 1. Gọi hàm CheckBoard xem có đánh xuống được k (Lấy thẳng _ROW, _COL)
                        int check = CheckBoard();
                        if (check != 0) { // Đánh thành công (Ô trống)
                            // 2. Gọi hàm TestBoard của bạn để phóng tia
                            gameState = TestBoard();

                            // Xong nước đi thì đổi lượt cho người sau
                            if (gameState == 2) {
                                _TURN = !_TURN;
                            }
                        }
                    }
                }
            }
        } else {
            // Nếu game kết thúc, bấm phím ENTER để chơi lại
            if (IsKeyPressed(KEY_ENTER)) {
                for (int i = 0; i < BOARD_SIZE; i++)
                    for (int j = 0; j < BOARD_SIZE; j++)
                        _BOARD[i][j] = 0;
                _TURN = true;
                gameState = 2;
            }
        }

        // Vẽ
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Hiển thị trạng thái
        if (gameState == 2) {
            DrawText(TextFormat("Luot cua: %s", _TURN ? "X" : "O"), 50, 10, 20, DARKGRAY);
            DrawText("Chon o trong de danh co", 50, 30, 15, GRAY);
        } else {
            DrawText("Nhan ENTER de choi lai", 50, 10, 20, RED);
        }

        // Vẽ bàn cờ
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                Rectangle cellRect = { offsetX + j * cellSize, offsetY + i * cellSize, cellSize, cellSize };
                DrawRectangleLinesEx(cellRect, 1.0f, LIGHTGRAY);

                if (_BOARD[i][j] == -1) {
                    DrawText("X", (int)(cellRect.x + cellSize / 3.5), (int)(cellRect.y + cellSize / 8), (int)(cellSize * 0.8), RED);
                } else if (_BOARD[i][j] == 1) {
                    DrawText("O", (int)(cellRect.x + cellSize / 3.5), (int)(cellRect.y + cellSize / 8), (int)(cellSize * 0.8), BLUE);
                }
            }
        }

        // Vẽ thông báo kết thúc
        if (gameState != 2) {
            const char* msg = (gameState == -1) ? "X THANG!" : ((gameState == 1) ? "O THANG!" : "HOA NHAU!");
            int msgWidth = MeasureText(msg, 40);
            DrawRectangle(screenWidth / 2 - msgWidth / 2 - 20, screenHeight / 2 - 30, msgWidth + 40, 60, Fade(BLACK, 0.8f));
            DrawText(msg, screenWidth / 2 - msgWidth / 2, screenHeight / 2 - 20, 40, GREEN);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
