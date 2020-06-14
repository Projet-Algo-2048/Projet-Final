#ifndef Game
#define Game

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "GameStructs.h"
#include "Utils.h"
#include "SdlVar.h"
#include "pause.h"

#define NUMBER_OF_CASE 4
#define RECTANGLE_WIDTH 540
#define RECTANGLE_HIGH 540

#define BLOCK_HEIGH 110
#define BLOCK_WIDTH 110

int slide(Directions, GameState *);
bool canMove(GameState *);
int refreshRenderer(int, int, int, int, SDL_Color, SDL_Rect ,TTF_Font *, char* , SDL_Surface *, SDL_Texture *, GameState * , SDL_Rect , SDL_Rect , SDL_Renderer *);
int printBoardDebug (GameState *);
Box * generateNewBox(GameState *);
int game(int *, int *, int *, TTF_Font *, SDL_Renderer *, SDL_Window *, int, int);

#endif