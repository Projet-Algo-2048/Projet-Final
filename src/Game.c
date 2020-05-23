/**
 * @file Game.c
 * @brief This file contain function for the dourse of the game
 */

#include "headers/Game.h"

/**
 * @fn int game(GameState state)
 * @brief represente the game course
 */
int game(/* -> parameter to initialize game <- */) {

    /* initialisation of the game */
    GameState state;
    state.size = 4;
    state.board = malloc(state.size * sizeof(Box * [state.size])); //difference with Box * (*temp)[] = malloc(sizeof(Box *[size][size])) ?
    for (int i = 0; i < state.size; i++) state.board[i] = malloc(state.size * sizeof(Box*));

    /* Course of the game */
	while (true) {
		// -> code for the game course here <-
	}
	printf("Game Over ! \n");

    /* freeing memory */
    for (int i = 0; i < state.size; i++) {
        for (int j = 0; j < state.size; j++) if (state.board[i][j] != NULL) free(state.board[i][j]);
        free(state.board[i]);
    }
    free(state.board);
}
