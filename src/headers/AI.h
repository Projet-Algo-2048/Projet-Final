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

int AILevel1(Board board, int size);
int evalBoard(Board board, int size);
int AILevel2(Board board, int size);
int AILevel3(Board board, int size, int recursion);

#endif