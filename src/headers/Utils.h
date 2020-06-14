#ifndef Utils
#define Utils

#include <stdlib.h>
#include <stdio.h>
#include "GameStructs.h"

int power(int number, int power);
Box* copyBox(Box* box);
Board copyBoard(Board board, int size);
int freeBoard(Board board, int size);

#endif 
