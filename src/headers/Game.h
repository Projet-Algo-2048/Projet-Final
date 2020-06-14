#ifndef Game
#define Game

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "GameStructs.h"
#include "Utils.h"



int slide(Directions, Box * **, int);
bool canMove(Box * **, int);
int printBoard(Box * **, int);
Box * generateNewBox(Box * ** , int );
int game();

#endif