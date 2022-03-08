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
			selectSide();
			gameInit();
			
			while (passCnt < 2 && stoneCnt < BOARD_SIZE * BOARD_SIZE - block) {
				possibleCheck();
				boardDisplay();
				xyCoordinate();
				scoreBoard();
				if (std::count(&check[0][0], &check[0][0] + BOARD_SIZE * BOARD_SIZE, true) == 0) {
					pass();
					continue;
				}
				else {
					if ((selection == 1 && turnCnt % 2 == 0) || (selection == 2 && turnCnt % 2 == 1)) {
						putStone();
					}
					else {					
						randomAI();
					}
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