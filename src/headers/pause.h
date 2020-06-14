#ifndef pause
#define pause

#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "SdlVar.h"
#include "Language.h"
#include "LinkedList.h"

int pauseMenu (int *, int *, int *, TTF_Font *, SDL_Renderer *, SDL_Window *);
int gameOver (int *, int *, int *, TTF_Font *, SDL_Renderer *, SDL_Window *);

#endif