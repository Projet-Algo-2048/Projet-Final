#ifndef option
#define option


#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "SdlVar.h"

#define NUMBER_OF_THEME 3

int optionMenu (int *numTheme, int *red, int *green, int *blue, int *volume, Mix_Music *music, SDL_Color color1, SDL_Color color2,SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, SDL_Surface *optionButtonSurface, SDL_Texture *optionButton);

#endif
