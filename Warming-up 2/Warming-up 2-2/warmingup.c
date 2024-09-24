#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BOARD_SIZE 30

// 색 변경용
void set_color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void reset_color() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
// 기본 보드 설정
void init_board(char board[BOARD_SIZE][BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = '.';
		}
	}
}
// 출력
void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == '#') {
				set_color(12);
				printf("%c ", board[i][j]);
				reset_color();
			}
			else {
				printf("%c ", board[i][j]);
			}
		}
		printf("\n");
	}
}
// 도형 1 그리기
//void draw_rect(char board[BOARD_SIZE][BOARD_SIZE], int x1, int y1, int x2, int y2) {
//	for (int i = y1; i <= y2; i++) {
//		for (int j = x1; j <= x2; j++) {
//			if (board[i][j] == 'x') {
//				board[i][j] = '#';
//			}
//			else if (board[i][j] != '#') {
//				board[i][j] = '0';
//			}			
//		}
//	}
//}
// 초기화
void clear_rect(char board[BOARD_SIZE][BOARD_SIZE], int x1, int y1, int x2, int y2) {
	for (int i = y1; i <= y2; i++) {
		for (int j = x1; j <= x2; j++) {
			board[i][j] = '.';
		}
	}
}
void draw_rect(char board[BOARD_SIZE][BOARD_SIZE], int x1, int y1, int x2, int y2) {
	for (int i = y1; i <= y2; i++) {
		for (int j = x1; j <= x2; j++) {
			board[i][j] = '0';
		}
	}
}
// 1칸씩 움직임 도형 1
void move_rect1(char board[BOARD_SIZE][BOARD_SIZE], int* x1, int* y1, int* x2, int* y2, int dx, int dy) {
	if (*x1 > *x2) {
		for (int i = *y1; i <= *y2; i++) {
			for (int j = *x1; j < BOARD_SIZE; j++) {
				board[i][j] = '.';
			}
			for (int j = 0; j <= *x2; j++) {
				board[i][j] = '.';
			}
		}
	}
	else if (*y1 > *y2) {
		for (int j = *x1; j <= *x2; j++) {
			for (int i = *y1; i < BOARD_SIZE; i++) {
				board[i][j] = '.';
			}
			for (int i = 0; i <= *y2; i++) {
				board[i][j] = '.';
			}
		}
	}
	else {
		clear_rect(board, *x1, *y1, *x2, *y2);
	}

	*x1 = (*x1 + dx + BOARD_SIZE) % BOARD_SIZE;
	*x2 = (*x2 + dx + BOARD_SIZE) % BOARD_SIZE;
	*y1 = (*y1 + dy + BOARD_SIZE) % BOARD_SIZE;
	*y2 = (*y2 + dy + BOARD_SIZE) % BOARD_SIZE;

	if (*x1 > *x2) {
		for (int i = *y1; i <= *y2; i++) {
			for (int j = *x1; j < BOARD_SIZE; j++) {
				board[i][j] = '0';
			}
			for (int j = 0; j <= *x2; j++) {
				board[i][j] = '0';
			}
		}
	}
	else if (*y1 > *y2) {
		for (int j = *x1; j <= *x2; j++) {
			for (int i = *y1; i < BOARD_SIZE; i++) {
				board[i][j] = '0';
			}
			for (int i = 0; i <= *y2; i++) {
				board[i][j] = '0';
			}
		}
	}
	else {
		draw_rect(board, *x1, *y1, *x2, *y2);
	}
}
// 1칸씩 움직임 도형 2
void move_rect2(char board[BOARD_SIZE][BOARD_SIZE], int* x1, int* y1, int* x2, int* y2, int dx, int dy) {
	clear_rect(board, *x1, *y1, *x2, *y2);

	*x1 = (*x1 + dx + BOARD_SIZE) % BOARD_SIZE;
	*x2 = (*x2 + dx + BOARD_SIZE) % BOARD_SIZE;
	*y1 = (*y1 + dy + BOARD_SIZE) % BOARD_SIZE;
	*y2 = (*y2 + dy + BOARD_SIZE) % BOARD_SIZE;
}
// 충돌체크 및 그리기
void check_and_draw(char board[BOARD_SIZE][BOARD_SIZE], int x1, int y1, int x2, int y2, int w1, int a1, int w2, int a2) {
	for (int i = y1; i <= y2; i++) {
		for (int j = x1; j <= x2; j++) {
			if (board[i][j] == 'x') {
				board[i][j] = '#';
			}
			else {
				board[i][j] = '0';
			}
		}
	}

	for (int i = a1; i <= a2; i++) {
		for (int j = w1; j <= w2; j++) {
			if (board[i][j] == '0') {
				board[i][j] = '#';
			}
			else {
				board[i][j] = 'x';
			}
		}
	}
}
// 면적 구하는 용도
int rect_area(int x1, int y1, int x2, int y2) {
	return (x2 - x1 + 1) * (y2 - y1 + 1);
}

int main()
{
	char board[BOARD_SIZE][BOARD_SIZE];
	int x1, y1, x2, y2;
	int w1, a1, w2, a2;
	char command;

	init_board(board);

	printf("도형1 좌표값 입력(x1 y1 x2 y2): ");
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	/*printf("도형2 좌표값 입력(x1 y1 x2 y2): ");
	scanf("%d %d %d %d", &w1, &a1, &w2, &a2);*/
	w1 = 29; w2 = 29; a1 = 29; a2 = 29;

	check_and_draw(board, x1, y1, x2, y2, w1, a1, w2, a2);
	print_board(board);

	while (1) {
		printf("command: ");
		scanf(" %c", &command);

		switch (command)
		{
		case 'x':
			move_rect1(board, &x1, &y1, &x2, &y2, 1, 0);
			check_and_draw(board, x1, y1, x2, y2, w1, a1, w2, a2);
			break;

		case 'X':
			move_rect1(board, &x1, &y1, &x2, &y2, -1, 0);
			check_and_draw(board, x1, y1, x2, y2, w1, a1, w2, a2);
			break;

		case 'y':
			move_rect1(board, &x1, &y1, &x2, &y2, 0, 1);
			check_and_draw(board, x1, y1, x2, y2, w1, a1, w2, a2);
			break;

		case 'Y':
			move_rect1(board, &x1, &y1, &x2, &y2, 0, -1);
			check_and_draw(board, x1, y1, x2, y2, w1, a1, w2, a2); 
			break;

		case 's':
			clear_rect(board, x1, y1, x2, y2);
			x1 = (x1 + 1 < x2) ? x1 + 1 : x1;
			x2 = (x2 - 1 > x1) ? x2 - 1 : x2;
			y1 = (y1 + 1 < y2) ? y1 + 1 : y1;
			y2 = (y2 - 1 > y1) ? y2 - 1 : y2;
			check_and_draw(board, x1, y1, x2, y2, w1, a1, w2, a2);
			break;

		case 'S':
			clear_rect(board, x1, y1, x2, y2);
			x1 = (x1 - 1 >= 0) ? x1 - 1 : x1;
			x2 = (x2 + 1 < BOARD_SIZE) ? x2 + 1 : x2;
			y1 = (y1 - 1 >= 0) ? y1 - 1 : y1;
			y2 = (y2 + 1 < BOARD_SIZE) ? y2 + 1 : y2;
			check_and_draw(board, x1 + 1, y1 + 1, x2 + 1, y2 + 1, w1, a1, w2, a2);
			break;

		case 'w':
			move_rect2(board, &w1, &a1, &w2, &a2, 1, 0);
			check_and_draw(board, x1, y1, x2, y2, w1, a1, w2, a2);
			break;

		case 'W':
			move_rect2(board, &w1, &a1, &w2, &a2, -1, 0);
			check_and_draw(board, x1, y1, x2, y2, w1, a1, w2, a2);
			break;

		case 'a':
			move_rect2(board, &w1, &a1, &w2, &a2, 0, 1);
			check_and_draw(board, x1, y1, x2, y2, w1, a1, w2, a2);
			break;

		case 'A':
			move_rect2(board, &w1, &a1, &w2, &a2, 0, -1);
			check_and_draw(board, x1, y1, x2, y2, w1, a1, w2, a2);
			break;

		case 'd':
			clear_rect(board, w1, a1, w2, a2);
			w1 = (w1 + 1 < w2) ? w1 + 1 : w1;
			w2 = (w2 - 1 > w1) ? w2 - 1 : w2;
			a1 = (a1 + 1 < a2) ? a1 + 1 : a1;
			a2 = (a2 - 1 > a1) ? a2 - 1 : a2;
			check_and_draw(board, x1, y1, x2, y2, w1, a1, w2, a2);
			break;

		case 'D':
			clear_rect(board, w1, a1, w2, a2);
			w1 = (w1 - 1 >= 0) ? w1 - 1 : w1;
			w2 = (w2 + 1 < BOARD_SIZE) ? w2 + 1 : w2;
			a1 = (a1 - 1 >= 0) ? a1 - 1 : a1;
			a2 = (a2 + 1 < BOARD_SIZE) ? a2 + 1 : a2;
			check_and_draw(board, x1, y1, x2, y2, w1, a1, w2, a2);
			break;

		case 'm':
			printf("면적: %d\n", rect_area(x1, y1, x2, y2));
			break;

		case 'n':
			printf("면적 비율: %.2f%%\n", (float)rect_area(x1, y1, x2, y2) / (BOARD_SIZE * BOARD_SIZE) * 100);
			break;

		case 'r':
			init_board(board);
			system("cls");

			printf("좌표값 입력(x1 y1 x2 y2): ");
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			printf("도형2 좌표값 입력(x1 y1 x2 y2): ");
			scanf("%d %d %d %d", &w1, &a1, &w2, &a2);

			check_and_draw(board, x1, y1, x2, y2, w1, a1, w2, a2);
			break;

		case 'q':
			printf("program exit...\n");
			exit(0);
			break;

		default:
			printf("wrong command\n");
			break;
		}

		print_board(board);
	}
}