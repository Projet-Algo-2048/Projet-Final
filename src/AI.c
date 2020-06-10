/**
 * @file AI.c
 * @brief will manage AI
 */

#include "headers/AI.h"

/**
 * @fn int AILevel1(Box*** board)
 * @brief first level of IA ( which is not a AI just random)
 */
int AILevel1(Board board, int size) {
	int random;
	while (slide((random = rand() % 4), board, size) == 0);
	return random;
}


/**
 * @fn int evalBoard(Box *** board, int size)
 * @brief give a score to a board
 */
int evalBoard(Board board, int size) {
	int score = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] != NULL) score += (i * 4 + j + 1) * board[i][j]->value;
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
int AILevel2(Board board, int size) {
	int moves[4] = { 0 }, scores[4] = { 0 };

	for (int i = 0; i < 4; i++) {
		Board temp = copyBoard(board, size);
		moves[i] = slide(i, temp, size);
		scores[i] = evalBoard(temp, size);
		freeBoard(temp, size);
	}

	int k = 0;
	for (int i = 0; i < 4; i++) if (scores[k] < scores[i] && moves[i] != 0) k = i;

	slide(k, board, size);
	return k;
}
/*
int AILevel2(GameState * state) {
	

	Box*** boardUp = copyBoard(state->board, state->size);
	Box*** boardLeft = copyBoard(state->board, state->size);
	Box*** boardDown = copyBoard(state->board, state->size);
	Box*** boardRight = copyBoard(state->board, state->size);

	int moveUP = slide(UP, boardUp, state->size);
	int moveLEFT = slide(LEFT, boardLeft, state->size);
	int moveDOWN = slide(DOWN, boardDown, state->size);
	int moveRIGHT = slide(RIGHT, boardRight, state->size);

	int scoreUp = (moveUP == 0) ? 0 : evalBoard(boardUp, state->size);
	int scoreLeft = (moveLEFT == 0) ? 0 : evalBoard(boardLeft, state->size);
	int scoreDown = (moveDOWN == 0) ? 0 : evalBoard(boardDown, state->size);
	int scoreRight = (moveRIGHT == 0) ? 0 : evalBoard(boardRight, state->size);

	int max = maxof(4, scoreUp, scoreLeft, scoreDown, scoreRight);

	//pas de switch avec des valeur non constante
	printf("swith \n");
	if (max == scoreUp) {
		freeBoard(state->board, state->size);
		state->board = boardUp;
		printf("UP\n");
		freeBoard(boardLeft, state->size); freeBoard(boardDown, state->size); freeBoard(boardRight, state->size);
	} else if (max == scoreLeft) {
		freeBoard(state->board, state->size);
		state->board = boardLeft;
		printf("LEFT\n");
		freeBoard(boardUp, state->size); freeBoard(boardDown, state->size); freeBoard(boardRight, state->size);
	} else if (max == scoreDown) {
		freeBoard(state->board, state->size);
		state->board = boardDown;
		printf("DOWN\n");
		freeBoard(boardUp, state->size); freeBoard(boardLeft, state->size); freeBoard(boardRight, state->size);
	} else if (max == scoreRight) {
		freeBoard(state->board, state->size);
		state->board = boardRight;
		printf("RIGHT\n");
		freeBoard(boardUp, state->size); freeBoard(boardLeft, state->size); freeBoard(boardDown, state->size);
	} else {
		printf("An Error Occcured ! Please call developpers !"); freeBoard(boardUp, state->size); freeBoard(boardLeft, state->size); freeBoard(boardDown, state->size); freeBoard(boardRight, state->size); exit(EXIT_FAILURE);
	}
}
*/

#define AIRecursionMax 3
#define AILoopMax 10

int AILevel3(Board board, int size, int recursion) {
	if (recursion >= AIRecursionMax || !canMove(board, size)) return evalBoard(board, size);

	int scores[4] = { 0 }, moves[4] = { 0 };
	for (int j = 0; j < AILoopMax; j++) {
		for (int i = 0; i < 4; i++) {
			Board boards = copyBoard(board, size);
			if (slide(i, boards, size) != 0) {
				moves[i]++;
				generateNewBox(boards, size);
				scores[i] += AILevel3(boards, size, recursion + 1);
			}
			freeBoard(boards, size);
		}
	}
	for (int i = 0; i < 4; i++) scores[i] = (moves[i] == 0) ? 0 : scores[i] / moves[i];

	if (recursion > 0) return maxof(4, scores[0], scores[1], scores[2], scores[3]);

	int k = 0;
	for (int i = 0; i < 4; i++) if (scores[k] < scores[i]) k = i;
	slide(k, board, size);
}

/*
int AILevel3(Board board, int size, int recursion) {
	printf("AILevel3 >> recursion : %d\n", recursion);
	if (recursion > AIRecursionMax || !canMove(board, size)) return evalBoard(board, size);
	
	int scoreUP = 0, scoreLEFT = 0, scoreDOWN = 0, scoreRIGHT = 0;
	int moveUP = 0, moveLEFT = 0, moveDOWN = 0, moveRIGHT = 0;
	for (int i = 0; i < AILoopMax; i++) {
		printf("AILevel3 >> loop : %d\n", i);
		Box*** boardUP = copyBoard(board, size);
		Box*** boardLEFT = copyBoard(board, size);
		Box*** boardDOWN = copyBoard(board, size);
		Box*** boardRIGHT = copyBoard(board, size);

		if (slide(UP, boardUP, size) != 0) { moveUP++; scoreUP += AILevel3(boardUP, size, recursion + 1);}
		if (slide(LEFT, boardLEFT, size) != 0) { moveLEFT++; scoreLEFT += AILevel3(boardLEFT, size, recursion + 1);}
		if (slide(DOWN, boardDOWN, size) != 0) { moveDOWN++; scoreDOWN += AILevel3(boardDOWN, size, recursion + 1);}
		if (slide(RIGHT, boardRIGHT, size) != 0) { moveRIGHT++; scoreRIGHT += AILevel3(boardRIGHT, size, recursion + 1);}

		freeBoard(boardUP, size);
		freeBoard(boardLEFT, size);
		freeBoard(boardDOWN, size);
		freeBoard(boardRIGHT, size);
	}
	scoreUP = (moveUP == 0) ? 0 : scoreUP / moveUP;
	scoreLEFT = (moveLEFT == 0) ? 0 : scoreLEFT / moveLEFT;
	scoreDOWN = (moveDOWN == 0) ? 0 : scoreDOWN / moveDOWN;
	scoreRIGHT = (moveRIGHT == 0) ? 0 : scoreRIGHT / moveRIGHT;

	int scoreMax = maxof(4, scoreDOWN, scoreLEFT, scoreRIGHT, scoreUP);

	if (recursion > 0) return scoreMax;
	
	if (scoreMax == scoreDOWN) slide(DOWN, board, size);
	else if (scoreMax == scoreLEFT) slide(LEFT, board, size);
	else if (scoreMax == scoreRIGHT) slide(RIGHT, board, size);
	else if (scoreMax == scoreUP) slide(UP, board, size);
	
}
*/
