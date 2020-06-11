/**
 * @file GameStruct.c
 * @brief This file will contain all structure need to the basic game
 */

#ifndef GameStructs
#define GameStructs

/**
 * @enum Directions
 * @brief represente a direction
 */
typedef enum {
    UP,
    LEFT,
    DOWN,
    RIGHT
} Directions;

/**
 * @struct Box
 * @brief represente a box in the game.
 * We choose to create a new struct in case we want to add new feature easily
 */
typedef struct {
    int value;                          /*< the score of the box*/
} Box;

/**
 * @struct GameState
 * @brief represente a the game state.
 * It gather all information about the game into one struct
 */
typedef struct {
    int size;                           /*< size of the board*/
    Box*** board1;
    Box*** board2;                     /*< the game board */
} GameState;

#endif
