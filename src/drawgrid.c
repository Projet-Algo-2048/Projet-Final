#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


#define NUMBER_OF_CASE 4
#define RECTANGLE_WIDTH 540
#define RECTANGLE_HIGH 540

#define BLOCK_HEIGH 110
#define BLOCK_WIDTH 110

void drawBox (SDL_Rect chiffreRect, SDL_Rect rectangle, SDL_Renderer *renderer);

int drawGrid (int *red, int *green, int *blue, TTF_Font *font, SDL_Renderer *renderer, SDL_Window *window)
{
    //reset the screen
    SDL_RenderClear(renderer);

    //creation du rectangle pricipal
    SDL_Rect rectangle;
    rectangle.x = 50;
    rectangle.y = 120;
    rectangle.w = RECTANGLE_WIDTH;
    rectangle.h = RECTANGLE_HIGH;

   
    //creation du rectangle attribue aux couleurs des chiffres    
    SDL_Rect chiffreRect;
       
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
            drawBox (chiffreRect, rectangle, renderer);
            //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            //SDL_RenderFillRect(renderer, &chiffreRect);
            SDL_SetRenderDrawColor(renderer, *red, *green, *blue, 0);

            SDL_RenderPresent(renderer);
            
        }

}

void drawBox (SDL_Rect chiffreRect, SDL_Rect rectangle, SDL_Renderer *renderer)
 {
    int a,b = 1;
    for (int y=0; y<4; y++) 
        {
            for (int x=0; x<4; x++)
                {
                    //SDL_Rect chiffreRect;
                    
                    chiffreRect.w = BLOCK_WIDTH;
                    chiffreRect.h = BLOCK_HEIGH;
                    chiffreRect.x = rectangle.x + chiffreRect.w * x + 20 * (x+1);
                    chiffreRect.y = rectangle.y + chiffreRect.h *y + 20* (y+1);
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
                    SDL_RenderFillRect(renderer, &chiffreRect);
                    
                }
            
        }
 }


    