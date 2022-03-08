#include <iostream>
#include "othello.h"

int main() {
	boardArr[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1] = 2;
	boardArr[BOARD_SIZE / 2][BOARD_SIZE / 2] = 2;
	boardArr[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2] = 1;
	boardArr[BOARD_SIZE / 2][BOARD_SIZE / 2 - 1] = 1;
	int block = 0;

	while (1) {
		int menu;
		init();
		titleDisplay();
		std::cin >> menu;

		switch (menu) {
		case SINGLE:
			gameInit();
			while (passCnt < 2 && stoneCnt < BOARD_SIZE * BOARD_SIZE - block) {
				selectSide();
				if (std::count(&check[0][0], &check[0][0] + BOARD_SIZE * BOARD_SIZE, true) == 0) {
					pass();
					continue;
				}
				else {
					ai();
					putStone();
				}
			}
			boardDisplay();
			xyCoordinate();
			scoreBoard();
			winnerJudge();
			break;

		case MULTI:
			gameInit();
			while (passCnt < 2 && turnCnt < BOARD_SIZE * BOARD_SIZE - 4 - block) {
				possibleCheck();
				boardDisplay();
				xyCoordinate();
				scoreBoard();

				if (std::count(&check[0][0], &check[0][0] + BOARD_SIZE * BOARD_SIZE, true) == 0) {
					pass();
					continue;
				}
				else {
					putStone();
				}
			}
			boardDisplay();
			xyCoordinate();
			scoreBoard();
			winnerJudge();
			break;

		case MAP:
			mapControl();
			break;

		case EXIT:
			return 0;
		}
	}
}