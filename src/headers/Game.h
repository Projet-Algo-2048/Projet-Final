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

#define NUMBER_OF_CASE 4
#define RECTANGLE_WIDTH 540
#define RECTANGLE_HIGH 540

#define BLOCK_HEIGH 110
#define BLOCK_WIDTH 110

#ifndef Game
#define Game

int slide(Directions, Box * **, int);
bool canMove(Box * **, int);
int printBoard(Box * **, int , SDL_Rect , SDL_Rect , SDL_Renderer *);
Box * generateNewBox(Box * ** , int );
int game(int *, int *, int *, TTF_Font *, SDL_Renderer *, SDL_Window *);

#endif
