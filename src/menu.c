#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define WINDOW_LARGEUR 640
#define WINDOW_HAUTEUR 480

void SDL_EXITWITHERROR (const char *message);

int main ()
{

    /*********************INITIALISATION**********************/

    // initialisation of SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_EXITWITHERROR("initialisation SDL");

    //initialisation SDL_MIXER
    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
        {
            printf("Erreur initialisation SDL_mixer : %s", Mix_GetError());
            SDL_Quit();
            exit(EXIT_FAILURE);
        }
    //initialisation SDL_ttf
    if (TTF_Init() != 0)
        {
            printf("Erreur : initialisation TTF %s\n", TTF_GetError());
            Mix_CloseAudio();
            SDL_Quit();
            exit(EXIT_FAILURE);
        }


    /******************************************************/


    //creating a window
    SDL_Window *window = SDL_CreateWindow("2048 : The game",
                                                SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                                                WINDOW_LARGEUR, WINDOW_HAUTEUR, 0);
    
    //check the creation of the window
    if (window == NULL)
        SDL_EXITWITHERROR("creation fenetre");

    // creating a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 1, SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        SDL_EXITWITHERROR("creation renderer");


    /*****************loading the TITLE font********************/
    SDL_Color white = {255, 255, 255 , 0};
    int fontSIZE = 70;
    //loading a font
    TTF_Font *titleFONT = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSIZE);
    if (!titleFONT)
        {
          printf("ERREUR: ouverture font %s\n", TTF_GetError());
          Mix_CloseAudio();
          SDL_Quit();
        }
    //creating a texture from a surface 
    SDL_Surface *titleSurface = TTF_RenderText_Solid(titleFONT, "2048", white);
    if (!titleSurface)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_EXITWITHERROR("creation titleSurface");
        }
    SDL_Texture *title = SDL_CreateTextureFromSurface(renderer, titleSurface);
    if (!title)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_EXITWITHERROR("creation titleSurface");
        }
    SDL_FreeSurface(titleSurface);
    SDL_Rect titleRect;
    SDL_QueryTexture(title, NULL, NULL, &titleRect.w, &titleRect.h);
    titleRect.x = (WINDOW_LARGEUR - titleRect.w) / 2;
    titleRect.y = 10;




    /***************loading the "play" font**************/
    SDL_Color red = {255, 0, 0, 0};
    fontSIZE = 40;
    //titleFONT = NULL;
    titleFONT = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSIZE);
    SDL_Surface *playButtonSurface = TTF_RenderText_Solid(titleFONT, "Play", white);
    if (!playButtonSurface)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_EXITWITHERROR("creation titleSurface");
        }
    SDL_Texture *playButton = SDL_CreateTextureFromSurface(renderer, playButtonSurface);
    if (!playButton)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_EXITWITHERROR("creation titleSurface");
        }
    //SDL_FreeSurface(playButtonSurface);
    SDL_Rect playButtonRect;
    SDL_QueryTexture(playButton, NULL, NULL, &playButtonRect.w, &playButtonRect.h);
    playButtonRect.x = (WINDOW_LARGEUR - playButtonRect.w) / 2;
    playButtonRect.y = 180;



SDL_Event event;
SDL_bool programRUNNIG = SDL_TRUE;
int mouse_x, mouse_y;
while (programRUNNIG)
{
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
            {
                case SDL_QUIT:
                    programRUNNIG = SDL_FALSE;
                    break;

                case SDL_MOUSEMOTION:
                    
                    mouse_x = event.motion.x;
                    mouse_y = event.motion.y;
                    if ((mouse_x < playButtonRect.x + playButtonRect.w)&&
                        (mouse_x > playButtonRect.x) &&
                        (mouse_y < playButtonRect.y + playButtonRect.h)&&
                        (mouse_y > playButtonRect.y))
                        {
                           playButtonSurface = TTF_RenderText_Solid(titleFONT, "Play", red);
                           playButton = SDL_CreateTextureFromSurface(renderer, playButtonSurface);
                        }
                    else
                    {
                        playButtonSurface = TTF_RenderText_Solid(titleFONT, "Play", white);
                        playButton = SDL_CreateTextureFromSurface(renderer, playButtonSurface);
                    }
                    
                    
            }
    }

    //clear the window
    SDL_RenderClear(renderer);

    //draw the image to the window
    SDL_RenderCopy(renderer, playButton, NULL, &playButtonRect);
    SDL_RenderCopy(renderer, title, NULL, &titleRect);
    

    SDL_RenderPresent(renderer);
}




    SDL_DestroyTexture(title);
    SDL_DestroyTexture(playButton);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

void SDL_EXITWITHERROR (const char *message)
{
    printf("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}