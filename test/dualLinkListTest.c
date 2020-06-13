#include "test.c"

#include "../src/headers/LinkedList.h"

int main(void) {
	int a = 1, b = 2, c = 3;
	Cell c1;
	Cell c2;
	Cell c3;
	c1.value = &a;
	c2.value = &b;
	c3.value = &c;
	c1.next = &c2;
	c2.next = &c3;
	c3.next = NULL;

	Cell2Cyclic * list = asCell2Cyclic(&c1);
	printf("%d", *((int *)list->value) );
	printf("%d", *((int*)(list = list->next)->value));
	printf("%d", *((int*)(list = list->next)->value));
	printf("%d", *((int*)(list = list->next)->value));
	printf("%d", *((int*)list->value) );
	printf("%d", *((int*)(list = list->previous)->value));
	printf("%d", *((int*)(list = list->previous)->value));
}