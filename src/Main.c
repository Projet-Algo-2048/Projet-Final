#ifndef Main
#define Main

#include <stdio.h>
/**
 * @struct Box
 * @brief represente a box in the game
 */
typedef struct {
    int value;
} Box;

#define BOARD_LENGHT 4
/**
 * @def board
 * @brief use struct box if we want to add feature
 */
Box* board[BOARD_LENGHT][BOARD_LENGHT] = NULL;

int main(int argc, char** argv) {
	printf("Hello Wolrd ! \n");
}
#endif