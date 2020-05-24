#include "test.c"

#include "../src/headers/GameStructs.h"
#include "../src/headers/Game.h"

int printBoardf(Box*** board, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf(" %d |", board[i][j]->value);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

int main(void) {

	GameState state;
	state.size = 4;
	state.board = malloc(state.size * sizeof(Box * [state.size]));
	for (int i = 0; i < state.size; i++) {
		state.board[i] = malloc(state.size * sizeof(Box*));

		for (int j = 0; j < state.size; j++) {
			state.board[i][j] = (Box*)malloc(sizeof(Box));
			state.board[i][j]->value = ((i + j) % 2 == 0) ? 2 : 4;
		}
	}
	printf("Board Full and can not move \n");
	printBoardf(state.board, state.size);
	testInt(canMove(state.board, state.size), false);

	state.board[0][0]->value = 4;
	printf("Board Full and can move");
	printBoardf(state.board, state.size);
	testInt(canMove(state.board, state.size), true);

	free(state.board[0][0]);
	printf("Board not full and can move \n");
	printBoardf(state.board, state.size);
	testInt(canMove(state.board, state.size), false);

	for (int i = 0; i < state.size; i++) {
		for (int j = 0; j < state.size; j++) {
			if (i == 0 && j == 0) continue;
			free(state.board[i][j]);
		}
		free(state.board[i]);
	}
	free(state.board);	
}