#define WIN32_LEAN_AND_MEAN
#define NOGDI              
#define NOUSER

#include "raylib.h"
#include "../include/View.h"
#include "../include/Model.h"
#include "../include/Control.h"
#include "../include/input_mouse.h"

int gameState = 0; // Trạng thái game: 0 là Menu, 1 là đang chơi, 2 là hỏi người chơi có muốn chơi tiếp không
int menuSelected = 0; // Lựa chọn trong menu

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Caro Game - Loi_UI Project");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    StartGame();

    while (!WindowShouldClose())
    {
        MouseState mouse = GetMouseStateNow();
        if (gameState == 0) // Đang ở màn hình chính
        {
            if (IsKeyPressed(KEY_UP)) menuSelected = (menuSelected - 1 + 4) % 4;
            if (IsKeyPressed(KEY_DOWN)) menuSelected = (menuSelected + 1) % 4;

            int hovered = GetMenuOptionFromMouse(mouse);
            if (hovered != -1)
                menuSelected = hovered;

            if (IsKeyPressed(KEY_ENTER))
            {
                if (menuSelected == 0) gameState = 1;
                else if (menuSelected == 3) {
					gameState = 3;
                    break;
                }
            }

            for (int i = 0; i < 4; i++)
            {
                Rectangle buttonRect = { 300.0f, (float)(220 + i * 50), 220.0f, 40.0f };
                if (IsMouseClickedRect(mouse, buttonRect))
                {
                    menuSelected = i;

                    if (i == 0) gameState = 1;
                    else if (i == 3)
                    {
                        gameState = 3;
                        break;
                    }
                }
            }

        }
		else if (gameState == 1)// màn hình chơi game
        {
            if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))  MoveLeft();
            if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) MoveRight();
            if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))    MoveUp();
            if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))  MoveDown();

            UpdateBoardCursorFromMouse(mouse);

            if (IsKeyPressed(KEY_ENTER))
            {
                if (CheckBoard() != 0)
                {
                    int result = TestBoard();
                    if (ProcessFinish(result) != 2)
                    {
                        gameState = 2;
                    }
                }
            }

            if (mouse.leftPressed)
            {
                int row, col;
                if (GetBoardCellFromMouse(mouse, row, col))
                {
                    _ROW = row;
                    _COL = col;
                    _X = 100 + _COL * 30;
                    _Y = 80 + _ROW * 30;

                    if (CheckBoard() != 0)
                    {
                        int result = TestBoard();
                        if (ProcessFinish(result) != 2)
                        {
                            gameState = 2;
                        }
                    }
                }
            }

            if (IsKeyPressed(KEY_ESCAPE)) gameState = 0;
        }
        else if (gameState == 2) {
            int answer = AskContinue(TestBoard()); 
            if (answer == 1) {
                StartGame();
                gameState = 1;
            }
            else if (answer == -1) {
                gameState = 0;
                ResetData(true);
            }
        }
        else if (gameState == 3) {
			CloseWindow();
			return 0;
        }
            // X

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameState == 0)
        {
            DrawMainMenu(menuSelected); 
        }
        else
        {
            DrawBoard(BOARD_SIZE);      // Vẽ lưới & tọa độ
            DrawPieces();       // Vẽ X và O từ mảng _BOARD
            DrawPlayerStats();  // Vẽ bảng điểm bên phải

            // Vẽ con trỏ tại vị trí hiện tại
            DrawRectangleLinesEx({ (float)_X, (float)_Y, 30, 30 }, 3, GREEN);

            DrawText("Di chuyen: WASD | Danh: ENTER | Menu: ESC", 10, 10, 20, DARKGRAY);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}