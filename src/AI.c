/**
 * @file AI.c
 * @brief will manage AI
 */

#include "headers/AI.h"

/**
 * @fn int AILevel1(Box*** board)
 * @brief first level of IA ( which is not a AI just random)
 */
int AILevel1(GameState * state) {
	int random;
	while (slide((random = rand() % 4), state) == 0);
	return random;
}


/**
 * @fn int evalBoard(Box *** board, int size)
 * @brief give a score to a board
 */
int evalBoard(GameState * state) {
	int score = 0;
	for (int i = 0; i < state->size; i++) {
		for (int j = 0; j < state->size; j++) {
			if (state->currentBoard[i][j] != NULL) score += (i * 4 + j + 1) * state->currentBoard[i][j]->value;
		}
	}
	return score;
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

	return max;
}

/**
 * @fn int AILevel2(Box*** board)
 * @brief The seconde level of AI wich give a score to next move and play the best
 */
int AILevel2(GameState * state) {
	int moves[4] = { 0 }, scores[4] = { 0 };

	for (int i = 0; i < 4; i++) {
		Board temp = copyBoard(state->currentBoard, state->size);
		GameState stateBis;
		stateBis.currentBoard = temp;
		stateBis.size = state->size;
		moves[i] = slide(i, &stateBis);
		scores[i] = evalBoard(&stateBis);
		freeBoard(temp, state->size);
	}

	int k = 0;
	for (int i = 0; i < 4; i++) if (scores[k] < scores[i] && moves[i] != 0) k = i;

	slide(k, state);
	return k;
}

#define AIRecursionMax 3
#define AILoopMax 10
int AILevel3(GameState* state) { return AILevel3R(state, 0); }

int AILevel3R(GameState * state, int recursion) {
	if (recursion >= AIRecursionMax || !canMove(state)) return evalBoard(state);

	int scores[4] = { 0 }, moves[4] = { 0 };
	for (int j = 0; j < AILoopMax; j++) {
		for (int i = 0; i < 4; i++) {
			Board board = copyBoard(state->currentBoard, state->size);
			GameState stateBis;
			stateBis.currentBoard = board;
			stateBis.size = state->size;
			if (slide(i, &stateBis) != 0) {
				moves[i]++;
				generateNewBox(&stateBis);
				scores[i] += AILevel3R(&stateBis, recursion + 1);
			}
			freeBoard(board, state->size);
		}
	}
	for (int i = 0; i < 4; i++) scores[i] = (moves[i] == 0) ? 0 : scores[i] / moves[i];

	if (recursion > 0) return maxof(4, scores[0], scores[1], scores[2], scores[3]);

	int k = 0;
	for (int i = 0; i < 4; i++) if (scores[k] < scores[i]) k = i;
	return slide(k, state);
}
