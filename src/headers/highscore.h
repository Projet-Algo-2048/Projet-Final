#ifndef HIGHSCORE
#define HIGHSCORE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

#include "SdlVar.h"
#include "Language.h"
#include "LinkedList.h"

#define HIGH_SCORE_FILE_NAME "HS.txt"
#define MAX_SCORE_TO_PRINT 10
#define MAX_LENGHT_PLAYER_NAME 256
#define MIN_SCORE_LENGHT 5
#define MAX_SCORE_PRINT 5

typedef struct {
    int score;
    char player[MAX_LENGHT_PLAYER_NAME];
} PlayerScore;

int searchiInStringArray(char * , PlayerScore * , int );
void tri (int , PlayerScore *);
int setScore();
int printHighScore(int *, int *, int *, TTF_Font *, SDL_Renderer *, SDL_Window * );

#endif