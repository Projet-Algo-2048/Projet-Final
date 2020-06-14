#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "GameStructs.h"
#include "Utils.h"

#ifndef Game
#define Game

int slide(Directions, GameState *);
bool canMove(GameState *);
int printBoard(GameState *);
Box * generateNewBox(GameState *);
int game();

#endif
