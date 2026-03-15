#ifndef MODEL_H
#define MODEL_H
#include "Common.h"

void ResetData();
void GarbageCollect();

/**
 * @brief Kiểm tra trạng thái toàn cục của bàn cờ sau một nước đi.
 *
 * Hàm này quét trên 4 trục (Ngang, Dọc, Chéo chính, Chéo phụ) giao tại vị trí
 * quân cờ vừa đánh để kiểm tra điều kiện thắng (5 quân liên tiếp và không bị chặn 2 đầu).
 * Đồng thời, hàm rà soát toàn bộ bàn cờ xem có ô trống nào còn lại không để thiết lập kết quả hòa.
 *
 * @param lastRow Vị trí hàng của quân cờ ở nước đi cuối cùng.
 * @param lastCol Vị trí cột của quân cờ ở nước đi cuối cùng.
 * @return Giá trị người thắng cuộc (-1 cho X, 1 cho O), 2 nếu kết quả là hòa, hoặc 0 nếu đánh tiếp.
 */
int TestBoard(int lastRow, int lastCol);

/**
 * @brief Đếm số lượng quân cờ liên tiếp trên một hướng chỉ định.
 *
 * Hàm này dùng vòng lặp để đếm số quân cờ cùng màu liên tiếp trên một hướng
 * được xác định bởi vector (dx, dy). Đồng thời đếm số đầu bị chặn bởi mép bàn cờ
 * hoặc quân đối phương.
 *
 * @param row Vị trí hàng của quân cờ đang kiểm tra.
 * @param col Vị trí cột của quân cờ đang kiểm tra.
 * @param dx Bước dịch chuyển theo trục x (cột).
 * @param dy Bước dịch chuyển theo trục y (hàng).
 * @param[out] blocks Biến tham chiếu lưu lại số lượng đầu bị chặn trên hướng này.
 * @return Số quân cờ đếm được liên tục và cùng màu theo hướng (dx, dy).
 */
int CheckBoard(int pX, int pY);

#endif