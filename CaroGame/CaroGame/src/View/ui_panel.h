#pragma once
#include "raylib.h"
#include <string>

void DrawNeonPanelFrame(Rectangle outer, Rectangle inner, Color glowColor, Color lineColor);

void DrawInfoCell(Font font, Rectangle rect, const char* left, const char* right, Color accent);

void DrawSectionTitle(Font font, const char* text, Vector2 pos);

void DrawValueBox(Font font, Rectangle rect, const std::string& text, Color accent, bool hovered);

void DrawMainMenuSidePanel(Font fontTitle, Font fontSmall);