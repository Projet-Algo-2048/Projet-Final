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

	int boxGap = RECTANGLE_WIDTH / (10 * size);
	int boxWidth = (RECTANGLE_WIDTH - boxGap * (size + 1)) / size;
	int boxHeight = (RECTANGLE_HIGH - boxGap * (size + 1)) / size;

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

	SDL_bool general = SDL_TRUE;

	while (general) {

		/* initialisation of the game */
		srand(time(NULL));                      //necessary for random in futur statement

		GameState state;
		state.playerNumber = 2;
		state.size = size;
		state.score = malloc(state.playerNumber * sizeof(int));
		for (int i = 0; i < state.playerNumber; i++) {
			state.score[i] = 0;
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

		SDL_bool playing = SDL_TRUE;
		SDL_Event playEvent;
		int truefalse = 1;

		/* Course of the game */
		int i = 0;
		while (playing) {
			state.currentPlayer = i % state.playerNumber;
			state.currentBoard = state.boards[state.currentPlayer];
			state.Currentscore = state.score[state.currentPlayer];
			//printf("c'estau tour du joueur %d de jouer \n", state.currentPlayer + 1);

			generateNewBox(&state);
			printBoardDebug(&state);

			if (!canMove(&state)) break;

			int moves = 0;
			do {
				while (SDL_PollEvent(&playEvent)) {
					switch (playEvent.type) {
					case SDL_QUIT:
						playing = SDL_FALSE;
						return 0;
						break;

					case SDL_KEYDOWN:
						switch (playEvent.key.keysym.sym) {

						case SDLK_LEFT: moves = slide(LEFT, &state); break;
						case SDLK_RIGHT: moves = slide(RIGHT, &state); break;
						case SDLK_UP: moves = slide(UP, &state); break;
						case SDLK_DOWN: moves = slide(DOWN, &state); break;

						case SDLK_ESCAPE:

							//bool afin fermer completement prog ou non dependament du choix ds le sub menu pause
							truefalse = pauseMenu(red, green, blue, font, renderer, window);
							if (truefalse == 0) {
								playing = SDL_FALSE;
								return 0;
							}
							else if (truefalse == 2) {
								playing = SDL_FALSE;
								return 1;
							}

							break;

						}
						break;
					}

				}
				//refresh view when event occured
				refreshRenderer(boxGap, *red, *green, *blue, white, numberRect, font, CaseNumber, numberSurface, numberTexture, &state, caseRect, rectangle, renderer);
				SDL_RenderPresent(renderer);

			} while (moves == 0);

			i++;
		}

		/* Game over*/;
		for (int i = 0; i < state.playerNumber; i++) {
			printf("Score : %d\n", state.score[i]);
		}
		printf("Game Over ! \n");

		int fintf = 0;
		fintf = gameOver(red, green, blue, font, renderer, window);
		if (fintf == 0)
		{
			general = SDL_FALSE;
			return 0;
		}
		else if (fintf == 2)
		{
			general = SDL_FALSE;
			return 1;
		}

		/* freeing memory */
		for (int k = 0; k < state.playerNumber; k++) {
			for (int i = 0; i < state.size; i++) {
				for (int j = 0; j < state.size; j++) if (state.boards[k][i][j] != NULL) free(state.boards[k][i][j]);
				free(state.boards[k][i]);
			}
			free(state.boards[k]);
		}
		free(state.boards);

		playing = SDL_FALSE;
	}
	return 1;
}
/**
 * @fn generateNewBox(int size, Box * board[size][size])
 * @brief add a new box to the game. Need srand(time(NULL) been called before
 * @param size the size of the following array
 * @param board 2D array 
 * @return the box generated
 */
Box * generateNewBox(GameState * state) {
	Box*** emptyBoxes = malloc(state->size * state->size * sizeof(Box**));
	for (int i = 0; i < state->size * state->size; i++) emptyBoxes[i] = NULL;

	int k = 0;
	for (int i = 0; i < state->size; i++) {
		for (int j = 0; j < state->size; j++) {
			if (state->currentBoard[i][j] == NULL) emptyBoxes[k++] = &(state->currentBoard[i][j]);
		}
	}

	int index = (k == 0) ? 0 : rand() % k;

	Box* box = (Box*)malloc(sizeof(Box));
	box->value = power(2, (rand() % 2) + 1);

	*(emptyBoxes[index]) = box;
	free(emptyBoxes);
	return box;
/*
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
	*/
}

/**
 * @fn int printboard1(Box*** board1, int size)
 * @brief just a debug function that print the board1
 */
int printBoardDebug(GameState * state) {
    for (int i = 0; i < state->size; i++) {
        for (int j = 0; j < state->size; j++) {
            (state->currentBoard[i][j] == NULL) ? printf("   |") : printf(" %d |", state->currentBoard[i][j]->value);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int refreshRenderer(int boxGap, int red, int green, int blue, SDL_Color white, SDL_Rect numberRect,TTF_Font *font, char* CaseNumber, SDL_Surface *numberSurface, SDL_Texture *numberTexture,  GameState * state, SDL_Rect caseRect, SDL_Rect rectangle, SDL_Renderer *renderer){
	SDL_SetRenderDrawColor(renderer, red, green, blue, 0);	// set color to theme color 
	SDL_RenderClear(renderer);								// reset the screen 

	SDL_SetRenderDrawColor(renderer, 44, 44, 44, 255);		// set color for board background 
	SDL_RenderFillRect(renderer, &rectangle);				// draw background 
	
	Uint8 r, g, b, a;
    for (int y=0; y<state->size; y++) {
		for (int x=0; x<state->size; x++){

			caseRect.x = rectangle.x + caseRect.w * x + boxGap * (x + 1);			//position x of the current box
			caseRect.y = rectangle.y + caseRect.h * y + boxGap * (y + 1);			//position y of the current box

			//the rectangle s color depend of the number value   
			if ( state->currentBoard[y][x] == NULL ) { r = 150; g = 150; b = 150; a = 150; sprintf(CaseNumber, " ");}  
			else {
				sprintf(CaseNumber, "%d", state->currentBoard[y][x]->value);
				switch (state->currentBoard[y][x]->value) {
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