#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 30

void init_board(char board[BOARD_SIZE][BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = '.';
		}
	}
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

void draw_rect(char board[BOARD_SIZE][BOARD_SIZE], int x1, int y1, int x2, int y2) {
	for (int i = y1; i <= y2; i++) {
		for (int j = x1; j <= x2; j++) {
			board[i][j] = '0';
		}
	}
}

void clear_rect(char board[BOARD_SIZE][BOARD_SIZE], int x1, int y1, int x2, int y2) {
	for (int i = y1; i <= y2; i++) {
		for (int j = x1; j <= x2; j++) {
			board[i][j] = '.';
		}
	}
}

void move_rect(char board[BOARD_SIZE][BOARD_SIZE], int* x1, int* y1, int* x2, int* y2, int dx, int dy) {
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

int rect_area(int x1, int y1, int x2, int y2) {
	return (x2 - x1 + 1) * (y2 - y1 + 1);
}

int main()
{
	char board[BOARD_SIZE][BOARD_SIZE];
	int x1, y1, x2, y2;
	char command;

	init_board(board);

	printf("좌표값 입력(x1 y1 x2 y2): ");
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

	draw_rect(board, x1, y1, x2, y2);
	print_board(board);

	while (1) {
		printf("command: ");
		scanf(" %c", &command);

		switch (command)
		{
		case 'x': move_rect(board, &x1, &y1, &x2, &y2, 1, 0); break;
		case 'X': move_rect(board, &x1, &y1, &x2, &y2, -1, 0); break;
		case 'y': move_rect(board, &x1, &y1, &x2, &y2, 0, 1); break;
		case 'Y': move_rect(board, &x1, &y1, &x2, &y2, 0, -1); break;
		case 's':
			clear_rect(board, x1, y1, x2, y2);
			x1 = (x1 + 1 < x2) ? x1 + 1 : x1;
			x2 = (x2 - 1 > x1) ? x2 - 1 : x2;
			y1 = (y1 + 1 < y2) ? y1 + 1 : y1;
			y2 = (y2 - 1 > y1) ? y2 - 1 : y2;
			draw_rect(board, x1, y1, x2, y2);
			break;

		case 'S':
			clear_rect(board, x1, y1, x2, y2);
			x1 = (x1 - 1 >= 0) ? x1 - 1 : x1;
			x2 = (x2 + 1 < BOARD_SIZE) ? x2 + 1 : x2;
			y1 = (y1 - 1 >= 0) ? y1 - 1 : y1;
			y2 = (y2 + 1 < BOARD_SIZE) ? y2 + 1 : y2;
			draw_rect(board, x1, y1, x2, y2);
			break;

		case 'm':
			printf("면적: %d\n", rect_area(x1, y1, x2, y2));
			break;

		case 'n':
			printf("면적 비율: %.2f%%\n", (float)rect_area(x1, y1, x2, y2) / (BOARD_SIZE * BOARD_SIZE) * 100);
			break;

		case 'r':
			init_board(board);
			printf("좌표값 입력(x1 y1 x2 y2): ");
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			draw_rect(board, x1, y1, x2, y2);
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