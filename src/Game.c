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
    state.board = malloc(state.size * sizeof(Box **)); //difference with Box * (*temp)[] = malloc(sizeof(Box *[size][size])) ?
	for (int i = 0; i < state.size; i++) {
		state.board[i] = malloc(state.size * sizeof(Box*));
		for (int j = 0; j < state.size; j++) state.board[i][j] = NULL;
	}

    srand(time(NULL));
    generateNewBox(state.board, state.size);

    /* Course of the game */
	while (true) {
        Box * box = generateNewBox(state.board, state.size);
        printBoard(state.board, state.size);
        if (!canMove(state.board, state.size)) break;

		AILevel3(state.board, state.size, 0);
		/*
        int moves = 0;
        do {
            int c;
            do {
                printf("Bouger le plateau : ");
                scanf("%d", &c);
            } while (c != 2 && c != 6 && c != 8 && c != 4);
            switch (c) {
            case 4: moves = slide(LEFT, state.board, state.size); break;
            case 6: moves = slide(RIGHT, state.board, state.size); break;
            case 8: moves = slide(UP, state.board, state.size); break;
            case 2: moves = slide(DOWN, state.board, state.size); break;
            }
            if (moves == 0) printf("2Can not move like that %c\n", c);
        } while (moves == 0);
		*/
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
Box * generateNewBox(Box *** board, int size) {
	Box*** emptyBoxes = malloc(size * size * sizeof(Box**));
	for (int i = 0; i < size * size; i++) emptyBoxes[i] = NULL;

	int k = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == NULL) emptyBoxes[k++] = &(board[i][j]);
		}
	}

	int index = (k == 0) ? 0 : rand() % k;

	Box* box = (Box*)malloc(sizeof(Box));
	box->value = power(2, (rand() % 2) + 1);

	return *(emptyBoxes[index]) = box;
	/*
    Box * box = malloc( sizeof(Box) );
    if (box == NULL) {
        printf("[ERROR] An error occured >> Could not allocate memory for new Box !");
        exit(EXIT_FAILURE);
    }

    int i, j;
    i = rand() % 4;
    j = rand() % 4;

    box->value = power(2, (rand() % 2) + 1);

    if (board[i][j] == NULL) {
        board[i][j] = box;
        return box;

    }
    else {
        free(box);
        return generateNewBox(board, size);
    }
	*/
}

/**
 * @fn int printBoard(Box*** board, int size)
 * @brief just a debug function that print the board
 */
int printBoard(Box *** board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            (board[i][j] == NULL) ? printf("   |") : printf(" %d |", board[i][j]->value);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

/**
 * @fn bool canMove(int** board, int size)
 * @brief chech if a move is possible
 * @param board the game board
 * @param the size of the game board
 * @return true if a move is possible false otherwise
 */
bool canMove(Box *** board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == NULL) return true;
            if (j != size - 1 && board[i][j] != NULL && board[i][j + 1] != NULL && board[i][j]->value == board[i][j + 1]->value) return true;
            if (i != size - 1 && board[i][j] != NULL && board[i + 1][j] != NULL && board[i][j]->value == board[i + 1][j]->value) return true;
        }
    }
    return false;
}

/**
 * @fn int slide(Direction dir, int ** board, int size)
 * @brief apply a move on the board
 * @param dir The Direction where the move go
 * @param board the game board
 * @param size of the game board
 * @return the number of move made
 */
int slide(Directions dir, Box *** board, int size) {

	int move = 0;
	switch (dir) {
		case LEFT:
		for (int i = 1; i < size; i++) {
			for (int j = 0; j < size; j++) {
				int k;
				for (k = i; k > 0 && board[j][k - 1] == NULL; k--) {
					if (board[j][k] == NULL) continue;
					board[j][k - 1] = board[j][k];
					board[j][k] = NULL;
					move++;
				}

				if (k > 0 && board[j][k - 1] != NULL && board[j][k] != NULL && board[j][k - 1]->value == board[j][k]->value) {
					board[j][k - 1]->value *= 2;
					free(board[j][k]);
                    board[j][k] = NULL;
					move++;
				}
			}
		}
		break;

	case RIGHT:
		for (int i = size - 1; i >= 0; i--) {
			for (int j = 0; j < size; j++) {
				int k;
				for (k = i; k < size - 1 && board[j][k + 1] == NULL; k++) {
					if (board[j][k] == NULL) continue;
					board[j][k + 1] = board[j][k];
					board[j][k] = NULL;
					move++;
				}

				if (k < size - 1 && board[j][k + 1] != NULL && board[j][k] != NULL && board[j][k + 1]->value == board[j][k]->value) {
					board[j][k + 1]->value *= 2;
					free(board[j][k]);
                    board[j][k] = NULL;
					move++;
				}
			}
		}
		break;

	case UP:
		for (int i = 1; i < size; i++) {
			for (int j = 0; j < size; j++) {
				int k;
				for (k = i; k > 0 && board[k - 1][j] == NULL; k--) {
					if (board[k][j] == NULL) continue;
					board[k - 1][j] = board[k][j];
					board[k][j] = NULL;
					move++;
				}

				if (k > 0 && board[k - 1][j] != NULL && board[k][j] != NULL && board[k - 1][j]->value == board[k][j]->value) {
					board[k - 1][j]->value *= 2;
					free(board[k][j]);
                    board[k][j] = NULL;
					move++;
				}
			}
		}
		break;

	case DOWN:
		for (int i = size - 1; i >= 0; i--) {
			for (int j = 0; j < size; j++) {
				int k;
				for (k = i; k < size - 1 && board[k + 1][j] == NULL; k++) {
					if (board[k][j] == NULL) continue;
					board[k + 1][j] = board[k][j];
					board[k][j] = NULL;
					move++;
				}

				if (k < size - 1 && board[k + 1][j] != NULL && board[k][j] != NULL && board[k + 1][j]->value == board[k][j]->value) {
					board[k + 1][j]->value *= 2;
					free(board[k][j]);
                    board[k][j] = NULL;
					move++;
				}
			}
		}
		break;

	default: printf("[Error] An error occured >> Direction for sliding unknown.\n Please contact developpers. \n"); exit(EXIT_FAILURE); break;
	}

	return move;
}