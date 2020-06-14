/**
 * @file GameSaver.c
 * @brief this file will handle game saving and loading
 */

#include "headers/GameSaver.h"

int saveGame(GameState * state) {
    FILE* stream = NULL;

    //================[Open File]===================
    stream = fopen(SAVE_FILE_NAME, "r+");

    if (stream == NULL) {
        printf("[WARN] File do not exist creating it !\n");
        stream = fopen(SAVE_FILE_NAME, "w+");
        if (stream == NULL) {
            printf("[ERROR] can not open save file\n");
            return SAVEFILE_NOT_OPEN;
        }
    }
    //==============================================
    
     //=============[Write in Buffer]================
    char buffer[1024] = { 0 };
    char args[128] = { 0 };

    sprintf(args, "%s : %d\n", SIZE_DATA, state->size);
    strcat(buffer, args);

    sprintf(args, "%s : \n", BOARD_DATA);
    strcat(buffer, args);
    for (int i = 0; i < state->size; i++) {
        for (int j = 0; j < state->size; j++) {
            char temp[10] = { 0 };
            sprintf(temp, "%d", (state->board[i][j] == NULL) ? 0 : state->board[i][j]->value);
            
            strcat(buffer, temp);

            if(j + 1 < state->size)strcat(buffer, GAP_CHAR);
        }
        strcat(buffer, "\n");
    }
    //==============================================

    //===============[Write File]===================
    fprintf(stream, buffer);
    //==============================================

    //===============[Close File]===================
    if (stream != NULL) fclose(stream);
    //==============================================
}

int loadGame(GameState* state) {
    FILE* stream = NULL;

    //================[Open File]===================
    printf("Loading game ... \n");
    stream = fopen(SAVE_FILE_NAME, "r");
    if (stream == NULL) return SAVEFILE_NOT_EXIST;
    //==============================================

    //================[Read File]===================
    char buffer[1024];  //buffer which will contain one line

    while (fgets(buffer, sizeof(buffer), stream) != NULL) { //read until end of file
        if (buffer[0] == '#') continue;         // ignore comment
        char key[256] = "";
        char value[256] = "";

        sscanf(buffer, "%s : %s", key, value);  //scaning string to find pair key/value. Deprecated : use instead strsrch()

        if (!strcmp(key, SIZE_DATA)) {          // SIZE
            printf("[INFO] Board size is : %s\n", value);
            state->size = atoi(value);

            state->board = malloc( state->size * sizeof(Box**) );
            for (int i = 0; i < state->size; i++) {
                state->board[i] = malloc(state->size * sizeof(Box*));
                for (int j = 0; j < state->size; j++) state->board[i][j] = NULL;
            }
        }
        if (!strcmp(key, BOARD_DATA)) {         // BOARD
            printf(" [INFO] loading board\n");

            for (int i = 0; i < state->size; i++) {
                if (fgets(buffer, sizeof(buffer), stream) == NULL) return SAVEFILE_CORRUPTED;
                for (int j = 0; j < state->size; j++) {
                    int value = (j == 0) ? atoi(strtok(buffer, GAP_CHAR)) : atoi(strtok(NULL, GAP_CHAR));
                    if (value != 0) {
                        Box* box = malloc( sizeof(Box) );
                        box->value = value;
                        state->board[i][j] = box;
                    }
                }
            }
            printf("[INFO] Board loaded\n");
        }
    }
    //==============================================

    //===============[Close File]===================
    if (stream != NULL) fclose(stream);
    //==============================================
    return 1;
}

int deleteSave() {
    remove(SAVE_FILE_NAME);
}