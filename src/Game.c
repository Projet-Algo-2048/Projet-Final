/**
 * @file Game.c
 * @brief This file contain function for the dourse of the game
 */

#include "headers/Game.h"

/**
 * @fn int game(GameState state)
 * @brief represente the game course
 */
int game(/* parameters here */)  {

    /* initialisation of the game */
    srand(time(NULL));                      //necessary for random in futur statement

    GameState state;
    state.playerNumber = 2;
    state.size = 4;
    state.score = malloc(state.playerNumber * sizeof(int));
    for (int i = 0; i < state.playerNumber ; i++) {
      state.score[i]=0;
    }
    state.boards = malloc(state.playerNumber * sizeof(Board));
    for (int k = 0; k < state.playerNumber; k++) {
        state.boards[k] = malloc(state.size * sizeof(Box**));
        for (int i = 0; i < state.size; i++) {
            state.boards[k][i] = malloc(state.size * sizeof(Box*));
            for (int j = 0; j < state.size; j++) state.boards[k][i][j] = NULL;
        }
        state.currentBoard = state.boards[k];
        generateNewBox(&state);
    }
    

    /*
     state.board1 = malloc(state.size * sizeof(Box **));
     for (int i = 0; i < state.size; i++) {
       state.board1[i] = malloc(state.size * sizeof(Box*));
       for (int j = 0; j < state.size; j++) state.board1[i][j] = NULL;
     }
     state.board2 = malloc(state.size * sizeof(Box **));
     for (int i = 0; i < state.size; i++) {
       state.board2[i] = malloc(state.size * sizeof(Box*));
       for (int j = 0; j < state.size; j++) state.board2[i][j] = NULL;
     }

     srand(time(NULL));
     generateNewBox(state.board1, state.size);
     generateNewBox(state.board2, state.size);

    /* Course of the game */
    int i = 0;

    while (true) {
        state.currentPlayer = i % state.playerNumber;
        state.currentBoard = state.boards[state.currentPlayer];
        state.Currentscore = state.score[state.currentPlayer];
        printf("c'estau tour du joueur %d de jouer \n", state.currentPlayer + 1);

        generateNewBox(&state);
        printBoard(&state);

        if (!canMove(&state)) break;

        int moves = 0;
        do {
            int c;
            do {
                printf("Bouger le plateau : ");
                scanf("%d", &c);
            }while (c != 2 && c != 6 && c != 8 && c != 4);

            switch (c) {
                case 4: moves = slide(LEFT, &state); break;
                case 6: moves = slide(RIGHT, &state); break;
                case 8: moves = slide(UP, &state); break;
                case 2: moves = slide(DOWN, &state); break;
            }
            if (moves == 0) printf("Can not move like that %c\n", c);
        }while (moves == 0);

        i++;
 	}

    for ( int i = 0; i < state.playerNumber; i++) {
      printf("Score : %d\n", state.score[i]);
    }
 	printf("Game Over ! \n");
    /* freeing memory */

    for (int k = 0; k < state.playerNumber; k++) {
        for (int i = 0; i < state.size; i++) {
            for (int j = 0; j < state.size; j++) if (state.boards[k][i][j] != NULL) free(state.boards[k][i][j]);
            free(state.boards[k][i]);
        }
        free(state.boards[k]);
    }
    free(state.boards);

    /*
    for (int i = 0; i < state.size; i++) {
        for (int j = 0; j < state.size; j++) if (state.board1[i][j] != NULL) free(state.board1[i][j]);
        free(state.board1[i]);
    }
    free(state.board1);

    for (int i = 0; i < state.size; i++) {
        for (int j = 0; j < state.size; j++) if (state.board2[i][j] != NULL) free(state.board2[i][j]);
        free(state.board2[i]);
    }
    free(state.board2);
    */
 }


/**
 * @fn generateNewBox(int size, Box * board1[size][size])
 * @brief add a new box to the game. Need srand(time(NULL) been called before
 * @param size the size of the following array
 * @param board1 2D array
 * @return the box generated
 */
Box * generateNewBox(GameState * state) {
    Box * box = (Box *) malloc( sizeof(Box) );
    if (box == NULL) {
        printf("[ERROR] An error occured >> Could not allocate memory for new Box !");
        exit(EXIT_FAILURE);
    }

    int i, j;
    i = rand() % state->size;
    j = rand() % state->size;

    box->value = pow(2, (rand() % 2) + 1);

    if (state->currentBoard[i][j] == NULL) {
        state->currentBoard[i][j] = box;
        return box;

    }
    else {
        free(box);
        generateNewBox(state);
    }

    return box;
  }


/**
 * @fn int printboard1(Box*** board1, int size)
 * @brief just a debug function that print the board1
 */
int printBoard(GameState * state) {
    for (int i = 0; i < state->size; i++) {
        for (int j = 0; j < state->size; j++) {
            (state->currentBoard[i][j] == NULL) ? printf("   |") : printf(" %d |", state->currentBoard[i][j]->value);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

/**
 * @fn bool canMove(int** board1, int size)
 * @brief chech if a move is possible
 * @param board1 the game board1
 * @param the size of the game board1
 * @return true if a move is possible false otherwise
 */
bool canMove(GameState * state) {
    for (int i = 0; i < state->size; i++) {
        for (int j = 0; j < state->size; j++) {
            if (state->currentBoard[i][j] == NULL) return true;
            if (j != state->size - 1 && state->currentBoard[i][j] != NULL && state->currentBoard[i][j + 1] != NULL && state->currentBoard[i][j]->value == state->currentBoard[i][j + 1]->value) return true;
            if (i != state->size - 1 && state->currentBoard[i][j] != NULL && state->currentBoard[i + 1][j] != NULL && state->currentBoard[i][j]->value == state->currentBoard[i + 1][j]->value) return true;
        }
    }
    return false;
}

/**
 * @fn int slide(Direction dir, int ** board1, int size)
 * @brief apply a move on the board1
 * @param dir The Direction where the move go
 * @param board1 the game board1
 * @param size of the game board1
 * @return the number of move made
 */
int slide(Directions dir, GameState * state) {
	int move = 0;
	switch (dir) {
		case LEFT:
		for (int i = 1; i < state->size; i++) {
			for (int j = 0; j < state->size; j++) {
				int k;
				for (k = i; k > 0 && state->currentBoard[j][k - 1] == NULL; k--) {
					if (state->currentBoard[j][k] == NULL) continue;
                    state->currentBoard[j][k - 1] = state->currentBoard[j][k];
                    state->currentBoard[j][k] = NULL;
					move++;
				}

				if (k > 0 && state->currentBoard[j][k - 1] != NULL && state->currentBoard[j][k] != NULL && state->currentBoard[j][k - 1]->value == state->currentBoard[j][k]->value) {
                    state->currentBoard[j][k - 1]->value *= 2;
                    state->Currentscore = state->Currentscore + state->currentBoard[j][k - 1]->value;
					free(state->currentBoard[j][k]);
                    state->currentBoard[j][k] = NULL;
					move++;
				}
			}
		}
		break;

	case RIGHT:
		for (int i = state->size - 1; i >= 0; i--) {
			for (int j = 0; j < state->size; j++) {
				int k;
				for (k = i; k < state->size - 1 && state->currentBoard[j][k + 1] == NULL; k++) {
					if (state->currentBoard[j][k] == NULL) continue;
                    state->currentBoard[j][k + 1] = state->currentBoard[j][k];
                    state->currentBoard[j][k] = NULL;
					move++;
				}

				if (k < state->size - 1 && state->currentBoard[j][k + 1] != NULL && state->currentBoard[j][k] != NULL && state->currentBoard[j][k + 1]->value == state->currentBoard[j][k]->value) {
                    state->currentBoard[j][k + 1]->value *= 2;
                    state->Currentscore = state->Currentscore + state->currentBoard[j][k + 1]->value;
					free(state->currentBoard[j][k]);
                    state->currentBoard[j][k] = NULL;
					move++;
				}
			}
		}
		break;

	case UP:
		for (int i = 1; i < state->size; i++) {
			for (int j = 0; j < state->size; j++) {
				int k;
				for (k = i; k > 0 && state->currentBoard[k - 1][j] == NULL; k--) {
					if (state->currentBoard[k][j] == NULL) continue;
                    state->currentBoard[k - 1][j] = state->currentBoard[k][j];
                    state->currentBoard[k][j] = NULL;
					move++;
				}

				if (k > 0 && state->currentBoard[k - 1][j] != NULL && state->currentBoard[k][j] != NULL && state->currentBoard[k - 1][j]->value == state->currentBoard[k][j]->value) {
                    state->currentBoard[k - 1][j]->value *= 2;
                    state->Currentscore = state->Currentscore + state->currentBoard[k - 1][j]->value;
					free(state->currentBoard[k][j]);
                    state->currentBoard[k][j] = NULL;
					move++;
				}
			}
		}
		break;

	case DOWN:
		for (int i = state->size - 1; i >= 0; i--) {
			for (int j = 0; j < state->size; j++) {
				int k;
				for (k = i; k < state->size - 1 && state->currentBoard[k + 1][j] == NULL; k++) {
					if (state->currentBoard[k][j] == NULL) continue;
                    state->currentBoard[k + 1][j] = state->currentBoard[k][j];
                    state->currentBoard[k][j] = NULL;
					move++;
				}

				if (k < state->size - 1 && state->currentBoard[k + 1][j] != NULL && state->currentBoard[k][j] != NULL && state->currentBoard[k + 1][j]->value == state->currentBoard[k][j]->value) {
                    state->currentBoard[k + 1][j]->value *= 2;
                    state->Currentscore = state->Currentscore + state->currentBoard[k + 1][j]->value;
					free(state->currentBoard[k][j]);
                    state->currentBoard[k][j] = NULL;
					move++;
				}
			}
		}
		break;

	default: printf("[Error] An error occured >> Direction for sliding unknown.\n Please contact developpers. \n"); exit(EXIT_FAILURE); break;
	}

	return move;
}
