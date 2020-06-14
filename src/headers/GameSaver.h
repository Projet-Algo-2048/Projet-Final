#ifndef GAMESAVER
#define GAMESAVER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GameStructs.h"

#define SAVE_FILE_NAME "game.save"
#define GAP_CHAR "-"
#define SIZE_DATA "Size"
#define BOARD_DATA "Board"

typedef enum {
	SAVEFILE_NOT_OPEN,
	SAVEFILE_NOT_EXIST,
	SAVEFILE_CORRUPTED,
} GameSaverReturn;

int saveGame(GameState*);
int loadGame(GameState*);
int deleteSave();

#endif // !GAMESAVER