#ifndef LinkedList
#define LinkedList

#include <stdlib.h>

/**
 * @def foreach(i, list) macro to iterate through a simple LinkedList
 */
#define foreach(i,list) for(Cell * i = list; i != NULL; i = i -> next) //iterate through a list

/**
 * @struct cell
 * @brief is one element of a simple linked list  
 */
typedef struct cell Cell;
struct cell {
	void* value;
	Cell* next;
};

/**
 * @struct Cell2Cyclic
 * @brief is one element of a cyclic double linked list
 */
typedef struct cell2Cyclic Cell2Cyclic;
struct cell2Cyclic {
    void* value;
    Cell2Cyclic* next;
    Cell2Cyclic* previous;
};

void addValue(Cell**, void*);
void addEndValue(Cell**, void*);
int removeCell(Cell**, Cell*);
Cell2Cyclic* asCell2Cyclic(Cell*);
void freeAll(Cell*);

#endif