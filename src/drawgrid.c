#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define NUMBER_OF_CASE 4
#define RECTANGLE_WIDTH 540
#define RECTANGLE_HIGH 540

int drawGrid (int *red, int *green, int *blue,  SDL_Renderer *renderer, SDL_Window *window)
{
    //reset the screen
    SDL_RenderClear(renderer);

    //creation d un rectangle gris
    SDL_Rect rectangle;
    rectangle.x = 50;
    rectangle.y = 120;
    rectangle.w = RECTANGLE_WIDTH;
    rectangle.h = RECTANGLE_HIGH;

   
    


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

            ///draw the image to the window
            SDL_SetRenderDrawColor(renderer, 44, 44, 44, 255);
            SDL_RenderFillRect(renderer, &rectangle);
            SDL_SetRenderDrawColor(renderer, *red, *green, *blue, 0);

            SDL_RenderPresent(renderer);
        }

}