#include "test.c"
#include "../src/AI.c"

int main(void) {
	printf("Testing maxof function \n");
	testInt(maxof(4, 3, 1, -9, 5), 5);
}