#include "headers/highscore.h"

//INTERN STRUCT


/**
 * @fn int searchiInStringArray(char * str, PlayerScore * array, int lenght)
 * @brief search in PlayerScore array the index of 'str' and return the index
 *
 * @return the index of str in PlayerScore array or -1 if not found
 */
int searchiInStringArray(char * str, PlayerScore * array, int lenght) {
  for(int i = 0; i < lenght; i++) {
    if (!strcmp(array[i].player, str) ){ return i; }
  }
  return -1;
}


void tri (int lenght, PlayerScore * ScoreBoard){
  int j,c;
  char temp[MAX_LENGHT_PLAYER_NAME];
  for (int a=0;a<lenght-1;a++)
    {
      for (j=a+1;j<lenght;j++)
        {
          if (ScoreBoard[a].score<ScoreBoard[j].score)
            {
            c=ScoreBoard[a].score;
            ScoreBoard[a].score=ScoreBoard[j].score;
            ScoreBoard[j].score=c;
              sprintf(temp, "%s",ScoreBoard[a].player );
              sprintf(ScoreBoard[a].player, "%s",ScoreBoard[j].player );
              sprintf(ScoreBoard[j].player, "%s",temp );

          }
      }
    }
}

int setScore()
{
    //OPENING FILE
    FILE * stream = NULL;
    stream = fopen(HIGH_SCORE_FILE_NAME, "r+");
    if(stream == NULL) {
      stream = fopen(HIGH_SCORE_FILE_NAME, "w+");
      if(stream == NULL) {
        printf("Unable to load file ! \n");
        return -1;
      }
      printf("File created ! \n");
    }


    //GETTING LENGHT of ScoreBoard
    char buffer[256] = "";
    int lenght = 1;
    fpos_t pos;
    fgetpos(stream, &pos);
    while(fgets(buffer, sizeof(buffer), stream)) lenght++;

    //ARRAY OF SCORE
    PlayerScore * ScoreBoard = (PlayerScore *) malloc(lenght * sizeof(PlayerScore));
    for(int i = 0; i < lenght; i++) {
      sprintf(ScoreBoard[i].player, "%s", "");
      ScoreBoard[i].score = 0;
    }

    //COLLECTING ENTRIES
    fsetpos(stream, &pos);
    for(int i = 1; i < lenght; i++) {
    //  while (fgets(chaine, TAILLE_MAX, fichier) != NULL){
        fscanf(stream, "%s %d\n", &(ScoreBoard[i].player), &(ScoreBoard[i].score));
        if(!strcmp(ScoreBoard[i].player, "")) strcat(ScoreBoard[i].player, "No player");
    }

    //CLOSING FILE
    fclose(stream);

    //ADDING OR UPDATE ENTRY
    char blaz [MAX_LENGHT_PLAYER_NAME];
    printf("ENTREZ LE NOM DU VAINQUEUR:\n");
    printf(">> ");
    scanf("%s",blaz );
    printf("\n");

    int index = searchiInStringArray(blaz, ScoreBoard, lenght);
    if (index != -1)
    {
      printf("Profil existant \n");
      ScoreBoard[index].score++;
    }
    else
    {
      printf("Nouveau profil créé !\n" );
      sprintf(ScoreBoard[0].player, "%s", blaz);
      ScoreBoard[0].score = 1;
    }

    //PRINTING ENTRIES
    tri(lenght, ScoreBoard);
    int j = 0;
    printf("\n");
    for(int i = 0; i < MAX_SCORE_TO_PRINT && i < lenght; i++) {
        if(!strcmp(ScoreBoard[i].player, "")) {j--; continue;}
        printf("%d. %s : %d\n", i+j+1, ScoreBoard[i].player, ScoreBoard[i].score);

    }
    printf("\n");

    //WRINTING FILE
    stream = fopen(HIGH_SCORE_FILE_NAME, "w+"); //erase data
    if(stream != NULL){
      for(int i = 0; i < lenght; i++) {
          if(!strcmp(ScoreBoard[i].player, "")) continue;
          fprintf(stream, "%s %d\n",ScoreBoard[i].player, ScoreBoard[i].score);
      }
      fclose(stream);

    } else { printf("Unable to load file\n"); }

    free(ScoreBoard);

    return 0;
}

int printHighScore(int *red, int *green, int *blue, TTF_Font *font, SDL_Renderer *renderer, SDL_Window *window )
  {
    //reset the renderer memory
        SDL_RenderClear(renderer);
        SDL_Color white = {255, 255, 255, 0};


    /*********OPENING THE HS FILE*************/
    FILE * highscore = NULL;
    highscore = fopen("ressources/HS.txt", "r");
    if (highscore == NULL)
      {
        printf("erreur ouverture highscore\n");
        return 0;
      }


    /**********CREATING HS SURFACE N TEXTURE**************/
    int fontSize = 50;
    char toPrint[90] = ".";
    SDL_Surface *blazeSurface = TTF_RenderText_Solid(font, toPrint, white);
    if (!blazeSurface)
      SDL_EXITWITHERROR("creation blazeSurface");
    SDL_Texture *blazeTexture = SDL_CreateTextureFromSurface(renderer, blazeSurface);
    if(!blazeTexture)
      SDL_EXITWITHERROR("creation blazeTexture");
    SDL_Rect blazeRect;
    SDL_QueryTexture(blazeTexture, NULL, NULL, &blazeRect.w, &blazeRect.h);
    blazeRect.x = (WINDOW_LARGEUR - blazeRect.w) / 2;
    blazeRect.y = 20;


    
    char buffer[256] = "";
    int count = 0;
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, *red, *green, *blue, 0);
    while(count < MAX_SCORE_PRINT && fgets(buffer, sizeof(buffer), highscore))
      {
        char NAME[70];
        int SCORE;
        sscanf(buffer, "%s %d", NAME, &SCORE);
        sprintf(toPrint, "%s : %d", NAME, SCORE);
        blazeSurface = TTF_RenderText_Solid(font, toPrint, white);
        blazeTexture = SDL_CreateTextureFromSurface(renderer, blazeSurface);

        blazeRect.y += 50;
        SDL_QueryTexture(blazeTexture, NULL, NULL, &blazeRect.w, &blazeRect.h);
        blazeRect.x = (WINDOW_LARGEUR - blazeRect.w) / 2;
        SDL_RenderCopy(renderer, blazeTexture, NULL, &blazeRect); 
      }
    
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);

    SDL_DestroyTexture(blazeTexture);

  }
