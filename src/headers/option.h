#ifndef option
#define option


#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "SdlVar.h"
#include "Language.h"
#include "LinkedList.h"

#define NUMBER_OF_THEME 3

int optionMenu (int *, int *, int *, int *, int *, Mix_Music *, SDL_Color , SDL_Color ,SDL_Window *, SDL_Renderer *, TTF_Font *, SDL_Surface *, SDL_Texture *);

#endif
