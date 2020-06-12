

#include "headers/Main.h"
#include "drawgrid.c"


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


    /****************LOADING OF THE DIFFERENTS LANGUGES**************/

    loadLanguage(DEFAULT_LANG);
    sleep(1);


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
    /*****************opening a music***************************/
    Mix_Music *neverGonna = Mix_LoadMUS("ressources/SDL/music/Never Gonna Give You Up Original.mp3");
    if (neverGonna == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }
    //pointeur volume , empeche reinitialisation a chaque fois
    int volume = 10;
    int *pointeurVolume = NULL;
    pointeurVolume = &volume;
    /*****************loading the TITLE font********************/
    SDL_Color white = {255, 255, 255 , 0};
    int fontSIZE = 100;
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
    titleRect.y = 100;




    /***************loading the "play" font**************/
    SDL_Color red = {255, 0, 0, 0};
    fontSIZE = 40;
    //titleFONT = NULL;
    titleFONT = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSIZE);
    printfTranslationList();
    char test[20] = "";
    strcpy(test, getTranslatedText("mainMenu.pl"));
    SDL_Surface *playButtonSurface = TTF_RenderText_Solid(titleFONT, test, white);
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
    playButtonRect.y = 280;


    /***************loading the "HIGHSCORE" font**************/
    SDL_Surface *hsButtonSurface = TTF_RenderText_Solid(titleFONT, "Highscore", white);
    if (!hsButtonSurface)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_EXITWITHERROR("creation hsButtonSurface");
        }
    SDL_Texture *hsButton = SDL_CreateTextureFromSurface(renderer, hsButtonSurface);
    if (!hsButton)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_EXITWITHERROR("creation hsButton");
        }
    
    SDL_Rect hsButtonRect;
    SDL_QueryTexture(hsButton, NULL, NULL, &hsButtonRect.w, &hsButtonRect.h);
    hsButtonRect.x = (WINDOW_LARGEUR - hsButtonRect.w) / 2;
    hsButtonRect.y = 380;


/***************loading the "OPTION" font**************/
    SDL_Surface *optionButtonSurface = TTF_RenderText_Solid(titleFONT, "Options", white);
    if (!optionButtonSurface)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_EXITWITHERROR("creation optionButtonSurface");
        }
    SDL_Texture *optionButton = SDL_CreateTextureFromSurface(renderer, optionButtonSurface);
    if (!optionButton)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_EXITWITHERROR("creation optionButton");
        }
    
    SDL_Rect optionButtonRect;
    SDL_QueryTexture(optionButton, NULL, NULL, &optionButtonRect.w, &optionButtonRect.h);
    optionButtonRect.x = (WINDOW_LARGEUR - optionButtonRect.w) / 2;
    optionButtonRect.y = 480;


    /***************loading the "EXIT" font**************/
    SDL_Surface *exitButtonSurface = TTF_RenderText_Solid(titleFONT, "Exit", white);
    if (!optionButtonSurface)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_EXITWITHERROR("creation exitButtonSurface");
        }
    SDL_Texture *exitButton = SDL_CreateTextureFromSurface(renderer, exitButtonSurface);
    if (!exitButton)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_EXITWITHERROR("creation exitButton");
        }
    
    SDL_Rect exitButtonRect;
    SDL_QueryTexture(exitButton, NULL, NULL, &exitButtonRect.w, &exitButtonRect.h);
    exitButtonRect.x = (WINDOW_LARGEUR - exitButtonRect.w) / 2;
    exitButtonRect.y = 580;



//pointeur rgb , ne reinisialisie pas le theme a chaque page
int raid = 113;
int green = 0;
int blue = 0;
int a = 0;
int *pointeurRed = NULL;
int *pointeurGreen = NULL;
int *pointeurBlue = NULL;
int *pointeurA = NULL;
pointeurRed = &raid;
pointeurGreen = &green;
pointeurBlue = &blue;
pointeurA = &a;
Uint8 rred = raid;
Uint8 ggreen = green;
Uint8 bblue = blue;
Uint8 aa = a;
int theme = 1;




SDL_Event event;
SDL_bool programRUNNIG = SDL_TRUE;
int mouse_x, mouse_y;


Uint8 vvolume = volume;
Mix_VolumeMusic(vvolume);
Mix_PlayMusic(neverGonna, -1);



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
                    //switch button to red color when cursor is on it
                    //case 'play'
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
                    //case 'highscore'
                    if ((mouse_x < hsButtonRect.x + hsButtonRect.w)&&
                        (mouse_x > hsButtonRect.x) &&
                        (mouse_y < hsButtonRect.y + hsButtonRect.h)&&
                        (mouse_y > hsButtonRect.y))
                        {
                           hsButtonSurface = TTF_RenderText_Solid(titleFONT, "Highscore", red);
                           hsButton = SDL_CreateTextureFromSurface(renderer, hsButtonSurface);
                        }
                    else
                    {
                        hsButtonSurface = TTF_RenderText_Solid(titleFONT, "Highscore", white);
                        hsButton = SDL_CreateTextureFromSurface(renderer, hsButtonSurface);
                    }
                    //case 'option'
                    if ((mouse_x < optionButtonRect.x + optionButtonRect.w)&&
                        (mouse_x > optionButtonRect.x) &&
                        (mouse_y < optionButtonRect.y + optionButtonRect.h)&&
                        (mouse_y > optionButtonRect.y))
                        {
                           optionButtonSurface = TTF_RenderText_Solid(titleFONT, "Options", red);
                           optionButton = SDL_CreateTextureFromSurface(renderer, optionButtonSurface);
                        }
                    else
                    {
                        optionButtonSurface = TTF_RenderText_Solid(titleFONT, "Options", white);
                        optionButton = SDL_CreateTextureFromSurface(renderer, optionButtonSurface);
                    }
                    //case 'exit'
                    if ((mouse_x < exitButtonRect.x + exitButtonRect.w)&&
                        (mouse_x > exitButtonRect.x) &&
                        (mouse_y < exitButtonRect.y + exitButtonRect.h)&&
                        (mouse_y > exitButtonRect.y))
                        {
                           exitButtonSurface = TTF_RenderText_Solid(titleFONT, "exit", red);
                           exitButton = SDL_CreateTextureFromSurface(renderer, exitButtonSurface);
                        }
                    else
                    {
                        exitButtonSurface = TTF_RenderText_Solid(titleFONT, "exit", white);
                        exitButton = SDL_CreateTextureFromSurface(renderer, exitButtonSurface);
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    //close the window if click on 'exit'
                    if ((event.button.x < exitButtonRect.x + exitButtonRect.w)&&
                        (event.button.x > exitButtonRect.x) &&
                        (event.button.y < exitButtonRect.y + exitButtonRect.h)&&
                        (event.button.y > exitButtonRect.y))
                            programRUNNIG = SDL_FALSE;
                            
                    //launch the option menu
                    if ((event.button.x < optionButtonRect.x + optionButtonRect.w)&&
                        (event.button.x > optionButtonRect.x) &&
                        (event.button.y < optionButtonRect.y + optionButtonRect.h)&&
                        (event.button.y > optionButtonRect.y))
                            {
                                // bool afin de ferme le programme si on clique sur la croix pdnt les options
                            int trueFalse = 1;
                            trueFalse = optionMenu(&theme, &raid, &green, &blue, &volume, neverGonna, white, red, window, renderer, titleFONT, optionButtonSurface, optionButton);
                            if (trueFalse == 0)
                                programRUNNIG = SDL_FALSE;
                            
                            rred = raid;
                            ggreen = green;
                            bblue = blue;
                            } 
                    
                    //launch the game
                    if ((event.button.x < playButtonRect.x + playButtonRect.w)&&
                        (event.button.x > playButtonRect.x) &&
                        (event.button.y < playButtonRect.y + playButtonRect.h)&&
                        (event.button.y > playButtonRect.y))
                        {
                            int playTrueFalse = 1;
                            playTrueFalse = game(&raid, &green, &blue, titleFONT, renderer, window);
                            if (playTrueFalse == 0)
                                programRUNNIG = SDL_FALSE;
                        }


                    break;
                
                    
            }
    }

    //clear the window
    SDL_RenderClear(renderer);

    //draw the image to the window
    SDL_SetRenderDrawColor(renderer, rred, ggreen, bblue, 0);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, exitButton, NULL, &exitButtonRect);
    SDL_RenderCopy(renderer, optionButton, NULL, &optionButtonRect);
    SDL_RenderCopy(renderer, hsButton, NULL, &hsButtonRect);
    SDL_RenderCopy(renderer, playButton, NULL, &playButtonRect);
    SDL_RenderCopy(renderer, title, NULL, &titleRect);
    

    SDL_RenderPresent(renderer);
}




    SDL_DestroyTexture(title);
    SDL_DestroyTexture(playButton);
    SDL_DestroyTexture(hsButton);
    SDL_DestroyTexture(optionButton);
    SDL_DestroyTexture(exitButton);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeMusic(neverGonna);
    Mix_Quit();
    SDL_Quit();

}

void SDL_EXITWITHERROR (const char *message)
{
    printf("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}