/**
 * @file AI.c
 * @brief will manage AI
 */

#ifndef AI
#define AI

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "main.c"

/**
 * @fn int AILevel1(Box*** board)
 * @brief first level of IA ( which is not a AI just random)
 */
int AILevel1(Box*** board) {
	
	switch (rand() % 4) {
		case 0: slide(UP, board); break;
		case 1: slide(LEFT, board); break;
		case 2: slide(BOTTOM, board); break;
		case 3: slide(RIGHT, board); break;

		default: printf("An Error Occured ! Please call developpers"); exit(EXIT_FAILURE);
	}
}

/**
 * @fn Box* copyBox(Box* box)
 * @brief copy a box
 */
Box* copyBox(Box* box) {
	Box* temp = (Box*)malloc(sizeof(Box));
	temp->value = box->value;
	
	return temp;
}

/**
 * @fn Box*** copyBoard(Box*** board, int size)
 * @brief copy a board
 */
Box*** copyBoard(Box*** board, int size) {
	Box*** temp = (Box***)malloc(size * sizeof(Box**));

	for (int i = 0; i < size; i++) {
		temp[i] = (Box**)malloc(size * sizeof(Box*));
		
		for (int j = 0; j < size; j++) {
			temp[i][j] = copyBox(board[i][j]);
		}
	}
	
	return temp;
}


/**
 * @fn int evalBoard(Box *** board, int size)
 * @brief give a score to a board
 */
int evalBoard(Box *** board, int size) {

	int score = 0;
	static int** multiplier = NULL;
	if (multiplier == NULL) {
		multiplier = (int**)malloc(size * sizeof(int *));

		for (int i = 0; i < size; i++) {
			multiplier[i] = (int*)malloc(size * sizeof(int));

			for (int j = 0; j < size; j++) {
				if (i % 2 == 0) {
					multiplier[i][j] = -size*size*size + i*size*size + j*size;
				} else {
					multiplier[i][size -j] = -size*size*size + i*size*size + j * size;
				}
			}
		}
		//need to free mulyiplier at the end !!!
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] != NULL) score += board[i][j]->value * multiplier[i][j];
		}
	}

	return score;
}

/**
 * @fn int freeBoard(Box*** board, int size)
 * @brief free a board
 */
int freeBoard(Box*** board, int size) {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			free(board[i][j]);
		}
		free(board[i]);
	}
	free(board);

	return 0;
}

/**
 * @fn int maxof(int count, ...)
 * @brief get the maximun of all int in argument
 * @param count is the number of argument except this one
 * @param ... is an elliptic list of int
 * @return the maximun of all int in argument
 */
int maxof(int count, ...) {
	va_list args;
	va_start(args, count);

	int max;
	if (count <= 0) { return 0; }
	else {
		max = (int) va_arg(args, int);
		count--;
	}
	while (count > 0) {
		int temp = (int)va_arg(args, int);
		if (temp > max) max = temp;
		count--;
	}
	va_end(args);
}

/**
 * @fn int AILevel2(Box*** board)
 * @brief The seconde level of AI wich give a score to next move and play the best
 */
int AILevel2(Box*** board) {
	Box*** boardUp = copyBoard(board);
	Box*** boardLeft = copyBoard(board);
	Box*** boardBottom = copyBoard(board);
	Box*** boardRight = copyBoard(board);

	slide(UP, boardUp);
	slide(LEFT, boardLeft);
	slide(BOTTOM, boardBottom);
	slide(RIGHT, boardRight);

	int scoreUp = evalBoard(boardUp);
	int scoreLeft = evalBoard(boardLeft);
	int scoreBottom = evalBoard(boardBottom);
	int scoreRight = evalBoard(boardRight);

	int max = maxof(4, scoreUp, scoreLeft, scoreBottom, scoreRight);

	//pas de switch avec des valeur non constante

	if (max == scoreUp) {
		board = boardUp;
		freeBoard(boardLeft); freeBoard(boardBottom); freeBoard(boardRight);
	} else if (max == scoreLeft) {
		board = boardLeft;
		freeBoard(boardUp); freeBoard(boardBottom); freeBoard(boardRight);
	} else if (max == scoreBottom) {
		board = boardBottom;
		freeBoard(boardUp); freeBoard(boardLeft); freeBoard(boardRight);
	} else if (max == scoreRight) {
		board = boardRight;
		freeBoard(boardUp); freeBoard(boardLeft); freeBoard(boardBottom);
	} else {
		printf("An Error Occcured ! Please call developpers !"); freeBoard(boardUp); freeBoard(boardLeft); freeBoard(boardBottom); freeBoard(boardRight); exit(EXIT_FAILURE);
	}
}

#endif