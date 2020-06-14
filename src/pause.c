#include "headers/pause.h"

int pauseMenu (int *red, int *green, int *blue, TTF_Font *font, SDL_Renderer *renderer, SDL_Window *window)
    {
        //clear the renderer memory
        SDL_RenderClear(renderer);


        SDL_Color white = {255, 255, 255, 0};
        SDL_Color rouge = {255, 0, 0, 0};

        /***********PAUSE**************/
        int fontSize = 100;
        font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSize);
        SDL_Surface *pauseSurface = TTF_RenderText_Solid(font, getTranslatedText("paMenu.pa"), white);
        if (!pauseSurface)
            SDL_EXITWITHERROR("creation pause surface");
        SDL_Texture *pauseTexture = SDL_CreateTextureFromSurface(renderer, pauseSurface);
        if (!pauseTexture)
            SDL_EXITWITHERROR("creation pause Texture"); 
        SDL_FreeSurface(pauseSurface);
        SDL_Rect pauseRect;
        SDL_QueryTexture(pauseTexture, NULL, NULL, &pauseRect.w, &pauseRect.h);
        pauseRect.x = (WINDOW_LARGEUR - pauseRect.w) / 2;
        pauseRect.y = 50;

        /**************RESUME***********/
        fontSize = 60;
        font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSize);
        SDL_Surface *resume = TTF_RenderText_Solid(font, getTranslatedText("paMenu.re"), white);
        if (!resume)
            SDL_EXITWITHERROR("creation resume surface");
        SDL_Texture *resumeTexture = SDL_CreateTextureFromSurface(renderer, resume);
        if (!resumeTexture)
            SDL_EXITWITHERROR("creation resume texture");
        SDL_Rect resumeRect;
        SDL_QueryTexture(resumeTexture, NULL, NULL, &resumeRect.w, &resumeRect.h);
        resumeRect.x = (WINDOW_LARGEUR - resumeRect.w) / 2;
        resumeRect.y = pauseRect.y + pauseRect.h + 100;

        /*************HOME***************/
        SDL_Surface *homeSurface = TTF_RenderText_Solid(font, getTranslatedText("paMenu.ho"), white);
        if (!homeSurface)
            SDL_EXITWITHERROR("creation home surface");
        SDL_Texture *homeTexture = SDL_CreateTextureFromSurface(renderer, homeSurface);
        if (!homeTexture)
            SDL_EXITWITHERROR("creation home texture");
        SDL_Rect homeRect;
        SDL_QueryTexture(homeTexture, NULL, NULL, &homeRect.w, &homeRect.h);
        homeRect.x = (WINDOW_LARGEUR - homeRect.w) / 2;
        homeRect.y = resumeRect.y + resumeRect.h + 50;

    

    SDL_Event pauseEvent;
    SDL_bool pauseRunning = SDL_TRUE;
    int mouse_x, mouse_y = 0;

    while(pauseRunning)  {
        while(SDL_PollEvent(&pauseEvent)) {
            switch(pauseEvent.type) {
                case SDL_QUIT:
                    pauseRunning = SDL_FALSE;
                    return 0;
                break;

                case SDL_KEYDOWN:
                     switch(pauseEvent.key.keysym.sym) {
                        case SDLK_ESCAPE:
                             pauseRunning = SDL_FALSE;
                              return 1;
                        break;
                     }
                break;


                case SDL_MOUSEMOTION:
                     mouse_x = pauseEvent.motion.x;
                     mouse_y = pauseEvent.motion.y;
                     //switch button color depending of the cursor location
                     //case resume
                     if ((mouse_x < resumeRect.x + resumeRect.w) && (mouse_x > resumeRect.x) &&
                         (mouse_y < resumeRect.y + resumeRect.h) && (mouse_y > resumeRect.y)) {
                         
                         resume = TTF_RenderText_Solid(font, getTranslatedText("paMenu.re"), rouge);
                         resumeTexture = SDL_CreateTextureFromSurface(renderer, resume);
                     } else {
                         resume = TTF_RenderText_Solid(font, getTranslatedText("paMenu.re"), white);
                         resumeTexture = SDL_CreateTextureFromSurface(renderer, resume);
                     }

                     //case home
                     if ((mouse_x < homeRect.x + homeRect.w) && (mouse_x > homeRect.x) &&
                         (mouse_y < homeRect.y + homeRect.h) && (mouse_y > homeRect.y)) {
                         
                         homeSurface = TTF_RenderText_Solid(font, getTranslatedText("paMenu.ho"), rouge);
                         homeTexture = SDL_CreateTextureFromSurface(renderer, homeSurface);
                     } else {
                         homeSurface = TTF_RenderText_Solid(font, getTranslatedText("paMenu.ho"), white);
                          homeTexture = SDL_CreateTextureFromSurface(renderer, homeSurface);
                     }
                break;


                case SDL_MOUSEBUTTONDOWN:
                     //resume the game if click on resume
                     if ((pauseEvent.button.x < resumeRect.x + resumeRect.w) && (pauseEvent.button.x > resumeRect.x) &&
                         (pauseEvent.button.y < resumeRect.y + resumeRect.h) && (pauseEvent.button.y > resumeRect.y))

                         pauseRunning = SDL_FALSE;

                     //go to home menu if click on home
                     if ((pauseEvent.button.x < homeRect.x + homeRect.w) && (pauseEvent.button.x > homeRect.x) &&
                         (pauseEvent.button.y < homeRect.y + homeRect.h) && (pauseEvent.button.y > homeRect.y)) {
                         
                         pauseRunning = SDL_FALSE;
                         return 2;
                     }
                break;
            }
                    
        }
        //clear the renderer memory
        SDL_SetRenderDrawColor(renderer, *red, *green, *blue, 0);
        SDL_RenderClear(renderer);

        //charge the textures into the renderer memory
                
        SDL_RenderCopy(renderer, pauseTexture, NULL, &pauseRect);
        SDL_RenderCopy(renderer, resumeTexture, NULL, &resumeRect);
        SDL_RenderCopy(renderer, homeTexture, NULL, &homeRect);

        //display the loaded renderer
         SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(pauseTexture);
    SDL_DestroyTexture(resumeTexture);
    SDL_DestroyTexture(homeTexture);
}


int gameOver (int *red, int *green, int *blue, TTF_Font *font, SDL_Renderer *renderer, SDL_Window *window, GameState * state)
    {
        //clear the renderer memory
        SDL_RenderClear(renderer);


        SDL_Color white = {255, 255, 255, 0};
        SDL_Color rouge = {255, 0, 0, 0};

        /***********GameOver**************/
        int fontSize = 100;
        font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSize);
        SDL_Surface *gameoverSurface = TTF_RenderText_Solid(font, getTranslatedText("goMenu.go"), white);
        if (!gameoverSurface)
            SDL_EXITWITHERROR("creation gameover surface");
        SDL_Texture *gameoverTexture = SDL_CreateTextureFromSurface(renderer, gameoverSurface);
        if (!gameoverTexture)
            SDL_EXITWITHERROR("creation gameover Texture"); 
        SDL_FreeSurface(gameoverSurface);
        SDL_Rect gameoverRect;
        SDL_QueryTexture(gameoverTexture, NULL, NULL, &gameoverRect.w, &gameoverRect.h);
        gameoverRect.x = (WINDOW_LARGEUR - gameoverRect.w) / 2;
        gameoverRect.y = 50;

        /************multiplayer***********/
        char playerText[32] = "You lose";
        font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf", 40);
        if (state->playerNumber > 1) sprintf(playerText, "Player %d has lost", state->currentPlayer);

        SDL_Surface* pTextSurface = TTF_RenderText_Solid(font, playerText, white);
        SDL_Texture* pTextTexture = SDL_CreateTextureFromSurface(renderer, pTextSurface);

        SDL_Rect pTextRect;
        SDL_QueryTexture(pTextTexture, NULL, NULL, &pTextRect.w, &pTextRect.h);
        pTextRect.x = (WINDOW_LARGEUR - pTextRect.w) / 2;
        pTextRect.y = gameoverRect.y + gameoverRect.h + 25;;   

        /**************RESTART***********/
        fontSize = 60;
        font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSize);
        SDL_Surface *restart = TTF_RenderText_Solid(font, getTranslatedText("goMenu.re"), white);
        if (!restart)
            SDL_EXITWITHERROR("creation restart surface");
        SDL_Texture *restartTexture = SDL_CreateTextureFromSurface(renderer, restart);
        if (!restartTexture)
            SDL_EXITWITHERROR("creation restart texture");
        SDL_Rect restartRect;
        SDL_QueryTexture(restartTexture, NULL, NULL, &restartRect.w, &restartRect.h);
        restartRect.x = (WINDOW_LARGEUR - restartRect.w) / 2;
        restartRect.y = gameoverRect.y + gameoverRect.h + 150;

        /*************HOME***************/
        SDL_Surface *homeSurface = TTF_RenderText_Solid(font, getTranslatedText("goMenu.ho"), white);
        if (!homeSurface)
            SDL_EXITWITHERROR("creation home surface");
        SDL_Texture *homeTexture = SDL_CreateTextureFromSurface(renderer, homeSurface);
        if (!homeTexture)
            SDL_EXITWITHERROR("creation home texture");
        SDL_Rect homeRect;
        SDL_QueryTexture(homeTexture, NULL, NULL, &homeRect.w, &homeRect.h);
        homeRect.x = (WINDOW_LARGEUR - homeRect.w) / 2;
        homeRect.y = restartRect.y + restartRect.h + 50;



    SDL_Event gameoverEvent;
    SDL_bool gameoverRunning = SDL_TRUE;
    int mouse_x, mouse_y = 0;
    

    while(gameoverRunning)  {
        
        while(SDL_PollEvent(&gameoverEvent)) {
            switch(gameoverEvent.type) {
                case SDL_QUIT:
                    gameoverRunning = SDL_FALSE;
                    return 0;
                break;

                case SDL_KEYDOWN:
                     switch(gameoverEvent.key.keysym.sym) {
                        case SDLK_ESCAPE:
                             gameoverRunning = SDL_FALSE;
                              return 1;
                        break;
                     }
                break;


                case SDL_MOUSEMOTION:
                     mouse_x = gameoverEvent.motion.x;
                     mouse_y = gameoverEvent.motion.y;
                     //switch button color depending of the cursor location
                     //case restart
                     if ((mouse_x < restartRect.x + restartRect.w) && (mouse_x > restartRect.x) &&
                         (mouse_y < restartRect.y + restartRect.h) && (mouse_y > restartRect.y)) {
                         
                         restart = TTF_RenderText_Solid(font, getTranslatedText("goMenu.re"), rouge);
                         restartTexture = SDL_CreateTextureFromSurface(renderer, restart);
                     } else {
                         restart = TTF_RenderText_Solid(font, getTranslatedText("goMenu.re"), white);
                         restartTexture = SDL_CreateTextureFromSurface(renderer, restart);
                     }

                     //case home
                     if ((mouse_x < homeRect.x + homeRect.w) && (mouse_x > homeRect.x) &&
                         (mouse_y < homeRect.y + homeRect.h) && (mouse_y > homeRect.y)) {
                         
                         homeSurface = TTF_RenderText_Solid(font, getTranslatedText("goMenu.ho"), rouge);
                         homeTexture = SDL_CreateTextureFromSurface(renderer, homeSurface);
                     } else {
                         homeSurface = TTF_RenderText_Solid(font, getTranslatedText("goMenu.ho"), white);
                          homeTexture = SDL_CreateTextureFromSurface(renderer, homeSurface);
                     }
                break;


                case SDL_MOUSEBUTTONDOWN:
                     //restart the game if click on restart
                     if ((gameoverEvent.button.x < restartRect.x + restartRect.w) && (gameoverEvent.button.x > restartRect.x) &&
                         (gameoverEvent.button.y < restartRect.y + restartRect.h) && (gameoverEvent.button.y > restartRect.y))
                        {
                            int sc = setScore();
                            gameoverRunning = SDL_FALSE;
                            return 1;
                        }
                         

                     //go to home menu if click on home
                     if ((gameoverEvent.button.x < homeRect.x + homeRect.w) && (gameoverEvent.button.x > homeRect.x) &&
                         (gameoverEvent.button.y < homeRect.y + homeRect.h) && (gameoverEvent.button.y > homeRect.y)) {
                         
                         int sc = setScore();
                         gameoverRunning = SDL_FALSE;
                         return 2;
                     }
                break;
            }
                    
        }
        //clear the renderer memory
        SDL_SetRenderDrawColor(renderer, *red, *green, *blue, 0);
        SDL_RenderClear(renderer);

        //charge the textures into the renderer memory
                
        SDL_RenderCopy(renderer, gameoverTexture, NULL, &gameoverRect);
        SDL_RenderCopy(renderer, restartTexture, NULL, &restartRect);
        SDL_RenderCopy(renderer, homeTexture, NULL, &homeRect);
        SDL_RenderCopy(renderer, pTextTexture, NULL, &pTextRect);
        

        //display the loaded renderer
         SDL_RenderPresent(renderer);
    }
    

    SDL_DestroyTexture(gameoverTexture);
    SDL_DestroyTexture(restartTexture);
    SDL_DestroyTexture(homeTexture);
    SDL_DestroyTexture(pTextTexture);
}



