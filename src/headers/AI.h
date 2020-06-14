#ifndef AI
#define AI

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "GameStructs.h"
#include "Game.h"

//--- move thoses function aside ---
int maxof(int count, ...);
//----------------------------------

int AILevel1(GameState *);
int evalBoard(GameState *);
int AILevel2(GameState *);
int AILevel3R(GameState*, int);
int AILevel3(GameState *);


#endif