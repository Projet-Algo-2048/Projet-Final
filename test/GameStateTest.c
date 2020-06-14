#include <stdlib.h>

#include "test.c"
#include "../src/headers/GameStructs.h"

int printBoard(Box*** board, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf(" %p |", board[i][j]);
		}
		printf("\n");
	}
}

int main(void) {
	GameState state;
	state.size = 4;
	state.board = malloc(state.size * sizeof(Box * [state.size]));
	for (int i = 0; i < state.size; i++) state.board[i] = malloc(state.size * sizeof(Box*));

	printBoard(state.board, state.size);
}