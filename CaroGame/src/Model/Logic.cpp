#include "../../include/Model.h"



int CountPieces(int row, int col, int dx, int dy, int& blocks) {
	int current = _A[row][col].c;
	int count = 0;
	blocks = 0;

	for (int step = 1; step <= 5; step++) {
		int r = row + step * dy;
		int c = col + step * dx;

		// Nếu đụng vách bàn cờ -> Tính là 1 đầu bị chặn
		if (r < 0 || r >= BOARD_SIZE || c < 0 || c >= BOARD_SIZE) {
			blocks++;
			break;
		}

		// Đếm quân cùng màu
		if (_A[r][c].c == current) count++;
		// Đụng quân địch -> Tính là 1 đầu bị chặn
		else if (_A[r][c].c != 0) {
			blocks++;
			break;
		}
		// Đụng ô trống -> Đường mở, không bị chặn
		else break;
	}
	return count;
} 


int TestBoard(int lastRow, int lastCol) {
	if (lastRow < 0 || lastCol < 0) return 0;

	int current = _A[lastRow][lastCol].c;
	if (current == 0) return 0;

	// Mảng 4 hướng: Ngang (1,0), Dọc (0,1), Chéo chính (1,1), Chéo phụ (1,-1)
	int directions[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} };

	for (int i = 0; i < 4; i++) {
		int dx = directions[i][0];
		int dy = directions[i][1];

		int blocks1 = 0, blocks2 = 0;
		
		// Quét tới và quét lùi trên cùng 1 trục
		int countForward = CountPieces(lastRow, lastCol, dx, dy, blocks1);
		int countBackward = CountPieces(lastRow, lastCol, -dx, -dy, blocks2);

		int totalCount = 1 + countForward + countBackward;
		int totalBlocks = blocks1 + blocks2;

		//Đủ 5 quân và không bị chặn cả 2 đầu
		if (totalCount >= 5 && totalBlocks < 2) return current; // Trả về người thắng (-1 hoặc 1)
	}

	// Kiểm tra Hòa
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].c == 0) return 0; // Vẫn còn ô trống -> Đánh tiếp
		}
	}

	return 2; // Hòa

}

/**
 * @brief Kiểm tra và cập nhật quân cờ dựa trên vị trí chuột trên màn hình.
 * 
 * Nhận tọa độ X và Y của màn hình (thường là từ cú click chuột), phân tích 
 * độ lệch (offset) để tính toán ra vị trí ô cờ trên lưới tọa độ mảng 2 chiều.
 * Nếu hợp lệ và ô trống, tiến hành điền giá trị cho người chơi hiện tại trên mảng.
 * 
 * @param pX Tọa độ trục X trên màn hình (pixel).
 * @param pY Tọa độ trục Y trên màn hình (pixel).
 * @return Giá trị quân cờ vừa ghi (-1 cho X, 1 cho O) hoặc 0 nếu không hợp lệ (click ngoài bàn cờ, ô đã có cờ).
 */
int CheckBoard(int pX, int pY) {

	// 1. Tính toán vị trí cột (j) và dòng (i) dựa trên tọa độ pixel của chuột
	int row = (pY - OFFSET_Y) / CELL_SIZE;
	int col = (pX - OFFSET_X) / CELL_SIZE;
	
	// 2. Kiểm tra click có nằm TRONG giới hạn bàn cờ không
	if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
		// 3. Kiểm tra ô đó đã có người đánh chưa
		if (_A[row][col].c == 0) {
			_A[row][col].c = _TURN ? -1 : 1; // Đánh dấu quân cờ
			return _A[row][col].c; // Trả về giá trị quân cờ vừa đánh
		}
	}

	// Nếu click ra ngoài bàn cờ hoặc click vào ô đã đánh
	return 0;
}