#include "headers/option.h"

int optionMenu (int *numTheme, int *red, int *green, int *blue, int *volume, Mix_Music *music, SDL_Color color1, SDL_Color color2,SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, SDL_Surface *optionButtonSurface, SDL_Texture *optionButton)
{
    //reset the actual window
    SDL_RenderClear(renderer);
    optionButtonSurface = NULL;
    optionButton = NULL;

    
    /***************change size+pos of "OPTION" font**************/
    int fontSize = 100;
    font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSize);
    optionButtonSurface = TTF_RenderText_Solid(font, "OPTIONS", color1);
    optionButton = SDL_CreateTextureFromSurface(renderer, optionButtonSurface);
    if (!optionButton)
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_EXITWITHERROR("creation optionButton");
        }
    
    SDL_Rect optionButtonRect;
    SDL_QueryTexture(optionButton, NULL, NULL, &optionButtonRect.w, &optionButtonRect.h);
    optionButtonRect.x = (WINDOW_LARGEUR - optionButtonRect.w) / 2;
    optionButtonRect.y = 50;

    /******************music volume sound******************/
    fontSize = 70;
    font = NULL;
    font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSize);
    char volumeTXT [110] = "";
    sprintf(volumeTXT, "%d", *volume);
    SDL_Surface *volumeSurface = TTF_RenderText_Solid(font, volumeTXT, color1);
    if (!volumeSurface)
        SDL_EXITWITHERROR("creation volume surface");
    SDL_Texture *volumeTexture = SDL_CreateTextureFromSurface(renderer, volumeSurface);
    if (!volumeTexture)
        SDL_EXITWITHERROR("creation volumeTexture");
    SDL_Rect volumeTextureRect;
    SDL_QueryTexture(volumeTexture, NULL, NULL, &volumeTextureRect.w, &volumeTextureRect.h);
    volumeTextureRect.x = (WINDOW_LARGEUR - volumeTextureRect.w) / 2;
    volumeTextureRect.y = 280;

    /****************music param +/- font******************/
    // +
    fontSize = 60;
    font = NULL;
    font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSize);
    SDL_Surface *plusButtonSurface = TTF_RenderText_Solid(font, "+", color1);
    if (!plusButtonSurface)
        SDL_EXITWITHERROR("creation plusButtonSurface");
    SDL_Texture *plusButton = SDL_CreateTextureFromSurface(renderer, plusButtonSurface);
    if (!plusButton)
        SDL_EXITWITHERROR("creation plusButton");
    SDL_Rect plusButtonRect;
    SDL_QueryTexture(plusButton, NULL, NULL, &plusButtonRect.w, &plusButtonRect.h );
    plusButtonRect.x = volumeTextureRect.x + volumeTextureRect.w +100;
    plusButtonRect.y = 280;

    //-
    SDL_Surface *minusButtonSurface = TTF_RenderText_Solid(font,"-", color1);
    if (!minusButtonSurface)
        SDL_EXITWITHERROR("creation minusButton");
    SDL_Texture *minusButton = SDL_CreateTextureFromSurface(renderer, minusButtonSurface);
    if (!minusButtonSurface)
        SDL_EXITWITHERROR("creation minusButton");
    SDL_Rect minusButtonRect;
    SDL_QueryTexture(minusButton, NULL, NULL, &minusButtonRect.w, &minusButtonRect.h);
    minusButtonRect.x = volumeTextureRect.x - 100;
    minusButtonRect.y = 280;

    /****************'volume'***************/
    fontSize = 50;
    font = NULL;
    font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSize);
    SDL_Surface *volWordSurface = TTF_RenderText_Solid(font, "Volume", color1);
    if (!volWordSurface)
        SDL_EXITWITHERROR("creation volWordSurface");
    SDL_Texture *volWord = SDL_CreateTextureFromSurface(renderer, volWordSurface);
    if (!volWord)
        SDL_EXITWITHERROR("creation plusButton");
    SDL_FreeSurface(volWordSurface);
    SDL_Rect volWordRect;
    SDL_QueryTexture(volWord, NULL, NULL, &volWordRect.w, &volWordRect.h );
    volWordRect.x = (WINDOW_LARGEUR - volWordRect.w) / 2;
    volWordRect.y = 220;    

    /***************theme indicator********/
    char themeTitle[50];
    //int numTheme = 1;
    sprintf(themeTitle, "Theme %d", *numTheme);
    fontSize = 50;
    font = NULL;
    font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSize);
    SDL_Surface *themeSurface = TTF_RenderText_Solid(font, themeTitle, color1);
    if (!themeSurface)
        SDL_EXITWITHERROR("creation themeSurface");
    SDL_Texture *theme = SDL_CreateTextureFromSurface(renderer, themeSurface);
    if (!theme)
        SDL_EXITWITHERROR("creation theme");
    SDL_Rect themeRect;
    SDL_QueryTexture(theme, NULL, NULL, &themeRect.w, &themeRect.h);
    themeRect.x = (WINDOW_LARGEUR - themeRect.w) / 2;
    themeRect.y = volumeTextureRect.y + volumeTextureRect.h + 40;

    /***************</>**************/
    fontSize = 50;
    
    TTF_Font *specialFont = TTF_OpenFont("ressources/SDL/font/04B_30__.TTF",fontSize);
    if (!specialFont)
        {
          printf("ERREUR: ouverture font %s\n", TTF_GetError());
          Mix_CloseAudio();
          SDL_Quit();
        }
    //"<"
    SDL_Surface *gBSurface = TTF_RenderText_Solid(specialFont, "<", color1);
    if (!gBSurface)
        SDL_EXITWITHERROR("creation gBSurface");
    SDL_Texture *gB = SDL_CreateTextureFromSurface(renderer, gBSurface);
    if (!gB)
        SDL_EXITWITHERROR("creation gB");
    SDL_Rect gBRect;
    SDL_QueryTexture(gB, NULL, NULL, &gBRect.w, &gBRect.h);
    gBRect.x = themeRect.x - 100;
    gBRect.y = themeRect.y + 5;
    //'>'
    SDL_Surface *dBSurface = TTF_RenderText_Solid(specialFont, ">", color1);
    if (!dBSurface)
        SDL_EXITWITHERROR("creation dBSurface");
    SDL_Texture *dB = SDL_CreateTextureFromSurface(renderer, dBSurface);
    if (!dB)
        SDL_EXITWITHERROR("creation dB");
    SDL_Rect dBRect;
    SDL_QueryTexture(dB, NULL, NULL, &dBRect.w, &dBRect.h);
    dBRect.x = themeRect.x + themeRect.w + 100;
    dBRect.y = themeRect.y + 5 ;

/****************'return'***************/
    fontSize = 50;
    font = NULL;
    font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSize);
    SDL_Surface *returnSurface = TTF_RenderText_Solid(font, "Return", color1);
    if (!returnSurface)
        SDL_EXITWITHERROR("creation returnSurface");
    SDL_Texture *returnButton = SDL_CreateTextureFromSurface(renderer, returnSurface);
    if (!returnButton)
        SDL_EXITWITHERROR("creation returnButton");
    
    SDL_Rect returnButtonRect;
    SDL_QueryTexture(returnButton, NULL, NULL, &returnButtonRect.w, &returnButtonRect.h );
    returnButtonRect.x = (WINDOW_LARGEUR - returnButtonRect.w) / 2;
    returnButtonRect.y = themeRect.y + themeRect.h + 40;

    /****************'or press esc'***************/
    fontSize = 20;
    font = NULL;
    font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSize);
    SDL_Surface *escSurface = TTF_RenderText_Solid(font, "or press esc", color1);
    if (!escSurface)
        SDL_EXITWITHERROR("creation escSurface");
    SDL_Texture *esc = SDL_CreateTextureFromSurface(renderer, escSurface);
    if (!esc)
        SDL_EXITWITHERROR("creation esc");
    
    SDL_Rect escRect;
    SDL_QueryTexture(esc, NULL, NULL, &escRect.w, &escRect.h );
    escRect.x = (WINDOW_LARGEUR - escRect.w) / 2;
    escRect.y = returnButtonRect.y + returnButtonRect.h + 10; 







    
    SDL_bool optionRUNNING = SDL_TRUE;
    SDL_Event optionEvent;

    int mouse_x;
    int mouse_y;
    int mouseBx;
    int mouseBy;
    //variables for the color of the theme
    Uint8 a;

    // reset the font for the color changes
    fontSize = 60;
    font = NULL;
    font = TTF_OpenFont("ressources/SDL/font/Gameplay.ttf",fontSize);

    while (optionRUNNING)
        {
            while(SDL_PollEvent(&optionEvent))
                {
                    switch(optionEvent.type)
                        {
                            case SDL_QUIT:
                                optionRUNNING = SDL_FALSE;
                                return 0;
                            break;

                            case SDL_KEYDOWN:
                                switch (optionEvent.key.keysym.sym)
                                    {
                                        case SDLK_ESCAPE:
                                            optionRUNNING = SDL_FALSE;
                                            return 1;
                                        break;
                                    }
                            break;

                            case SDL_MOUSEMOTION:
                                mouse_x = optionEvent.motion.x;
                                mouse_y = optionEvent.motion.y;
                                //switch button to red color when cursor is on it
                                //case '-'
                                 if ((mouse_x < minusButtonRect.x + minusButtonRect.w)&&
                                    (mouse_x > minusButtonRect.x) &&
                                    (mouse_y < minusButtonRect.y + minusButtonRect.h)&&
                                    (mouse_y > minusButtonRect.y))
                                    {
                                        minusButtonSurface = TTF_RenderText_Solid(font, "-", color2);
                                        minusButton = SDL_CreateTextureFromSurface(renderer, minusButtonSurface);
                                    }
                                    else
                                    {
                                        minusButtonSurface = TTF_RenderText_Solid(font, "-", color1);
                                        minusButton = SDL_CreateTextureFromSurface(renderer, minusButtonSurface);
                                    }
                                //case '+'
                                if ((mouse_x < plusButtonRect.x + plusButtonRect.w)&&
                                    (mouse_x > plusButtonRect.x) &&
                                    (mouse_y < plusButtonRect.y + plusButtonRect.h)&&
                                    (mouse_y > plusButtonRect.y))
                                    {
                                        plusButtonSurface = TTF_RenderText_Solid(font, "+", color2);
                                        plusButton = SDL_CreateTextureFromSurface(renderer, plusButtonSurface);
                                    }
                                    else
                                    {
                                        plusButtonSurface = TTF_RenderText_Solid(font, "+", color1);
                                        plusButton = SDL_CreateTextureFromSurface(renderer, plusButtonSurface);
                                    }
                                //case '>'
                                if ((mouse_x < dBRect.x + dBRect.w)&&
                                    (mouse_x > dBRect.x) &&
                                    (mouse_y < dBRect.y + dBRect.h)&&
                                    (mouse_y > dBRect.y))
                                    {
                                        dBSurface = TTF_RenderText_Solid(specialFont, ">", color2);
                                        dB = SDL_CreateTextureFromSurface(renderer, dBSurface);
                                    }
                                    else
                                    {
                                        dBSurface = TTF_RenderText_Solid(specialFont, ">", color1);
                                        dB = SDL_CreateTextureFromSurface(renderer, dBSurface);
                                    }
                                //case '<'
                                if ((mouse_x < gBRect.x + gBRect.w)&&
                                    (mouse_x > gBRect.x) &&
                                    (mouse_y < gBRect.y + gBRect.h)&&
                                    (mouse_y > gBRect.y))
                                    {
                                        gBSurface = TTF_RenderText_Solid(specialFont, "<", color2);
                                        gB = SDL_CreateTextureFromSurface(renderer, gBSurface);
                                    }
                                    else
                                    {
                                        gBSurface = TTF_RenderText_Solid(specialFont, "<", color1);
                                        gB = SDL_CreateTextureFromSurface(renderer, gBSurface);
                                    }
                                //case 'return'
                                if ((mouse_x < returnButtonRect.x + returnButtonRect.w)&&
                                    (mouse_x > returnButtonRect.x) &&
                                    (mouse_y < returnButtonRect.y + returnButtonRect.h)&&
                                    (mouse_y > returnButtonRect.y))
                                    {
                                        returnSurface = TTF_RenderText_Solid(font, "return", color2);
                                        returnButton = SDL_CreateTextureFromSurface(renderer, returnSurface);
                                    }
                                    else
                                    {
                                        returnSurface = TTF_RenderText_Solid(font, "return", color1);
                                        returnButton = SDL_CreateTextureFromSurface(renderer, returnSurface);
                                    }
                            break;

                            case SDL_MOUSEBUTTONDOWN:
                                mouseBx = optionEvent.button.x;
                                mouseBy = optionEvent.button.y;
                                //decrease the volume
                                if ((mouseBx < minusButtonRect.x + minusButtonRect.w)&&
                                    (mouseBx > minusButtonRect.x) &&
                                    (mouseBy < minusButtonRect.y + minusButtonRect.h)&&
                                    (mouseBy > minusButtonRect.y))
                                        {
                                            *volume -= 10;
                                            if (*volume <0)
                                                *volume =0;
                                            sprintf(volumeTXT, "%d", *volume);
                                            volumeSurface = TTF_RenderText_Solid(font, volumeTXT, color1);
                                            volumeTexture = SDL_CreateTextureFromSurface(renderer, volumeSurface);
                                            Mix_VolumeMusic(*volume);
                                            
                                        }
                                //increase the volume
                                 if ((mouseBx < plusButtonRect.x + plusButtonRect.w)&&
                                    (mouseBx > plusButtonRect.x) &&
                                    (mouseBy < plusButtonRect.y + plusButtonRect.h)&&
                                    (mouseBy > plusButtonRect.y))
                                    {
                                        *volume += 10 ;
                                        if (*volume >100)
                                            *volume = 100;
                                        sprintf(volumeTXT, "%d", *volume);
                                        volumeSurface = TTF_RenderText_Solid(font, volumeTXT, color1);
                                        volumeTexture = SDL_CreateTextureFromSurface(renderer, volumeSurface);
                                        Mix_VolumeMusic(*volume);
                                    }
                                //"increase" the theme
                                if ((mouseBx < dBRect.x + dBRect.w)&&
                                    (mouseBx > dBRect.x) &&
                                    (mouseBy < dBRect.y + dBRect.h)&&
                                    (mouseBy > dBRect.y))
                                    {
                                        *numTheme += 1;
                                        //printf("%d",numTheme);
                                        if (*numTheme > NUMBER_OF_THEME)
                                            *numTheme = 1;
                                        sprintf(themeTitle, "Theme %d", *numTheme);
                                        themeSurface = TTF_RenderText_Solid(font, themeTitle, color1);
                                        theme = SDL_CreateTextureFromSurface(renderer, themeSurface);
                                        
                                    }
                                //"decrease the theme"
                                if ((mouseBx < gBRect.x + gBRect.w)&&
                                    (mouseBx > gBRect.x) &&
                                    (mouseBy < gBRect.y + gBRect.h)&&
                                    (mouseBy > gBRect.y))
                                    {
                                        *numTheme -= 1;
                                        //printf("%d",numTheme);
                                        if (*numTheme < 1)
                                            *numTheme = NUMBER_OF_THEME;
                                        sprintf(themeTitle, "Theme %d", *numTheme);
                                        themeSurface = TTF_RenderText_Solid(font, themeTitle, color1);
                                        theme = SDL_CreateTextureFromSurface(renderer, themeSurface);
                                        
                                    }
                                if (*numTheme == 1)
                                    {
                                        *red = 113;
                                        *blue = 0;
                                        *green = 0;
                                        a = 0;
                                    }
                                if (*numTheme == 2)
                                    {
                                        *red = 0;
                                        *blue = 113;
                                        *green = 0;
                                        a = 0;
                                    }
                                if (*numTheme == 3)
                                    {
                                        *red = 0;
                                        *blue = 0;
                                        *green = 113;
                                        a = 0;
                                    }
                                //leave by click on 'return'
                                if ((mouse_x < returnButtonRect.x + returnButtonRect.w)&&
                                    (mouse_x > returnButtonRect.x) &&
                                    (mouse_y < returnButtonRect.y + returnButtonRect.h)&&
                                    (mouse_y > returnButtonRect.y))
                                        {
                                        optionRUNNING = SDL_FALSE;
                                        return 1;
                                        }
                            break;

                        }

                }

                //clear the window
                SDL_RenderClear(renderer);

                //draw the image to the window
                SDL_SetRenderDrawColor(renderer, *red, *green, *blue, a);
                SDL_RenderCopy(renderer, esc, NULL, &escRect);
                SDL_RenderCopy(renderer, dB, NULL, &dBRect);
                SDL_RenderCopy(renderer, returnButton, NULL, &returnButtonRect);
                SDL_RenderCopy(renderer, gB, NULL, &gBRect);
                SDL_RenderCopy(renderer, theme, NULL, &themeRect);
                SDL_RenderCopy(renderer, volWord, NULL, &volWordRect);
                SDL_RenderCopy(renderer, volumeTexture, NULL, &volumeTextureRect);
                SDL_RenderCopy(renderer, optionButton, NULL, &optionButtonRect);
                SDL_RenderCopy(renderer, plusButton, NULL, &plusButtonRect);
                SDL_RenderCopy(renderer, minusButton, NULL, &minusButtonRect);

                SDL_RenderPresent(renderer);
        }


    SDL_DestroyTexture(optionButton);
    SDL_DestroyTexture(esc);
    SDL_DestroyTexture(theme);
    SDL_DestroyTexture(volWord);
    SDL_DestroyTexture(plusButton);
    SDL_DestroyTexture(gB);
    SDL_DestroyTexture(dB);
    SDL_DestroyTexture(returnButton);
    SDL_DestroyTexture(minusButton);
    SDL_DestroyTexture(volumeTexture);
    SDL_FreeSurface(optionButtonSurface);

}

