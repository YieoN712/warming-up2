#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define SIZE 5

void print_original_board();
void suffle(int* array, int size);

int main() {
	int board[SIZE][SIZE];
	int alp_number[25];
	int index = 0;

	for (int i = 64; i < 77; i++) {
		if (i == 64) {
			alp_number[index] = 64;
		}
		else {
			alp_number[++index] = i;
			alp_number[++index] = i;
		}			   
	}

	srand(time(NULL));

	suffle(alp_number, 25);

	index = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i][j] = alp_number[index++];
		}
	}

	print_original_board();

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf("%2c", board[i][j]);
		}
		printf("\n");
	}

	char position1[10], position2[10];

	return 0;
}

void print_original_board()
{
	for (int i = 0; i < SIZE + 1; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (i == 0 && j == 0) {
				printf("   ");
			}
			else if (i == 0 && j == 4) {
				printf(" %c ", j + 96);
				printf(" %c ", j + 97);
			}
			else if (i == 0) {
				printf(" %c ", j + 96);
			}
			else {
				printf(" * ");
			}
		}
		if (i != 5) {
			printf("\n %d ", i + 1);
		}
		else {
			printf("\n");
		}
	}

	printf("\n");
}
void suffle(int* array, int size)
{
	for (int i = size - 1; i > 0; i--) {
		int j = rand() % (i + 1);

		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}