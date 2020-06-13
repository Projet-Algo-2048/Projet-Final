/**
 * @file LinkedList.c
 * @brief contain Linkedlist functions
 */

#include "headers/LinkedList.h"

/**
 * @fn void addValue(Cell ** header, void * value)
 * @brief add a value at begining
 *
 * @param header the list to which add
 * @param value a pointer toward the value to add
 *
 * @return nothing
 */
void addValue(Cell** header, void* value) {
	Cell* cell = (Cell*)malloc(sizeof(Cell));
	cell->value = value;
	cell->next = *header;
	*header = cell;
}



/**
 * @fn void addEndValue(Cell ** header, void * value)
 * @brief add a value at end
 *
 * @param header the list to which add
 * @param value a pointer toward the value to add
 *
 * @return nothing
 */
void addEndValue(Cell** header, void* value) {
	Cell* cell = (Cell*)malloc(sizeof(Cell));
	cell->value = value;
	cell->next = NULL;

	if (*header == NULL) {
		*header = cell;
	} else {
		Cell* j = NULL;
		foreach(i, *header) {
			j = i;
		}
		j->next = cell;
	}
}

/**
 * @fn int removeCell(Cell ** header, Cell * cell)
 * @brief remove a cell of the list. DO NOT FREE (desired for later use possibility)
 *
 * @param header the list
 * @param cell the cell to remove
 *
 * @return 0 if cell has been remove or -1 otherwise
 */
int removeCell(Cell** header, Cell* cell) {
	if (cell == NULL) return -1;

	if (*header == cell) {
		*header = cell->next;
		return 0;
	}
	foreach(i, *header) {
		if (i->next == cell) {
			i->next = cell->next;
			return 0;
		}
	}
	return -1;
}

/**
 * @fn Cell2Cyclic* asCell2Cyclic(Cell* cell)
 * @brief transform a Simple Linked List into a Cyclic Double linked list
 * @param cell pointer to the first element of the linked list
 * @return a pointer to one element of the cyclic 
 */
Cell2Cyclic* asCell2Cyclic(Cell* cell) {
	if (cell == NULL) return NULL;

	Cell2Cyclic* startCell = malloc(sizeof(Cell2Cyclic));
	startCell->value = cell->value;

	Cell2Cyclic* lastCell = startCell;
	foreach(i, cell->next) {
		Cell2Cyclic* temp = malloc(sizeof(Cell2Cyclic));
		temp->value = i->value;
		lastCell->next = temp;
		temp->previous = lastCell;
		lastCell = temp;
	}
	startCell->previous = lastCell;
	lastCell->next = startCell;
	return startCell;
}

/**
 * @fn void freeAll(Cell* header)
 * @brief free all Cell of a list. BUT DO NOT FREE VALUE !
 *
 * @param header the first element a the list
 *
 * @return nothing
 */
void freeAll(Cell* header) {
	if (header != NULL) {
		Cell* next = header->next;

		freeAll(next);
		free(header);
	}
}
