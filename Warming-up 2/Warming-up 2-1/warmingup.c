#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define SIZE 5
#define JOKER '@'
#define MAX_TURNS 25

void print_game_board(int board[SIZE][SIZE], int revealed[SIZE][SIZE], int match_row1, int match_col1, int match_row2, int match_col2, int match);
void suffle(int* array, int size);
void reveal_positions(int board[SIZE][SIZE], int revealed[SIZE][SIZE], char pos1[], char pos2[]);
void reset_game(int board[SIZE][SIZE], int revealed[SIZE][SIZE]);
void set_color(int color);
void reset_color();
int check_game_over(int revealed[SIZE][SIZE]);

int main() {
	int board[SIZE][SIZE];
	int revealed[SIZE][SIZE] = { 0 };
	char position1[10], position2[10];
	int turn = 1, score = 100;

	srand(time(NULL));

	reset_game(board, revealed);

	while (turn <= MAX_TURNS) {
		print_game_board(board, revealed, -1, -1, -1, -1, 0);

		printf("턴 %d (남은 턴: %d): ", turn, MAX_TURNS - turn + 1);
		scanf("%s", position1);

		if (position1[0] == 'r') {
			system("cls");
			printf("reset...\n");
			Sleep(500);
			system("cls");
			reset_game(board, revealed);
			turn = 1;
			continue;
		}

		scanf("%s", position2);

		reveal_positions(board, revealed, position1, position2);

		if (check_game_over(revealed)) {
			printf("게임 성공!\n");
			Sleep(700);
			printf("게임 점수: 100점\n");
			printf("추가 점수: %d\n", (MAX_TURNS - turn + 1) * 3);
			printf("총    점: %d\n", (MAX_TURNS - turn + 1) * 3 + 100);
			break;
		}

		turn++;

		if (turn > MAX_TURNS) {
			if (!check_game_over(revealed)) {
				printf("게임 실패\n");
			}
			break;
		}

		printf("\n\n");
	}

	return 0;
}

// 초기 보드와 상태를 설정
void reset_game(int board[SIZE][SIZE], int revealed[SIZE][SIZE]) {
	int alp_number[25];
	int index = 0;

	// 초기화
	for (int i = 65; i < 77; i++) {
		if (index < 24) {
			alp_number[index++] = i;
			alp_number[index++] = i;
		}
	}
	alp_number[24] = JOKER;

	suffle(alp_number, 25);

	index = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i][j] = alp_number[index++];
			revealed[i][j] = 0;
		}
	}
	// 확인용
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf(" %c ", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void print_game_board(int board[SIZE][SIZE], int revealed[SIZE][SIZE], int match_row1, int match_col1, int match_row2, int match_col2, int match) {
	printf("   ");
	for (int j = 0; j < SIZE; j++) {
		printf(" %c ", 'a' + j);
	}
	printf("\n");

	for (int i = 0; i < SIZE; i++) {
		printf(" %d ", i + 1);
		for (int j = 0; j < SIZE; j++) {
			if (revealed[i][j]) {
				if ((i == match_row1 && j == match_col1) || (i == match_row2 && j == match_col2)) {
					if (match) {
						set_color(11);
					}
					else {
						set_color(12);
					}
				}
				else {
					set_color(9);
				}
				printf(" %c ", board[i][j]);
				reset_color();
			}
			else {
				printf(" * ");
			}
		}
		printf("\n");
	}
}

void suffle(int* array, int size) {
	for (int i = size - 1; i > 0; i--) {
		int j = rand() % (i + 1);

		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}
// 좌표를 변환
void parse_position(char pos[], int* row, int* col) {
	*col = pos[0] - 'a';
	*row = pos[1] - '1';
}

void reveal_positions(int board[SIZE][SIZE], int revealed[SIZE][SIZE], char pos1[], char pos2[]) {
	int row1, col1, row2, col2;
	parse_position(pos1, &row1, &col1);
	parse_position(pos2, &row2, &col2);

	revealed[row1][col1] = 1;
	revealed[row2][col2] = 1;

	if (board[row1][col1] == JOKER) {
		// 조커가 나왔을 경우 다른 알파벳과 같은 칸을 열어줌
		char target = board[row2][col2];
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (board[i][j] == target) {
					revealed[i][j] = 1;
				}
			}
		}
		print_game_board(board, revealed, row1, col1, row2, col2, 1);
	}
	else if (board[row2][col2] == JOKER) {
		// 두 번째 선택이 조커일 경우
		char target = board[row1][col1];
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (board[i][j] == target) {
					revealed[i][j] = 1;
				}
			}
		}
		print_game_board(board, revealed, row1, col1, row2, col2, 1);
	}
	else if (board[row1][col1] == board[row2][col2]) {
		print_game_board(board, revealed, row1, col1, row2, col2, 1);
	}
	else {
		print_game_board(board, revealed, row1, col1, row2, col2, 0);

		Sleep(1000);
		revealed[row1][col1] = 0;
		revealed[row2][col2] = 0;
	}
}

void set_color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void reset_color() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 기본색상 회색으로 설정
}

int check_game_over(int revealed[SIZE][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (!revealed[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}