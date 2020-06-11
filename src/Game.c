/**
 * @file Game.c
 * @brief This file contain function for the dourse of the game
 */

#include "headers/Game.h"

/**
 * @fn int game(GameState state)
 * @brief represente the game course
 */
int game (int *red, int *green, int *blue, TTF_Font *font, SDL_Renderer *renderer, SDL_Window *window) {

   //reset the screen
   SDL_RenderClear(renderer);
	 

	 //const Uint8 redBG = (const Uint8)red;
	
   //creation of the main rectangle
	SDL_Rect rectangle;
	rectangle.x = 50;
	rectangle.y = 120;
	rectangle.w = RECTANGLE_WIDTH;
	rectangle.h = RECTANGLE_HIGH;

	//creation of the number's color rectangle
	SDL_Rect chiffreRect;

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

	SDL_bool playing = SDL_TRUE;
	SDL_Event playEvent;

    /* Course of the game */
	
	
		while (playing) {
			SDL_RenderClear(renderer);
        	generateNewBox(state.board, state.size);
			printBoardDebug(state.board, state.size);
        	SDL_SetRenderDrawColor(renderer, 44, 44, 44, 255);
			SDL_RenderFillRect(renderer, &rectangle);
			printBoard(state.board, state.size, chiffreRect, rectangle, renderer );
			SDL_SetRenderDrawColor(renderer, *red, *green, *blue, 0);

			SDL_RenderPresent(renderer);
			

        	if (!canMove(state.board, state.size)) break;

        	int moves = 0;
        	do {
            	while(SDL_PollEvent(&playEvent))
					{
						switch(playEvent.type)
							{
								case SDL_QUIT:
									playing = SDL_FALSE;
									return 0;
								break;

								case SDL_KEYDOWN:
									switch(playEvent.key.keysym.sym)
										{
											case SDLK_LEFT:
												moves = slide(LEFT, state.board, state.size);
											break;

											case SDLK_RIGHT:
												moves = slide(RIGHT, state.board, state.size);
											break;
											
											case SDLK_UP:
												moves = slide(UP, state.board, state.size);
											break;

											case SDLK_DOWN:
												moves = slide(DOWN, state.board, state.size);
											break;

										}
								break;
							}
					}
            	//if (moves == 0) printf("2Can not move like that %c\n", c);
        	} while (moves == 0);

			//clear the screen
			SDL_RenderClear(renderer);

			//draw the image to the window
			SDL_SetRenderDrawColor(renderer, 44, 44, 44, 255);
			SDL_RenderFillRect(renderer, &rectangle);
			printBoard(state.board, state.size, chiffreRect, rectangle, renderer );
			SDL_SetRenderDrawColor(renderer, *red, *green, *blue, 0);

			SDL_RenderPresent(renderer);
			//printf("test\n");

		}
		printf("Game Over ! \n");

    	/* freeing memory */
    	for (int i = 0; i < state.size; i++) {
        	for (int j = 0; j < state.size; j++) if (state.board[i][j] != NULL) free(state.board[i][j]);
        	free(state.board[i]);
    	}
    	free(state.board);
		playing = SDL_FALSE;
		return 1;
	
}

/**
 * @fn generateNewBox(int size, Box * board[size][size])
 * @brief add a new box to the game. Need srand(time(NULL) been called before
 * @param size the size of the following array
 * @param board 2D array 
 * @return the box generated
 */

Box * generateNewBox(Box * **board, int size) {
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
    Box * box = (Box *) malloc( sizeof(Box) );
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
        generateNewBox(board, size);
    }

    return box;
	*/
}

/**
 * @fn int printBoard(Box*** board, int size, SDL_Rect chiffreRect, SDL_Rect rectangle, SDL_Renderer *renderer)
 * @brief just a debug function that print the board
 */


int printBoardDebug (Box * ** board, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            (board[i][j] == NULL) ? printf("   |") : printf(" %d |", board[i][j]->value);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}


int printBoard (Box * ** board, int size, SDL_Rect chiffreRect, SDL_Rect rectangle, SDL_Renderer *renderer){
	Uint8 r, g, b, a;
	printf("du biff\n");
	//printBoardDebug(board, size);
    for (int y=0; y<size; y++) {
		for (int x=0; x<size; x++){
			//the rectangle s color depend of the number value   
			if ( board[y][x] == NULL ) { r = 150; g = 150; b = 150; a = 150; }  
			else {
				switch (board[y][x]->value) {
					case 2: r = 200; g = 200; b = 200; a = 150; break;
					case 4: r = 150; g = 150; b = 150; a = 150; break;
					case 8: r = 100; g = 100; b = 100; a = 150; break;
					case 16: r = 250; g = 0; b = 0; a = 150; break;
					case 32: r = 200; g = 0; b = 0; a = 150; break;
					case 64: r = 100; g = 0; b = 0; a = 150; break;
					case 128: r = 250; g = 250; b = 0; a = 150; break;
					case 256: r = 200; g = 200; b = 0; a = 150; break;
					case 512: r = 100; g = 100; b = 0; a = 150; break;
					case 1024: r = 0; g = 100; b = 0; a = 150; break;
					case 2048: r = 0; g = 200; b = 0; a = 150; break;
					default: r = 250; g = 250; b = 250; a = 150;
				}
			}  

            chiffreRect.w = BLOCK_WIDTH;
			chiffreRect.h = BLOCK_HEIGH;
			chiffreRect.x = rectangle.x + chiffreRect.w * x + 20 * (x+1);
			chiffreRect.y = rectangle.y + chiffreRect.h * y + 20 * (y+1);
			SDL_SetRenderDrawColor(renderer, r, g, b, a);
			SDL_RenderFillRect(renderer, &chiffreRect);
					
        }
    }
	return 0;
 }









/**
 * @fn bool canMove(int** board, int size)
 * @brief chech if a move is possible
 * @param board the game board
 * @param the size of the game board
 * @return true if a move is possible false otherwise
 */
bool canMove(Box * ** board, int size) {
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
int slide(Directions dir, Box * ** board, int size) {

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