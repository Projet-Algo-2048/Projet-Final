#include <SDL2/SDL.h> 
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h> 




void SDL_EXITWITHERROR (const char *message);
int miam (int foodx, int foody, int foodw, int foodh, int shrekx, int shreky, int shrekw, int shrekh);
 

#define window_largeur 640*1.5
#define window_hauteur 480*1.5
#define PIXEL_SPEED 500 



int main(int argc, char* argv[]) 
{
    if (SDL_Init(SDL_INIT_VIDEO ) != 0)
        SDL_EXITWITHERROR("initialisation SDL");

    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur initialisation SDL_mixer : %s", Mix_GetError());
        SDL_Quit();
        return -1;
    }

    Mix_Music* music = Mix_LoadMUS("ressources/SDL/music/smash-mouth-all-star.wav");

    if (music == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }

    Mix_PlayMusic(music, -1);

    if (TTF_Init() != 0)
        {
            printf("TTF_Init: %s\n", TTF_GetError());
            exit(EXIT_FAILURE);
        }

    TTF_Font *font = TTF_OpenFont("ressources/SDL/font/JLR Star Shrek.ttf",70);
    if (font == NULL)
        {
            printf("TTF_Init: %s\n", TTF_GetError());
            exit(EXIT_FAILURE);
        }

    TTF_Font *gamefont = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",20);
    if (gamefont == NULL)
        {
            printf("TTF_Init: %s\n", TTF_GetError());
            exit(EXIT_FAILURE);
        }
    

    SDL_Window* pWindow = NULL;
    SDL_Renderer* pRenderer = NULL;
    SDL_Event events;
    SDL_bool close = SDL_FALSE;

    if (SDL_CreateWindowAndRenderer(window_largeur, window_largeur, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur creation fenetre et rendue SDL : %s", SDL_GetError());
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }



    //load the image into memory using SDL_image library function 
    SDL_Surface* surface = IMG_Load("ressources/SDL/hello.png");
    if (!surface)
        {
            SDL_DestroyRenderer(pRenderer);
            SDL_DestroyWindow(pWindow);
            SDL_EXITWITHERROR("image load");

        }

    //load the image data into the graphics hardware's memory 
    SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, surface);
    SDL_FreeSurface(surface);
    if (!texture)
        {
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(pRenderer);
            SDL_DestroyWindow(pWindow);
            SDL_EXITWITHERROR("image load");
        }

    // struct to hold the position and the size of the sprite 
    SDL_Rect rectangle;

    //get and scale the dimensions of texture
    //divide the scale by 4
    SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h);
    rectangle.w /=2; 
    rectangle.h /=2;

    //start sprite in center of screen
    float x_pos = (window_largeur - rectangle.w) / 2;
    float y_pos = (window_hauteur - rectangle.h) /2;
    float x_velocity = 0;
    float y_velocity =0;

    Uint8 volume = 0;
    Mix_VolumeMusic(50); // Mets le volume a 50

    SDL_bool up = SDL_FALSE;
    SDL_bool down = SDL_FALSE;
    SDL_bool left = SDL_FALSE;
    SDL_bool right = SDL_FALSE;

    SDL_Surface *onionSurface = IMG_Load("ressources/SDL/onion.png");
    if (!onionSurface)
        {
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(pRenderer);
            SDL_DestroyWindow(pWindow);
            SDL_EXITWITHERROR("image onion load");
        }

    SDL_Texture *onion = SDL_CreateTextureFromSurface(pRenderer, onionSurface);
        if (!onion)
        {
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(pRenderer);
            SDL_DestroyWindow(pWindow);
            SDL_EXITWITHERROR("onion texture load");
        }
    SDL_FreeSurface(onionSurface);
    SDL_Rect onionRect;
    SDL_QueryTexture(onion, NULL, NULL, &onionRect.w, &onionRect.h);
    float x_onion;
    float y_onion;
    onionRect.w /=50; 
    onionRect.h /=50;
        
        


    SDL_Color white = {255, 255, 255 , 0};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Shronkey  THE GAME", white );
    SDL_Texture *text = SDL_CreateTextureFromSurface(pRenderer, textSurface);
    SDL_FreeSurface(textSurface);
    textSurface = NULL;
    SDL_Rect textRect;
    SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);
    textRect.x = (window_largeur - textRect.w) / 2;
    textRect.y = 800;

    
    char score [20] = "";
    int conteur = 0;
    sprintf(score, "Score : %d", conteur);
    SDL_Surface *scoreActuelSurface = TTF_RenderText_Solid(gamefont, score, white );
    SDL_Texture *scoreActuel = SDL_CreateTextureFromSurface(pRenderer, scoreActuelSurface);
    
    SDL_Rect scoreRect;
    SDL_QueryTexture(scoreActuel, NULL, NULL, &scoreRect.w, &scoreRect.h);
    scoreRect.x = 0;
    scoreRect.y = 700;

    x_onion=100;
            y_onion=100;



    while (!close)
    {
        while (SDL_PollEvent(&events))
        {
            switch (events.type)
                {
                    case SDL_QUIT:
                    close = SDL_TRUE;
                    break;

                    case SDL_KEYDOWN:
                            switch(events.key.keysym.scancode)
                                {
                                    case SDL_SCANCODE_W:
                                        up = SDL_TRUE;
                                        break;
                                    case SDL_SCANCODE_S:
                                        down = SDL_TRUE;
                                        break;
                                    case SDL_SCANCODE_A:
                                        left = SDL_TRUE;
                                        break;
                                    case SDL_SCANCODE_D:
                                        right = SDL_TRUE;
                                        break;
                                }
                            break;

                        case SDL_KEYUP:
                            switch(events.key.keysym.scancode)
                                {
                                    case SDL_SCANCODE_W:
                                        up = SDL_FALSE;
                                        break;
                                    case SDL_SCANCODE_S:
                                        down = SDL_FALSE;
                                        break;
                                    case SDL_SCANCODE_A:
                                        left = SDL_FALSE;
                                        break;
                                    case SDL_SCANCODE_D:
                                        right = SDL_FALSE;
                                        break;
                                }
                            break;
                }
        }
        x_velocity = 0;
            y_velocity =0;
            
            if (up && !down)
                y_velocity = -PIXEL_SPEED;
            if (down && !up)
                y_velocity = PIXEL_SPEED;
            if (right && !left)
                x_velocity = PIXEL_SPEED;
            if (left && !right)
                x_velocity = -PIXEL_SPEED;



            //uptade position
            x_pos += x_velocity / 60;
            y_pos += y_velocity / 60;

            
            

            //collision detectin
            if (x_pos <= 0)
                x_pos = 0;
            if (y_pos <= 0)
                y_pos = 0;
            if (x_pos >= window_largeur - rectangle.w)
                x_pos = window_largeur - rectangle.w;
            if (y_pos >= window_hauteur - rectangle.h)
                y_pos = window_hauteur - rectangle.h;

            //set the position in the struct
            rectangle.y = (int) y_pos;
            rectangle.x = (int) x_pos;
            onionRect.x = (int) x_onion;
            onionRect.y = (int) y_onion;
            
            if (miam(onionRect.x, onionRect.y, onionRect.w, onionRect.h, rectangle.x, rectangle.y, rectangle.w, rectangle.h) == 1)
            {
                conteur += 1;
                sprintf(score, "Score : %d", conteur);
                scoreActuelSurface = TTF_RenderText_Solid(gamefont, score, white );
                scoreActuel = SDL_CreateTextureFromSurface(pRenderer, scoreActuelSurface);   
                x_onion = 500;
                y_onion = 780;
            }
            
            
            //SDL_FreeSurface()


            //clear the window
            SDL_RenderClear(pRenderer);

            //draw the image to the window
            SDL_RenderCopy(pRenderer, onion, NULL, &onionRect);
            SDL_RenderCopy(pRenderer, texture, NULL, &rectangle);
            SDL_RenderCopy(pRenderer, text, NULL, &textRect);
            SDL_RenderCopy(pRenderer, scoreActuel, NULL, &scoreRect);
            
            SDL_RenderPresent(pRenderer);

            SDL_Delay(100/6);

    }
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(text);
    SDL_DestroyTexture(scoreActuel);
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}




void SDL_EXITWITHERROR (const char *message)
{
    printf("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}


int miam (int foodx, int foody, int foodw, int foodh, int shrekx, int shreky, int shrekw, int shrekh)
    {
        if ((shrekx < foodx + foodw) && (shrekx + shrekw > foodx) && (shreky < foody + foodh) && (shreky + shrekh > foody))
            return 1;
        else
            return 0;
        
    }
