/**
 * @file Game.c
 * @brief This file contain function for the dourse of the game
 */

#include "headers/Game.h"

/**
 * @fn int game(GameState state)
 * @brief represente the game course
 */
int game (int *red, int *green, int *blue, TTF_Font *font, SDL_Renderer *renderer, SDL_Window *window, int size, int players) {
	
	//===============[INIT VIEW]====================

	int boxGap = RECTANGLE_WIDTH / (10 * size);
	int boxWidth = (RECTANGLE_WIDTH - boxGap * (size + 1)) / size;		// box Width depending on size
	int boxHeight = (RECTANGLE_HIGH - boxGap * (size + 1)) / size;		// box Height dependint on size

	SDL_Rect rectangle = { 50, 120, RECTANGLE_WIDTH, RECTANGLE_HIGH };	/**< position and size of the board for the SDL */
	SDL_Rect caseRect = { 0, 0, boxWidth, boxHeight };					/**< position and size of a box for the SDL */

	//loading a dedicated texture for the numbers value
	SDL_Color white = {255, 255, 255, 0};
	int fontSize = 50;
    font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSize);
	char CaseNumber [10] = "0";																//variable which will containe box value for SDL Surfacing
	SDL_Surface *numberSurface = TTF_RenderText_Solid(font, CaseNumber,white);				//creating surface
	if (!numberSurface) SDL_EXITWITHERROR("creation number surface");

	SDL_Texture *numberTexture = SDL_CreateTextureFromSurface(renderer, numberSurface);		//creating Texture
	if (!numberTexture) SDL_EXITWITHERROR("creation number texture");

	SDL_Rect numberRect;
	SDL_QueryTexture(numberTexture, NULL, NULL, &numberRect.w, &numberRect.h);				//get postion and sze of the number Texture

	SDL_bool general = SDL_TRUE;


	// =================[GAME]====================
	while (general) {																	// Play until the player want to stop

		// =================[INIT GAME]===================
		srand(time(NULL));																//necessary for random in futur statement

		GameState state;
		state.playerNumber = players;													// get parameter
		state.size = size;																// get parameter

		state.score = malloc(state.playerNumber * sizeof(int));							// Init score array depending on players parameter
		for (int i = 0; i < state.playerNumber; i++) {
			state.score[i] = 0;
		}

		state.boards = malloc(state.playerNumber * sizeof(Board));						// init board array depending on players parameters
		for (int k = 0; k < state.playerNumber; k++) {
			state.boards[k] = malloc(state.size * sizeof(Box**));						// init board depending on size parameter
			for (int i = 0; i < state.size; i++) {
				state.boards[k][i] = malloc(state.size * sizeof(Box*));
				for (int j = 0; j < state.size; j++) state.boards[k][i][j] = NULL;
			}
			state.currentBoard = state.boards[k];
			generateNewBox(&state);														// generating the first box
		}

		SDL_bool playing = SDL_TRUE;
		SDL_Event playEvent;
		int truefalse = 1;
		// ==================================================

		// ==================[GAME COURSE]===================
		int i = 0;
		while (playing) {
			state.currentPlayer = i % state.playerNumber;
			state.currentBoard = state.boards[state.currentPlayer];
			state.Currentscore = state.score[state.currentPlayer];

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
				SDL_Delay(250);

			} while (moves == 0);

			i++;
		}
		// =================================================

		// ==================[GAME OVER]====================
		for (int i = 0; i < state.playerNumber; i++) {
			printf("Score : %d\n", state.score[i]);
		}
		printf("Game Over ! \n");

		int fintf = 0;
		fintf = gameOver(red, green, blue, font, renderer, window, &state);
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
		// =================================================

		// ===================[FREEING]=====================

		free(state.score);
		for (int k = 0; k < state.playerNumber; k++) {
			for (int i = 0; i < state.size; i++) {
				for (int j = 0; j < state.size; j++) if (state.boards[k][i][j] != NULL) free(state.boards[k][i][j]);
				free(state.boards[k][i]);
			}
			free(state.boards[k]);
		}
		free(state.boards);
		// =================================================

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

/**
 * @fn int refreshRenderer(int boxGap, int red, int green, int blue, SDL_Color white, SDL_Rect numberRect,TTF_Font *font, char* CaseNumber, SDL_Surface *numberSurface, SDL_Texture *numberTexture,  GameState * state, SDL_Rect caseRect, SDL_Rect rectangle, SDL_Renderer *renderer)
 * @brief refresh th renderer to the current logic game state
 * @param too much
 * @todo decrease parameters
 */
int refreshRenderer(int boxGap, int red, int green, int blue, SDL_Color white, SDL_Rect numberRect,TTF_Font *font, char* CaseNumber, SDL_Surface *numberSurface, SDL_Texture *numberTexture,  GameState * state, SDL_Rect caseRect, SDL_Rect rectangle, SDL_Renderer *renderer){
	SDL_SetRenderDrawColor(renderer, red, green, blue, 0);							// set color to theme color 
	SDL_RenderClear(renderer);														// reset the screen 

	SDL_SetRenderDrawColor(renderer, 44, 44, 44, 255);								// set color for board background 
	SDL_RenderFillRect(renderer, &rectangle);										// draw background 

	if (state->playerNumber > 1) {
		char playerText[16] = { 0 };
		sprintf(playerText, "Player %d", state->currentPlayer + 1);

		SDL_Surface * pTextSurface = TTF_RenderText_Solid(font, playerText, white);
		SDL_Texture * pTextTexture = SDL_CreateTextureFromSurface(renderer, pTextSurface);
		
		SDL_Rect pTextRect;
		SDL_QueryTexture(pTextTexture, NULL, NULL, &pTextRect.w, &pTextRect.h);

		SDL_RenderCopy(renderer, pTextTexture, NULL, &pTextRect);
		SDL_DestroyTexture(pTextTexture);
	}
	
	Uint8 r, g, b, a;
    for (int y=0; y<state->size; y++) {
		for (int x=0; x<state->size; x++){

			caseRect.x = rectangle.x + caseRect.w * x + boxGap * (x + 1);			//position x of the current box
			caseRect.y = rectangle.y + caseRect.h * y + boxGap * (y + 1);			//position y of the current box

			//the rectangle s color depend of the number value   
			if ( state->currentBoard[y][x] == NULL ) { r = 150; g = 150; b = 150; a = 150; sprintf(CaseNumber, " ");}  
			else {
				sprintf(CaseNumber, "%d", state->currentBoard[y][x]->value);		//set CaseNumber to the current box value
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


			numberSurface = TTF_RenderText_Solid(font, CaseNumber, white);			//create Number text surface
			numberTexture = SDL_CreateTextureFromSurface(renderer, numberSurface);	//create number text texture

			numberRect.x = caseRect.x + (caseRect.w - numberRect.w) / 2;			//set number tex texure position x
			numberRect.y = caseRect.y + (caseRect.h - numberRect.h) / 2;			//set number tex texure position y

			SDL_SetRenderDrawColor(renderer, r, g, b, a);							//Set color to the current selected color
			SDL_RenderFillRect(renderer, &caseRect);								//set a rect of this color on the render

			SDL_RenderCopy(renderer, numberTexture, NULL, &numberRect);				//Copy number text texure on the render
					
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
            if (state->currentBoard[i][j] == NULL) return true;	//Empty box
            if (j != state->size - 1 && state->currentBoard[i][j] != NULL && state->currentBoard[i][j + 1] != NULL && state->currentBoard[i][j]->value == state->currentBoard[i][j + 1]->value) return true;	// same value on 2 box side by side x
            if (i != state->size - 1 && state->currentBoard[i][j] != NULL && state->currentBoard[i + 1][j] != NULL && state->currentBoard[i][j]->value == state->currentBoard[i + 1][j]->value) return true;	// same value on 2 box side by side y
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
				//shift box as much as possible
				for (k = i; k > 0 && state->currentBoard[j][k - 1] == NULL; k--) {
					if (state->currentBoard[j][k] == NULL) continue;
                    state->currentBoard[j][k - 1] = state->currentBoard[j][k];
                    state->currentBoard[j][k] = NULL;
					move++;
				}

				//fusion
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
				//shift box as much as possible
				for (k = i; k < state->size - 1 && state->currentBoard[j][k + 1] == NULL; k++) {
					if (state->currentBoard[j][k] == NULL) continue;
                    state->currentBoard[j][k + 1] = state->currentBoard[j][k];
                    state->currentBoard[j][k] = NULL;
					move++;
				}

				//fusion
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
				//shift box as much as possible
				for (k = i; k > 0 && state->currentBoard[k - 1][j] == NULL; k--) {
					if (state->currentBoard[k][j] == NULL) continue;
                    state->currentBoard[k - 1][j] = state->currentBoard[k][j];
                    state->currentBoard[k][j] = NULL;
					move++;
				}

				//fusion
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
				//shift box as much as possible
				for (k = i; k < state->size - 1 && state->currentBoard[k + 1][j] == NULL; k++) {
					if (state->currentBoard[k][j] == NULL) continue;
                    state->currentBoard[k + 1][j] = state->currentBoard[k][j];
                    state->currentBoard[k][j] = NULL;
					move++;
				}

				//fusion
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

	default: printf("[Error] An error occured >> Direction for sliding unknown.\n Please contact developpers. \n"); exit(EXIT_FAILURE); break;	//change exit -> not free correctly
	}

	return move;
}