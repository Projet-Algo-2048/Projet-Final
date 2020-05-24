#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "GameStructs.h"
#include "Utils.h"

#ifndef Game
#define Game

int printBoard(Box * **, int);
Box * generateNewBox(Box * ** , int );
int game();

#endif