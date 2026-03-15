#ifndef VIEW_H
#define VIEW_H
#include "Common.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

void FixConsoleWindow();
void GotoXY(int x, int y);
void DrawBoard(int pSize);
int ProcessFinish(int pWhoWin);
int AskContinue();

#endif