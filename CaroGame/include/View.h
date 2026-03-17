#pragma once
#include "Common.h"
#include "input_mouse.h"

void FixConsoleWindow();
void GotoXY(int x, int y);
void DrawBoard(int pSize);
int ProcessFinish(int pWhoWin);
int AskContinue(int pWhoWin);
void DrawMainMenu(int selectedOption);
void DrawPlayerStats();
void DrawPieces();
int GetMenuOptionFromMouse(const MouseState& mouse);