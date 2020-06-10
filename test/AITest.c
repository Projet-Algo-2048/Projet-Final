#include "test.c"
#include "../src/headers/GameStructs.h"
#include "stdlib.h"
#include "time.h"
#include "../src/headers/AI.h"

int main(void) {
	printf("Testing maxof function \n");
	testInt(maxof(4, 3, 1, -9, 5), 5);

	GameState state;
	state.size = 4;
	state.board = malloc(state.size * sizeof(Box **)); //difference with Box * (*temp)[] = malloc(sizeof(Box *[size][size])) ?
	for (int i = 0; i < state.size; i++) state.board[i] = malloc(state.size * sizeof(Box*));

	srand(time(NULL));
	generateNewBox(state.board, state.size);
	for (int i = 0; i < 10; i++) {
		if (!canMove(state.board, state.size)) break;
		generateNewBox(state.board, state.size);

		printBoard(state.board, state.size);

		AILevel2(&state);
	}
	printBoard(state.board, state.size);
}