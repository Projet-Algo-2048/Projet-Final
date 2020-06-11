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
     GameState state;
     state.size = 4;

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
   Box*** board;
   i++;

   if (i % 2 == 0) {
       printf("c'est au joueur 1 de jouer\n");
        board = state.board1;
   }
   else {
       printf("c'est au joueur 2 de jouer\n");
       board = state.board2;
   }

         generateNewBox(board, state.size);
         printBoard(board, state.size);

         if (!canMove(board, state.size)) break;

         int moves = 0;
         do {
             int c;
             do {
                 printf("Bouger le plateau : ");
                 scanf("%d", &c);
             } while (c != 2 && c != 6 && c != 8 && c != 4);
             switch (c) {
             case 4: moves = slide(LEFT, board, state.size); break;
             case 6: moves = slide(RIGHT, board, state.size); break;
             case 8: moves = slide(UP, board, state.size); break;
             case 2: moves = slide(DOWN, board, state.size); break;

           }
             if (moves == 0) printf("2Can not move like that %c\n", c);
         } while (moves == 0);
 	}
 	printf("Game Over ! \n");
     /* freeing memory */
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
 }


/**
 * @fn generateNewBox(int size, Box * board1[size][size])
 * @brief add a new box to the game. Need srand(time(NULL) been called before
 * @param size the size of the following array
 * @param board1 2D array
 * @return the box generated
 */
Box * generateNewBox(Box * **board1, int size) {
    Box * box = (Box *) malloc( sizeof(Box) );
    if (box == NULL) {
        printf("[ERROR] An error occured >> Could not allocate memory for new Box !");
        exit(EXIT_FAILURE);
    }

    int i, j;
    i = rand() % 4;
    j = rand() % 4;

    box->value = pow(2, (rand() % 2) + 1);

    if (board1[i][j] == NULL) {
        board1[i][j] = box;
        return box;

    }
    else {
        free(box);
        generateNewBox(board1, size);
    }

    return box;
  }


/**
 * @fn int printboard1(Box*** board1, int size)
 * @brief just a debug function that print the board1
 */
int printBoard(Box * ** board, int size) {
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
 * @fn bool canMove(int** board1, int size)
 * @brief chech if a move is possible
 * @param board1 the game board1
 * @param the size of the game board1
 * @return true if a move is possible false otherwise
 */
bool canMove(Box * ** board1, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board1[i][j] == NULL) return true;
            if (j != size - 1 && board1[i][j] != NULL && board1[i][j + 1] != NULL && board1[i][j]->value == board1[i][j + 1]->value) return true;
            if (i != size - 1 && board1[i][j] != NULL && board1[i + 1][j] != NULL && board1[i][j]->value == board1[i + 1][j]->value) return true;
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
int slide(Directions dir, Box * ** board1, int size) {

	int move = 0;
	switch (dir) {
		case LEFT:
		for (int i = 1; i < size; i++) {
			for (int j = 0; j < size; j++) {
				int k;
				for (k = i; k > 0 && board1[j][k - 1] == NULL; k--) {
					if (board1[j][k] == NULL) continue;
					board1[j][k - 1] = board1[j][k];
					board1[j][k] = NULL;
					move++;
				}

				if (k > 0 && board1[j][k - 1] != NULL && board1[j][k] != NULL && board1[j][k - 1]->value == board1[j][k]->value) {
					board1[j][k - 1]->value *= 2;
					free(board1[j][k]);
                    board1[j][k] = NULL;
					move++;
				}
			}
		}
		break;

	case RIGHT:
		for (int i = size - 1; i >= 0; i--) {
			for (int j = 0; j < size; j++) {
				int k;
				for (k = i; k < size - 1 && board1[j][k + 1] == NULL; k++) {
					if (board1[j][k] == NULL) continue;
					board1[j][k + 1] = board1[j][k];
					board1[j][k] = NULL;
					move++;
				}

				if (k < size - 1 && board1[j][k + 1] != NULL && board1[j][k] != NULL && board1[j][k + 1]->value == board1[j][k]->value) {
					board1[j][k + 1]->value *= 2;
					free(board1[j][k]);
                    board1[j][k] = NULL;
					move++;
				}
			}
		}
		break;

	case UP:
		for (int i = 1; i < size; i++) {
			for (int j = 0; j < size; j++) {
				int k;
				for (k = i; k > 0 && board1[k - 1][j] == NULL; k--) {
					if (board1[k][j] == NULL) continue;
					board1[k - 1][j] = board1[k][j];
					board1[k][j] = NULL;
					move++;
				}

				if (k > 0 && board1[k - 1][j] != NULL && board1[k][j] != NULL && board1[k - 1][j]->value == board1[k][j]->value) {
					board1[k - 1][j]->value *= 2;
					free(board1[k][j]);
                    board1[k][j] = NULL;
					move++;
				}
			}
		}
		break;

	case DOWN:
		for (int i = size - 1; i >= 0; i--) {
			for (int j = 0; j < size; j++) {
				int k;
				for (k = i; k < size - 1 && board1[k + 1][j] == NULL; k++) {
					if (board1[k][j] == NULL) continue;
					board1[k + 1][j] = board1[k][j];
					board1[k][j] = NULL;
					move++;
				}

				if (k < size - 1 && board1[k + 1][j] != NULL && board1[k][j] != NULL && board1[k + 1][j]->value == board1[k][j]->value) {
					board1[k + 1][j]->value *= 2;
					free(board1[k][j]);
                    board1[k][j] = NULL;
					move++;
				}
			}
		}
		break;

	default: printf("[Error] An error occured >> Direction for sliding unknown.\n Please contact developpers. \n"); exit(EXIT_FAILURE); break;
	}

	return move;
}
