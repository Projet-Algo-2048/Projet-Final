#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define NUMBER_OF_CASE 4

int drawGrid (int *red, int *blue, int *green, SDL_Renderer *renderer, SDL_Window *window)
{
    //reset the screen
    SDL_RenderClear(renderer);

    //creation d un rectangle gris
    SDL_Surface *rectangle = SDL_CreateRGBSurface(0, 450, 450 , 32, 0, 0, 0, 0);
    if (!rectangle)
        {
            SDL_EXITWITHERROR("creation rectangle");
        }
    SDL_FillRect(rectangle, NULL, SDL_MapRGB(rectangle->format, 44, 44, 44));
    SDL_Texture *rectTexture = SDL_CreateTextureFromSurface(renderer, rectangle);
    SDL_FreeSurface(rectangle);
    SDL_Rect Rect;
    SDL_QueryTexture(rectTexture, NULL, NULL, &Rect.w, &Rect.h);


    SDL_bool playing = SDL_TRUE;
    SDL_Event playEvent;

    while(playing)
        {
            while(SDL_PollEvent(&playEvent))
                {
                    switch(playEvent.type)
                        {
                            case SDL_QUIT:
                                playing = SDL_FALSE;
                                return 0;
                            break;

                            case SDL_KEYDOWN:
                                switch (playEvent.key.keysym.sym)
                                    {
                                        case SDLK_ESCAPE:
                                            playing = SDL_FALSE;
                                            return 1;
                                        break;
                                    }
                        }
                }

            

            //clear the screen
            SDL_RenderClear(renderer);

            //SDL_SetRenderDrawColor(renderer, *red, *green, *blue, 0);
            //SDL_RenderClear(renderer);

            

            //draw the images to the window
            SDL_RenderCopy(renderer, rectTexture, NULL, NULL);
            SDL_SetRenderDrawColor(renderer, *red, *green, *blue, 0);
            SDL_RenderPresent(renderer);
        }

}