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

void drawBox (int (*tableau)[4], SDL_Rect chiffreRect, SDL_Rect rectangle, SDL_Renderer *renderer);

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

    int tableau[4][4]={{2, 0, 4, 8},
                        {0, 0, 64, 4},
                        {0, 0, 0, 0},
                        {128, 2, 8, 0}};

   
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
            drawBox (tableau, chiffreRect, rectangle, renderer);
            //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
            //SDL_RenderFillRect(renderer, &chiffreRect);
            SDL_SetRenderDrawColor(renderer, *red, *green, *blue, 0);

            SDL_RenderPresent(renderer);
            
        }

}

void drawBox (int (*tableau)[4], SDL_Rect chiffreRect, SDL_Rect rectangle, SDL_Renderer *renderer)
 {
    //int a,b = 1;
    Uint8 r,b,g,a;
    for (int y=0; y<4; y++) 
        {
            for (int x=0; x<4; x++)
                {
                    if ( tableau[y][x] == 0 ) { r = 150; g = 150; b = 150; a = 150; }  
			else {
				switch (tableau[y][x]) {
					case 2: r = 200; g = 200; b = 200; a = 150; break;
					case 4: r = 150; g = 150; b = 150; a = 150; break;
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
                    //SDL_Rect chiffreRect;
                    
                    chiffreRect.w = BLOCK_WIDTH;
                    chiffreRect.h = BLOCK_HEIGH;
                    chiffreRect.x = rectangle.x + chiffreRect.w * x + 20 * (x+1);
                    chiffreRect.y = rectangle.y + chiffreRect.h *y + 20* (y+1);
                    SDL_SetRenderDrawColor(renderer, r, g, b, a);
                    SDL_RenderFillRect(renderer, &chiffreRect);
                    //r += 100;
                    //b += 50;
                    //if (r>200) r=0;
                    //if (b>200) b=0;

                    
                }
            
        }
 }


    