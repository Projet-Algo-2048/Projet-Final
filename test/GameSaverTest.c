#include "test.c"
#include "../src/headers/GameSaver.h"
#include "../src/headers/GameStructs.h"
#include "../src/headers/Game.h"


int main(void) {
	GameState state;
	state.size = 4;

	state.board = malloc(state.size * sizeof(Box**));
	for (int i = 0; i < state.size; i++) {
		state.board[i] = malloc(state.size * sizeof(Box*));
		for (int j = 0; j < state.size; j++) state.board[i][j] = NULL;
	}

	Box* b1 = malloc(sizeof(Box));
	Box* b2 = malloc(sizeof(Box));
	b1->value = 5;
	b2->value = 16;

	state.board[1][2] = b1;
	state.board[3][0] = b2;

	saveGame(&state);

	GameState state2;

	loadGame(&state2);
	printBoard(state2.board, state2.size);
}