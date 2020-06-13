#include "headers/selectionTitle.h"

int selectGame(int *red, int *green, int *blue, TTF_Font *font, SDL_Renderer *renderer, SDL_Window *window)
    {
        //reset the renderer memory
        SDL_RenderClear(renderer);
        SDL_Color white = {255, 255, 255, 0};
        SDL_Color rouge = {255, 0, 0, 0};

        /*************choose game mode**************/
        int fontSize = 50;
        font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSize);
        SDL_Surface *gmSurface = TTF_RenderText_Solid(font, getTranslatedText("chMenu.ch"), white);
        if (!gmSurface)
            SDL_EXITWITHERROR("creation gm surface");
         SDL_Texture *gmTexture = SDL_CreateTextureFromSurface(renderer, gmSurface);
        if (!gmTexture)
            SDL_EXITWITHERROR("creation gmTexture");
        SDL_FreeSurface(gmSurface);
        SDL_Rect gmTextureRect;
        SDL_QueryTexture(gmTexture, NULL, NULL, &gmTextureRect.w, &gmTextureRect.h);
        gmTextureRect.x = (WINDOW_LARGEUR - gmTextureRect.w) / 2;
        gmTextureRect.y = 50;


        /**************4x4**********************/
        fontSize = 40;
        font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSize);
        SDL_Surface *fourSurface = TTF_RenderText_Solid(font, getTranslatedText("chMenu.fo"), white);
        if (!fourSurface)
            SDL_EXITWITHERROR("creation four surface");
         SDL_Texture *fourTexture = SDL_CreateTextureFromSurface(renderer, fourSurface);
        if (!fourTexture)
            SDL_EXITWITHERROR("creation fourTexture");
        SDL_Rect fourTextureRect;
        SDL_QueryTexture(fourTexture, NULL, NULL, &fourTextureRect.w, &fourTextureRect.h);
        fourTextureRect.x = (WINDOW_LARGEUR - fourTextureRect.w) / 2;
        fourTextureRect.y = gmTextureRect.y + gmTextureRect.h + 100;


        /***********8x8*******************/
        SDL_Surface *eightSurface = TTF_RenderText_Solid(font, getTranslatedText("chMenu.ei"), white);
        if (!eightSurface)
            SDL_EXITWITHERROR("creation eight surface");
         SDL_Texture *eightTexture = SDL_CreateTextureFromSurface(renderer, eightSurface);
        if (!eightTexture)
            SDL_EXITWITHERROR("creation eightTexture");
        SDL_Rect eightTextureRect;
        SDL_QueryTexture(eightTexture, NULL, NULL, &eightTextureRect.w, &eightTextureRect.h);
        eightTextureRect.x = (WINDOW_LARGEUR - eightTextureRect.w) / 2;
        eightTextureRect.y = fourTextureRect.y + fourTextureRect.h + 40;


        /****************J vs J***************/
        SDL_Surface *JvJSurface = TTF_RenderText_Solid(font, getTranslatedText("chMenu.jj"), white);
        if (!JvJSurface)
            SDL_EXITWITHERROR("creation JvJ surface");
         SDL_Texture *JvJTexture = SDL_CreateTextureFromSurface(renderer, JvJSurface);
        if (!JvJTexture)
            SDL_EXITWITHERROR("creation JvJTexture");
        SDL_Rect JvJTextureRect;
        SDL_QueryTexture(JvJTexture, NULL, NULL, &JvJTextureRect.w, &JvJTextureRect.h);
        JvJTextureRect.x = (WINDOW_LARGEUR - JvJTextureRect.w) / 2;
        JvJTextureRect.y = eightTextureRect.y + eightTextureRect.h + 40;


        /**********J vs IA*******************/
        SDL_Surface *JvIASurface = TTF_RenderText_Solid(font, getTranslatedText("chMenu.ji"), white);
        if (!JvIASurface)
            SDL_EXITWITHERROR("creation JvIA surface");
         SDL_Texture *JvIATexture = SDL_CreateTextureFromSurface(renderer, JvIASurface);
        if (!JvIATexture)
            SDL_EXITWITHERROR("creation JvIATexture");
        SDL_Rect JvIATextureRect;
        SDL_QueryTexture(JvIATexture, NULL, NULL, &JvIATextureRect.w, &JvIATextureRect.h);
        JvIATextureRect.x = (WINDOW_LARGEUR - JvIATextureRect.w) / 2;
        JvIATextureRect.y = JvJTextureRect.y + JvJTextureRect.h + 40;




        SDL_bool selectionRunning = SDL_TRUE;
        SDL_Event selectionEvent;
        int mouse_x, mouse_y;
        int truefalse;

        while(selectionRunning)
            {
                while(SDL_PollEvent(&selectionEvent))
                    {
                        switch(selectionEvent.type)
                            {
                                case SDL_QUIT:
                                    selectionRunning = SDL_FALSE;
                                    return 0;
                                break;

                                case SDL_KEYDOWN:
                                switch (selectionEvent.key.keysym.sym)
                                    {
                                        case SDLK_ESCAPE:
                                            selectionRunning = SDL_FALSE;
                                            return 1;
                                        break;
                                    }
                                break;

                                case SDL_MOUSEMOTION:
                                mouse_x = selectionEvent.motion.x;
                                mouse_y = selectionEvent.motion.y;
                                //switch button to red color when cursor is on it
                                //case '4x4'
                                if ((mouse_x < fourTextureRect.x + fourTextureRect.w)&&
                                    (mouse_x > fourTextureRect.x) &&
                                    (mouse_y < fourTextureRect.y + fourTextureRect.h)&&
                                    (mouse_y > fourTextureRect.y))
                                    {
                                        fourSurface = TTF_RenderText_Solid(font, getTranslatedText("chMenu.fo"), rouge);
                                        fourTexture = SDL_CreateTextureFromSurface(renderer, fourSurface);
                                    }
                                else
                                    {
                                        fourSurface = TTF_RenderText_Solid(font, getTranslatedText("chMenu.fo"), white);
                                        fourTexture = SDL_CreateTextureFromSurface(renderer, fourSurface);
                                    }
                                
                                //case '8x8'
                                if ((mouse_x < eightTextureRect.x + eightTextureRect.w)&&
                                    (mouse_x > eightTextureRect.x) &&
                                    (mouse_y < eightTextureRect.y + eightTextureRect.h)&&
                                    (mouse_y > eightTextureRect.y))
                                    {
                                        eightSurface = TTF_RenderText_Solid(font, getTranslatedText("chMenu.ei"), rouge);
                                        eightTexture = SDL_CreateTextureFromSurface(renderer, eightSurface);
                                    }
                                else
                                    {
                                        eightSurface = TTF_RenderText_Solid(font, getTranslatedText("chMenu.ei"), white);
                                        eightTexture = SDL_CreateTextureFromSurface(renderer, eightSurface);
                                    }

                                //case 'J vs J'
                                if ((mouse_x < JvJTextureRect.x + JvJTextureRect.w)&&
                                    (mouse_x > JvJTextureRect.x) &&
                                    (mouse_y < JvJTextureRect.y + JvJTextureRect.h)&&
                                    (mouse_y > JvJTextureRect.y))
                                    {
                                        JvJSurface = TTF_RenderText_Solid(font, getTranslatedText("chMenu.jj"), rouge);
                                        JvJTexture = SDL_CreateTextureFromSurface(renderer, JvJSurface);
                                    }
                                else
                                    {
                                        JvJSurface = TTF_RenderText_Solid(font, getTranslatedText("chMenu.jj"), white);
                                        JvJTexture = SDL_CreateTextureFromSurface(renderer, JvJSurface);
                                    }

                                //case 'J vs IA'
                                if ((mouse_x < JvIATextureRect.x + JvIATextureRect.w)&&
                                    (mouse_x > JvIATextureRect.x) &&
                                    (mouse_y < JvIATextureRect.y + JvIATextureRect.h)&&
                                    (mouse_y > JvIATextureRect.y))
                                    {
                                        JvIASurface = TTF_RenderText_Solid(font, getTranslatedText("chMenu.ji"), rouge);
                                        JvIATexture = SDL_CreateTextureFromSurface(renderer, JvIASurface);
                                    }
                                    else
                                    {
                                        JvIASurface = TTF_RenderText_Solid(font, getTranslatedText("chMenu.ji"), white);
                                        JvIATexture = SDL_CreateTextureFromSurface(renderer, JvIASurface);
                                    }
                                break;


                                case SDL_MOUSEBUTTONDOWN:
                                //case '4x4' l
                                if ((selectionEvent.button.x < fourTextureRect.x + fourTextureRect.w)&&
                                    (selectionEvent.button.x > fourTextureRect.x) &&
                                    (selectionEvent.button.y < fourTextureRect.y + fourTextureRect.h)&&
                                    (selectionEvent.button.y > fourTextureRect.y))
                                        {
                                            truefalse = game(red, green, blue, font, renderer, window, 4);
                                            if (truefalse == 0)
													{
														selectionRunning = SDL_FALSE;
														return 0;
													}
												else if (truefalse == 1)
													{
														selectionRunning = SDL_FALSE;
														return 1;
													}
                                        }

                                if ((selectionEvent.button.x < eightTextureRect.x + eightTextureRect.w) && (selectionEvent.button.x > eightTextureRect.x) &&
                                    (selectionEvent.button.y < eightTextureRect.y + eightTextureRect.h) && (selectionEvent.button.y > eightTextureRect.y)) {
                                    printf("loadding 4x4 board\n");
                                    truefalse = game(red, green, blue, font, renderer, window, 8);
                                    if (truefalse == 0) {
                                        selectionRunning = SDL_FALSE;
                                        return 0;
                                    } else if (truefalse == 1) {
                                        selectionRunning = SDL_FALSE;
                                        return 1;
                                    }
                                }
                            }
                    }

                //clear the renderer memory
                SDL_RenderClear(renderer);

                //charge textures in renderer
                SDL_SetRenderDrawColor(renderer, *red, *green, *blue, 0);
                SDL_RenderCopy(renderer, gmTexture, NULL, &gmTextureRect);
                SDL_RenderCopy(renderer, fourTexture, NULL, &fourTextureRect);
                SDL_RenderCopy(renderer, eightTexture, NULL, &eightTextureRect);
                SDL_RenderCopy(renderer, JvJTexture, NULL, &JvJTextureRect);
                SDL_RenderCopy(renderer, JvIATexture, NULL, &JvIATextureRect);

                SDL_RenderPresent(renderer);
            }
    SDL_DestroyTexture(gmTexture);
    SDL_DestroyTexture(fourTexture);
    SDL_DestroyTexture(eightTexture);
    SDL_DestroyTexture(JvJTexture);
    SDL_DestroyTexture(JvIATexture);


    }