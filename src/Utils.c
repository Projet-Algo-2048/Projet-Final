/**
 * @file Utils.c
 * @brief this file will contain all utils fonction for the game
 */

#include "headers/Utils.h"

/**
 * @fn int power(int number, int power)
 * @brief compute the result of 'number' to power of 'power'
 */
int power(int number, int power) {
    int value = 1;
    for (int i = 0; i < power; i++) {
        value = value * number;
    }
    return value;
}


/**
 * @fn Box* copyBox(Box* box)
 * @brief copy a box
 */
Box* copyBox(Box* box) {
	Box* temp = malloc(sizeof(Box));
	if (temp == NULL) { printf("[ERROR]<COPYBOARD> : Could not allocate memory \n"); exit(EXIT_FAILURE); }

	temp->value = box->value;

	return temp;
}

/**
 * @fn Box*** copyBoard(Box*** board, int size)
 * @brief copy a board
 */
Board copyBoard(Board board, int size) {
	Board temp = malloc(size * sizeof(Box**));
	if (temp == NULL) { printf("[ERROR]<COPYBOARD> : Could not allocate memory \n"); exit(EXIT_FAILURE); }

	for (int i = 0; i < size; i++) {
		temp[i] = malloc(size * sizeof(Box*));
		if (temp == NULL) { printf("[ERROR]<COPYBOARD> : Could not allocate memory \n"); exit(EXIT_FAILURE); }

		for (int j = 0; j < size; j++) {
			temp[i][j] = (board[i][j] == NULL) ? NULL : copyBox(board[i][j]);
		}
	}

	return temp;
}

/**
 * @fn int freeBoard(Box*** board, int size)
 * @brief free a board
 */
int freeBoard(Board board, int size) {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] != NULL) free(board[i][j]);
			board[i][j] = NULL;
		}
		free(board[i]);
	}
	free(board);

	return 0;
}