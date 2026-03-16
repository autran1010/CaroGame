#include "../../include/Model.h"

// Hàm phụ trợ: phóng tia kiểm tra 1 hướng (dx, dy)
int CountPieces(int row, int col, int dx, int dy, int& blocks) {
	int current = _BOARD[row][col];
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
		if (_BOARD[r][c] == current) count++;
		// Đụng quân địch -> Tính là 1 đầu bị chặn
		else if (_BOARD[r][c] != 0) {
			blocks++;
			break;
		}
		// Đụng ô trống -> Đường mở, không bị chặn
		else break;
	}
	return count;
}

int TestBoard() {
	int current = _BOARD[_ROW][_COL];
	if (current == 0) return 0;

	// Mảng 4 hướng: Ngang (1,0), Dọc (0,1), Chéo chính (1,1), Chéo phụ (1,-1)
	int directions[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} };

	for (int i = 0; i < 4; i++) {
		int dx = directions[i][0];
		int dy = directions[i][1];

		int blocks1 = 0, blocks2 = 0;

		// Quét tới và quét lùi trên cùng 1 trục từ vị trí (_ROW, _COL)
		int countForward = CountPieces(_ROW, _COL, dx, dy, blocks1);
		int countBackward = CountPieces(_ROW, _COL, -dx, -dy, blocks2);

		int totalCount = 1 + countForward + countBackward;
		int totalBlocks = blocks1 + blocks2;

		// Đủ 5 quân và không bị chặn cả 2 đầu
		if (totalCount >= 5 && totalBlocks < 2) return current; // Trả về người thắng (-1 hoặc 1)
	}

	// Kiểm tra Hòa
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_BOARD[i][j] == 0) return 2; // Vẫn còn ô trống -> Đánh tiếp
		}
	}

	return 0; // Hòa
}

int CheckBoard() // Không cần truyền pX, pY nữa vì đã dùng _ROW, _COL toàn cục
{
	// Kiểm tra xem ô tại vị trí con trỏ hiện tại có trống không
	if (_BOARD[_ROW][_COL] == 0)
	{
		if (_TURN == true)
			_BOARD[_ROW][_COL] = -1; // X đánh
		else
			_BOARD[_ROW][_COL] = 1; // O đánh

		return _BOARD[_ROW][_COL]; // Trả về giá trị vừa đánh (-1 hoặc 1)
	}
	return 0; // Ô đã có quân, không cho đánh
}
