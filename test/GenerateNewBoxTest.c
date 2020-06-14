#include <time.h>
#include "test.c"

#include "../src/headers/GameStructs.h"
#include "../src/headers/Game.h"

int main() {
	srand(time(NULL));

    GameState state;
    state.size = 4;
    state.board = malloc(state.size * sizeof(Box * [state.size])); //difference with Box * (*temp)[] = malloc(sizeof(Box *[size][size])) ?
    for (int i = 0; i < state.size; i++) state.board[i] = malloc(state.size * sizeof(Box*));
    printBoard(state.board, state.size);

    Box * box = generateNewBox(state.board, state.size);
    printBoard(state.board, state.size);

    free(box);
    for (int i = 0; i < state.size; i++) free(state.board[i]);
    free(state.board);


}