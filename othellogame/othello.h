#pragma once
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include "stdlib.h" 
#include <cstdlib>
#include <ctime>
#define BOARD_SIZE 8 // 가로 및 세로 칸수

enum { SINGLE = 1, MULTI, MAP, EXIT };

int boardArr[BOARD_SIZE][BOARD_SIZE];
bool check[BOARD_SIZE][BOARD_SIZE] = { false };
int turnCnt = 0;
int passCnt = 0;
int stoneCnt = 4;
int winner = 0;
int block = 0;
int selection = 0;


int dx[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
int dy[8] = { 1, 0, -1, 1, -1, -1, 0, 1 }; //탐색할 방향(가로, 세로, 대각선)


//콘솔 창 크기 설정
void init() {
	system("mode con cols=72 lines=20 | title OTHELLO");
	turnCnt = 0;
	passCnt = 0;
}
void gameInit() {
	system("mode con cols=37 lines=40 | title OTHELLO");
	boardArr[BOARD_SIZE][BOARD_SIZE] = { 0 };
	boardArr[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1] = 2;
	boardArr[BOARD_SIZE / 2][BOARD_SIZE / 2] = 2;
	boardArr[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2] = 1;
	boardArr[BOARD_SIZE / 2][BOARD_SIZE / 2 - 1] = 1;
}
// 게임 제목, 메뉴 출력
void titleDisplay() {
	std::cout << "   .aMMMb   dMMMMMMP    dMP dMP     dMMMMMP    dMP      dMP     .aMMMb " << std::endl;
	std::cout << "  dMP'dMP     dMP      dMP dMP     dMP        dMP      dMP     dMP'dMP " << std::endl;
	std::cout << " dMP dMP     dMP      dMMMMMP     dMMMP      dMP      dMP     dMP dMP  " << std::endl;
	std::cout << "dMP.aMP     dMP      dMP dMP     dMP        dMP      dMP     dMP.aMP   " << std::endl;
	std::cout << "VMMMP'     dMP      dMP dMP     dMMMMMP    dMMMMMP  dMMMMMP  VMMMP'    " << std::endl;
	std::cout << "========================================================================" << std::endl;
	std::cout << "||    1 싱글 모드     2 멀티 모드     3 장애물 설정     4 게임 종료   ||" << std::endl;
	std::cout << "========================================================================" << std::endl;
}

//콘솔의 커서 위치 변경
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}
//싱글플레이 시 돌 색깔 선택
void selectSide() {
	std::cout << "선공/후공을 선택하세요(선공 : 1 후공 : 2)" << std::endl;
	std::cin >> selection;
}

//싱글플레이 시 랜덤배치하는 컴퓨터
void randomAI() {
	Sleep(5000);
	int possibleCnt = 0;
	int possibleArr[BOARD_SIZE * BOARD_SIZE][2];
	int r, c;
	if (selection == 2 && turnCnt % 2 == 0) { //player: 후공, 컴퓨터: 선공
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (check[i][j] == true) {
					possibleArr[possibleCnt][0] = i;
					possibleArr[possibleCnt][1] = j;
					possibleCnt += 1;
				}
			}
		}
	}
	if (selection == 1 && turnCnt % 2 == 1) { //player: 선공, 컴퓨터: 후공
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (check[i][j] == true) {
					possibleArr[possibleCnt][0] = i;
					possibleArr[possibleCnt][1] = j;
					possibleCnt += 1;
				}
			}
		}
	}
	std::srand((unsigned int)std::time(NULL));
	int tmp = rand() % std::count(&check[0][0], &check[0][0] + BOARD_SIZE * BOARD_SIZE, true);
	r = possibleArr[tmp][0];
	c = possibleArr[tmp][1];

	for (int i = 0; i < 8; i++) {
		int nx = r + dx[i];
		int ny = c + dy[i];
		if (nx >= BOARD_SIZE || nx < 0 || ny >= BOARD_SIZE || ny < 0 || boardArr[nx][ny] == 3) {
			continue;
		}
		if (turnCnt % 2 == 0 && boardArr[nx][ny] == 2) { // 흑차례일때
			while (nx + dx[i] < BOARD_SIZE &&
				ny + dy[i] < BOARD_SIZE &&
				nx + dx[i] >= 0 &&
				ny + dy[i] >= 0 &&
				boardArr[nx + dx[i]][ny + dy[i]] != 3) {
				nx += dx[i];
				ny += dy[i];
				if (boardArr[nx][ny] != 2) {
					break;
				}
			}
			if (boardArr[nx][ny] == 1) {
				while (1) {
					boardArr[nx][ny] = 1;
					if (nx == r && ny == c) {
						boardArr[r][c] = 4;
						break;
					}
					nx -= dx[i];
					ny -= dy[i];
				}
			}
		}
		if (turnCnt % 2 == 1 && boardArr[nx][ny] == 1) { // 백차례일때
			while (nx + dx[i] < BOARD_SIZE &&
				ny + dy[i] < BOARD_SIZE &&
				nx + dx[i] >= 0 &&
				ny + dy[i] >= 0 &&
				boardArr[nx + dx[i]][ny + dy[i]] != 3) {
				nx += dx[i];
				ny += dy[i];
				if (boardArr[nx][ny] != 1) {
					break;
				}
			}
			if (boardArr[nx][ny] == 2) {
				while (1) {
					boardArr[nx][ny] = 2;
					if (nx == r && ny == c) {
						boardArr[r][c] = 5;
						break;
					}
					nx -= dx[i];
					ny -= dy[i];
				}
			}
		}
	}
	passCnt = 0;
	turnCnt++;
	stoneCnt++;
}


//패스
void pass() {
	passCnt++;
	turnCnt++;
}

//지형 갯수를 변경하는 함수
void mapControl() {
	std::cout << "원하는 장애물의 갯수를 입력하세요" << std::endl;
	std::cin >> block;
	if ((block <= BOARD_SIZE * BOARD_SIZE - 4) && (block >= 0)) {
		int tmp = block;
		std::srand((unsigned int)std::time(NULL));
		int a, b;

		while (tmp > 0) {
			a = rand() % BOARD_SIZE;
			b = rand() % BOARD_SIZE;
			if ((a == BOARD_SIZE / 2 && b == BOARD_SIZE / 2) ||
				(a == BOARD_SIZE / 2 - 1 && b == BOARD_SIZE / 2) ||
				(a == BOARD_SIZE / 2 && b == BOARD_SIZE / 2 - 1) ||
				(a == BOARD_SIZE / 2 - 1 && b == BOARD_SIZE / 2 - 1)) {
				continue; //시작할 때 돌이 있는 네 칸에는 장애물이 올수없음
			}
			if (boardArr[a][b] != 3) { //중복된 좌표는 세지않음
				boardArr[a][b] = 3;
				tmp--;
			}
		}
	}
}

//게임판을 그리는 함수
void boardDisplay() {
	system("cls");
	for (int i = 1; i < BOARD_SIZE * 2 + 2; i++) {
		for (int j = 1; j < BOARD_SIZE * 2 + 2; j++) {
			if (i == 1) {
				if (j == 1) {
					std::cout << "┌";
				}
				else if (j == BOARD_SIZE * 2 + 1) {
					std::cout << "┐" << std::endl;
				}
				else if (j % 2 == 0) {
					std::cout << "───";
				}
				else {
					std::cout << "┬";
				}
			}
			else if (i == BOARD_SIZE * 2 + 1) {
				if (j == 1) {
					std::cout << "└";
				}
				else if (j == BOARD_SIZE * 2 + 1) {
					std::cout << "┘" << std::endl;
				}
				else if (j % 2 == 0) {
					std::cout << "───";
				}
				else {
					std::cout << "┴";
				}
			}
			else {
				if (i % 2 == 1) {
					if (j == 1) {
						std::cout << "├";
					}
					else if (j == BOARD_SIZE * 2 + 1) {
						std::cout << "┤" << std::endl;
					}
					else if (j % 2 == 0) {
						std::cout << "───";
					}
					else {
						std::cout << "┼";
					}
				}
				else {
					if (j == BOARD_SIZE * 2 + 1) {
						std::cout << "│" << std::endl;
					}
					else if (j % 2 == 0) {
						if (check[i / 2 - 1][j / 2 - 1] == true) {
							std::cout << " ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); //파란색
							std::cout << "※"; // 돌을 놓을 수 있는 곳 표시
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						}
						else {
							if (boardArr[i / 2 - 1][j / 2 - 1] == 0) {
								std::cout << "   "; // 아무것도 없으면(0) 공백 출력
							}
							else if (boardArr[i / 2 - 1][j / 2 - 1] == 1) {
								std::cout << " ○"; // 검은 돌이 있으면(1) 검은 돌 출력
							}
							else if (boardArr[i / 2 - 1][j / 2 - 1] == 2) {
								std::cout << " ●"; // 흰 돌이 있으면(2) 흰 돌 출력
							}
							else if (boardArr[i / 2 - 1][j / 2 - 1] == 3) {
								std::cout << " ";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //장애물 색깔 빨강색으로 설정
								std::cout << "Х"; // 장애물이 있으면(3) X 출력
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
							}
							else if (boardArr[i / 2 - 1][j / 2 - 1] == 4) {
								std::cout << " ◇"; // 마지막 놓은 돌이 검은돌이면(4) ☆ 출력;
								boardArr[i / 2 - 1][j / 2 - 1] = 1;
							}
							else if (boardArr[i / 2 - 1][j / 2 - 1] == 5) {
								std::cout << " ◆"; // 마지막 놓은 돌이 흰돌이면(5) ★ 출력
								boardArr[i / 2 - 1][j / 2 - 1] = 2;
							}
						}
					}
					else {
						std::cout << "│";
					}
				}
			}
		}
	}
}

//돌을 놓을 수 있는 자리인지 체크하는 함수
void possibleCheck() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			check[i][j] = false;
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) { // 보드 전체 돌면서 체크
			if (boardArr[i][j] == 0) { // 빈자리라면 그 칸 주위 돌면서 체크
				for (int k = 0; k < 8; k++) {
					int nx = i + dx[k];
					int ny = j + dy[k];
					if (nx >= BOARD_SIZE || ny >= BOARD_SIZE || nx < 0 || ny < 0 || boardArr[nx][ny] == 3) {
						continue; //보드 밖 벗어나는 칸, 장애물 칸 제외
					}
					if (turnCnt % 2 == 0 && (boardArr[nx][ny] == 2 || boardArr[nx][ny] == 5)) {   //흑차례인 경우 
						while (0 <= nx + dx[k] &&
							nx + dx[k] < BOARD_SIZE &&
							0 <= ny + dy[k] &&
							ny + dy[k] < BOARD_SIZE &&
							boardArr[nx + dx[k]][ny + dy[k]] != 3) {
							nx += dx[k];
							ny += dy[k];
							if (boardArr[nx][ny] != 2 && boardArr[nx][ny] != 5) {
								if (boardArr[nx][ny] == 1) {
									check[i][j] = true;
									break;
								}
								else {
									break;
								}
							}
						}
					}
					if (turnCnt % 2 == 1 && (boardArr[nx][ny] == 1 || boardArr[nx][ny] == 4)) {   //백차례인 경우
						while (0 <= nx + dx[k] &&
							nx + dx[k] < BOARD_SIZE &&
							0 <= ny + dy[k] &&
							ny + dy[k] < BOARD_SIZE &&
							boardArr[nx + dx[k]][ny + dy[k]] != 3) {
							nx += dx[k];
							ny += dy[k];
							if (boardArr[nx][ny] != 1 && boardArr[nx][ny] != 4) {
								if (boardArr[nx][ny] == 2) {
									check[i][j] = true;
									break;
								}
								else {
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

// 놓을 수 있는 자리에 돌을 놓으면 돌을 뒤집는 함수
void putStone() {
	int r, c;
	char tmp_r;
	while (1) {
		if (passCnt > 0) {
			std::cout << "더 이상 놓을 곳이 없어 패스합니다" << std::endl;
		}
		std::cout << std::endl << "돌을 놓을 곳을 입력하세요 ex) E5" << std::endl;
		std::cout << "지금은 ";
		if (turnCnt % 2 == 0) {
			std::cout << "○";
		}
		else {
			std::cout << "●";
		}
		std::cout << " 차례입니다" << std::endl;
		std::cin >> tmp_r >> c;
		r = tmp_r - 'A';
		c -= 1;

		if (check[r][c] == true) {
			for (int i = 0; i < 8; i++) {
				int nx = r + dx[i];
				int ny = c + dy[i];
				if (nx >= BOARD_SIZE || nx < 0 || ny >= BOARD_SIZE || ny < 0 || boardArr[nx][ny] == 3) {
					continue;
				}
				if (turnCnt % 2 == 0 && boardArr[nx][ny] == 2) { // 흑차례일때
					while (nx + dx[i] < BOARD_SIZE &&
						ny + dy[i] < BOARD_SIZE &&
						nx + dx[i] >= 0 &&
						ny + dy[i] >= 0 &&
						boardArr[nx + dx[i]][ny + dy[i]] != 3) {
						nx += dx[i];
						ny += dy[i];
						if (boardArr[nx][ny] != 2) {
							break;
						}
					}
					if (boardArr[nx][ny] == 1) { //탐색 중 상대 돌 발견 시 되돌아오며 자신의 돌을 뒤집음 
						while (1) {
							boardArr[nx][ny] = 1;
							if (nx == r && ny == c) {
								boardArr[r][c] = 4;
								break;
							}
							nx -= dx[i];
							ny -= dy[i];
						}
					}
				}
				if (turnCnt % 2 == 1 && boardArr[nx][ny] == 1) { // 백차례일때
					while (nx + dx[i] < BOARD_SIZE &&
						ny + dy[i] < BOARD_SIZE &&
						nx + dx[i] >= 0 &&
						ny + dy[i] >= 0 &&
						boardArr[nx + dx[i]][ny + dy[i]] != 3) {
						nx += dx[i];
						ny += dy[i];
						if (boardArr[nx][ny] != 1) {
							break;
						}
					}
					if (boardArr[nx][ny] == 2) { //탐색 중 상대 돌 발견 시 되돌아오며 자신의 돌을 뒤집음 
						while (1) {
							boardArr[nx][ny] = 2;
							if (nx == r && ny == c) {
								boardArr[r][c] = 5;
								break;
							}
							nx -= dx[i];
							ny -= dy[i];
						}
					}
				}
			}
			passCnt = 0;
			turnCnt++;
			stoneCnt++;
			break;
		}
		else { // 돌을 놓을 수 없는 위치이면 메시지 출력하고 다시 물음
			std::cout << "놓을 수 없는 위치입니다" << std::endl;
		}
	}
}

//좌표축 출력
void xyCoordinate() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		gotoxy(4 * BOARD_SIZE + 2, 2 * i + 1);
		char b = i + 'A';
		std::cout << b;
	}
	gotoxy(2, 2 * BOARD_SIZE + 1);
	for (int i = 1; i <= BOARD_SIZE; i++) {
		std::cout << i << "   ";
	}
}

//점수판 출력
void scoreBoard() {
	int blackCnt = std::count(&boardArr[0][0], &boardArr[0][0] + BOARD_SIZE * BOARD_SIZE, 1) +
		std::count(&boardArr[0][0], &boardArr[0][0] + BOARD_SIZE * BOARD_SIZE, 4);
	int whiteCnt = std::count(&boardArr[0][0], &boardArr[0][0] + BOARD_SIZE * BOARD_SIZE, 2) +
		std::count(&boardArr[0][0], &boardArr[0][0] + BOARD_SIZE * BOARD_SIZE, 5);

	gotoxy(0, 19);
	for (int i = 0; i < BOARD_SIZE; i++) {
		std::cout << "****";
	}
	std::cout << "*****" << std::endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		std::cout << " ";
	}
	std::cout << "○  :  " << blackCnt << "   " << "●  :  " << whiteCnt << std::endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		std::cout << "****";
	}
	std::cout << "*****";
}

//게임종료 후 승자판단하여 출력
void winnerJudge() {
	int blackCnt = std::count(&boardArr[0][0], &boardArr[0][0] + BOARD_SIZE * BOARD_SIZE, 1) +
		std::count(&boardArr[0][0], &boardArr[0][0] + BOARD_SIZE * BOARD_SIZE, 4);
	int whiteCnt = std::count(&boardArr[0][0], &boardArr[0][0] + BOARD_SIZE * BOARD_SIZE, 2) +
		std::count(&boardArr[0][0], &boardArr[0][0] + BOARD_SIZE * BOARD_SIZE, 5);
	std::cout << std::endl << "게임이 종료되었습니다. " << std::endl;
	if (blackCnt > whiteCnt) {
		std::cout << "승자는 ○ 입니다." << std::endl;
	}
	else if (whiteCnt > blackCnt) {
		std::cout << "승자는 ● 입니다." << std::endl;
	}
	else {
		std::cout << "비겼습니다." << std::endl;
	}
	selection = 0;
	//보드 초기화
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			boardArr[i][j] = 0;
			check[i][j] = false;
		}
	}
	system("PAUSE");
}