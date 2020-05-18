#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>



void SDL_EXITWITHERROR (const char *message);

#define window_largeur 640*1.5
#define window_hauteur 480*1.5
#define PIXEL_SPEED 500 

int main ()
{
    //attempt to initialize graphics
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_EXITWITHERROR("initialisation SDL");
 
    SDL_Window *window = SDL_CreateWindow("2048 LE JEU", 
                                            SDL_WINDOWPOS_CENTERED ,SDL_WINDOWPOS_CENTERED,
                                            window_largeur, window_hauteur, 0);

    if (window == NULL)
        SDL_EXITWITHERROR("creation fenetre");

    //create a renderer , which sets up the graphics hardware
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
     if (!renderer)
        SDL_EXITWITHERROR("creation rendu");


    //load the image into memory using SDL_image library function 
    SDL_Surface* surface = IMG_Load("ressources/SDL/hello.png");
    if (!surface)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_EXITWITHERROR("image load");

        }

    //load the image data into the graphics hardware's memory 
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture)
        {
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
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

    

    SDL_bool program_launched = SDL_TRUE;

    //suivi du mouvement 
    SDL_bool up = SDL_FALSE;
    SDL_bool down = SDL_FALSE;
    SDL_bool left = SDL_FALSE;
    SDL_bool right = SDL_FALSE;

    //programme lance
    while (program_launched)
        {
            SDL_Event event;

            // lis tout les evenements
            while(SDL_PollEvent(&event))
                {
                   switch (event.type)
                    {
                        case SDL_QUIT:
                            program_launched = SDL_FALSE;
                            break;
                        
                        case SDL_KEYDOWN:
                            switch(event.key.keysym.scancode)
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
                            switch(event.key.keysym.scancode)
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

                        //default:
                           // break;
                    }
                }

            
            //initiate velocity
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

            //clear the window
            SDL_RenderClear(renderer);

            //draw the image to the window
            SDL_RenderCopy(renderer, texture, NULL, &rectangle);
            SDL_RenderPresent(renderer);

            SDL_Delay(100/6);
        }
    

    
    

    SDL_DestroyTexture(texture);
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
