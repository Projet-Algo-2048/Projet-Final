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
    srand(time(NULL));
    generateNewBox(state.board, state.size);

    /* Course of the game */
	while (true) {
        generateNewBox(state.board, state.size);
        printBoard(state.board, state.size);
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

/**
 * @fn generateNewBox(int size, Box * board[size][size])
 * @brief add a new box to the game. Need srand(time(NULL) been called before
 * @param size the size of the following array
 * @param board 2D array 
 * @return the box generated
 */
Box * generateNewBox(Box * **board, int size) {
    Box * box = (Box *) malloc( sizeof(Box) );
    if (box == NULL) {
        printf("[ERROR] An error occured >> Could not allocate memory for new Box !");
        exit(EXIT_FAILURE);
    }

    int i, j;
    i = rand() % 4;
    j = rand() % 4;

    box->value = pow(2, (rand() % 2) + 1);

    if (board[i][j] == NULL) {
        board[i][j] = box;
        return box;

    }
    else {
        free(box);
        generateNewBox(board, size);
    }

    return box;
}

/**
 * @fn int printBoard(Box*** board, int size)
 * @brief just a debug function that print the board
 */
int printBoard(Box * ** board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf(" %d |", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}