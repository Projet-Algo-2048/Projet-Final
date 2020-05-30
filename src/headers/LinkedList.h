#ifndef LinkedList
#define LinkedList

#include <stdlib.h>

#define foreach(i,list) for(Cell * i = list; i != NULL; i = i -> next) //iterate through a list

typedef struct cell Cell;
struct cell {
	void* value;
	Cell* next;
};

void addValue(Cell**, void*);
void addEndValue(Cell**, void*);
int removeCell(Cell**, Cell*);
void freeAll(Cell*);

#endif