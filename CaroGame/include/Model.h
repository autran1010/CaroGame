#ifndef MODEL_H
#define MODEL_H
#include "Common.h"
#include <vector>

void ResetData(bool resetGame = false);
void SaveGameProgress(const char* filename);
void LoadGameProgress(const char* filename, std::vector<Progress>& history);
void PrintGameHistory();
void GarbageCollect();

/**
 * @brief Kiểm tra trạng thái bàn cờ (thắng, thua, hòa) ngay sau một nước đi.
 * 
 * Sử dụng thuật toán phóng tia từ vị trí hiện tại (_ROW, _COL) theo 4 trục để đếm 
 * số quân cờ cùng màu liên tiếp.
 * @return Giá trị người thắng (-1 cho X, 1 cho O), 0 nếu kết quả là hòa (hết ô), hoặc 2 nếu ván đấu tiếp tục.
 */
int TestBoard();

/**
 * @brief Cố gắng đặt quân cờ xuống bàn dựa trên lượt đi hiện tại (_TURN) và vị trí con trỏ (_ROW, _COL).
 * @return Giá trị quân cờ vừa ghi (-1 cho X, 1 cho O) hoặc 0 nếu không hợp lệ (ô đã có cờ).
 */
int CheckBoard();

#endif
