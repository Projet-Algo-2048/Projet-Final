/**
 * @file Game.c
 * @brief This file contain function for the dourse of the game
 */

#include "headers/Game.h"

/**
 * @fn int game(GameState state)
 * @brief represente the game course
 */
int game (int *red, int *green, int *blue, TTF_Font *font, SDL_Renderer *renderer, SDL_Window *window, int size) {
   //SDL_RenderClear(renderer); reset renderer

	GameState state;
	state.size = size;

	int boxGap = RECTANGLE_WIDTH / (10 * (state.size));
	int boxWidth = (RECTANGLE_WIDTH - boxGap * (state.size + 1)) / state.size;
	int boxHeight = (RECTANGLE_HIGH - boxGap * (state.size + 1)) / state.size;

	SDL_Rect rectangle = { 50, 120, RECTANGLE_WIDTH, RECTANGLE_HIGH };	/**< the board main rectangle */
	SDL_Rect caseRect = { 0, 0, boxWidth, boxHeight };					/**< a box rectangle */

	//loading a dedicated texture for the numbers value
	SDL_Color white = {255, 255, 255, 0};
	int fontSize = 50;
    font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSize);
	char CaseNumber [10] = "0";
	SDL_Surface *numberSurface = TTF_RenderText_Solid(font, CaseNumber,white);
	if (!numberSurface) SDL_EXITWITHERROR("creation number surface");

	SDL_Texture *numberTexture = SDL_CreateTextureFromSurface(renderer, numberSurface);
	if (!numberTexture) SDL_EXITWITHERROR("creation number texture");

	SDL_Rect numberRect;
	SDL_QueryTexture(numberTexture, NULL, NULL, &numberRect.w, &numberRect.h);


    /* initialisation of the game */
    state.board = malloc(state.size * sizeof(Box **));
	for (int i = 0; i < state.size; i++) {
		state.board[i] = malloc(state.size * sizeof(Box*));
		for (int j = 0; j < state.size; j++) state.board[i][j] = NULL;
	}
    srand(time(NULL));
    generateNewBox(state.board, state.size);

	SDL_bool playing = SDL_TRUE;
	SDL_Event playEvent;
	int truefalse = 1;

    /* Course of the game */
	while (playing) {
		generateNewBox(state.board, state.size);
		printBoardDebug(state.board, state.size);
        	
        if (!canMove(state.board, state.size)) break;

        int moves = 0;
        do {
            while(SDL_PollEvent(&playEvent)) {
				switch(playEvent.type) {
					case SDL_QUIT:
						playing = SDL_FALSE;
						return 0;
					break;

					case SDL_KEYDOWN:
						switch(playEvent.key.keysym.sym) {

							case SDLK_LEFT: moves = slide(LEFT, state.board, state.size); break;
							case SDLK_RIGHT: moves = slide(RIGHT, state.board, state.size); break;
							case SDLK_UP: moves = slide(UP, state.board, state.size); break;
							case SDLK_DOWN: moves = slide(DOWN, state.board, state.size); break;

							case SDLK_ESCAPE:

								//bool afin fermer completement prog ou non dependament du choix ds le sub menu pause
								truefalse = pauseMenu(red, green, blue, font, renderer, window);
								if (truefalse == 0) {
									playing = SDL_FALSE;
									return 0;
								} else if (truefalse == 2) {
									playing = SDL_FALSE;
									return 1;
								}
									
							break;

						}
					break;
				}

			}
			//refresh view when event occured
			refreshRenderer(boxGap, *red, *green, *blue, white, numberRect, font, CaseNumber, numberSurface, numberTexture, state.board, state.size, caseRect, rectangle, renderer);
			SDL_RenderPresent(renderer);

        } while (moves == 0);
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

	SDL_DestroyTexture(numberTexture);
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
 * @fn int printBoardDebug(Box*** board, int size, SDL_Rect caseRect, SDL_Rect rectangle, SDL_Renderer *renderer)
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


int refreshRenderer(int boxGap, int red, int green, int blue, SDL_Color white, SDL_Rect numberRect,TTF_Font *font, char* CaseNumber, SDL_Surface *numberSurface, SDL_Texture *numberTexture,  Box * ** board, int size, SDL_Rect caseRect, SDL_Rect rectangle, SDL_Renderer *renderer){
	SDL_SetRenderDrawColor(renderer, red, green, blue, 0);	// set color to theme color 
	SDL_RenderClear(renderer);								// reset the screen 

	SDL_SetRenderDrawColor(renderer, 44, 44, 44, 255);		// set color for board background 
	SDL_RenderFillRect(renderer, &rectangle);				// draw background 
	
	Uint8 r, g, b, a;
    for (int y=0; y<size; y++) {
		for (int x=0; x<size; x++){

			caseRect.x = rectangle.x + caseRect.w * x + boxGap * (x + 1);			//position x of the current box
			caseRect.y = rectangle.y + caseRect.h * y + boxGap * (y + 1);			//position y of the current box

			//the rectangle s color depend of the number value   
			if ( board[y][x] == NULL ) { r = 150; g = 150; b = 150; a = 150; sprintf(CaseNumber, " ");}  
			else {
				sprintf(CaseNumber, "%d", board[y][x]->value);
				switch (board[y][x]->value) {
					case 2: r = 200; g = 200; b = 200; a = 150; break;
					case 4: r = 0; g = 0; b = 0; a = 150; break;
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


			numberSurface = TTF_RenderText_Solid(font, CaseNumber, white);
			numberTexture = SDL_CreateTextureFromSurface(renderer, numberSurface);	

			numberRect.x = caseRect.x + (caseRect.w - numberRect.w) / 2;
			numberRect.y = caseRect.y + (caseRect.h - numberRect.h) / 2;

			SDL_SetRenderDrawColor(renderer, r, g, b, a);
			SDL_RenderFillRect(renderer, &caseRect);

			SDL_RenderCopy(renderer, numberTexture, NULL, &numberRect);
					
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