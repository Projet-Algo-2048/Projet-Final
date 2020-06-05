/**
 * @file Utils.c
 * @brief this file will contain all utils fonction for the game
 */

/**
 * @fn int pow(int number, int power)
 * @brief compute the result of 'number' to power of 'power'
 */
int power(int number, int power) {
    int value = 1;
    for (int i = 0; i < power; i++) {
        value = value * number;
    }
    return value;
}
