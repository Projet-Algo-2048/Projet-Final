/**
 * @file test.c
 * @brief this file is a library for testing function. It will not be called by the Makefile but must be include in your test file.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * @fn int testInt(int expression, int expected)
 * @brief Check if evaluated expression and expected int are equal and print it
 * @param expression the expression to evaluate
 * @param expected the value expected
 * @return nothing
 */
int testInt(int expression, int expected) {
	if (expected == expression) {
		printf("\x1b[32m Test Succesfully passed : \n\t expected %d and got %d \x1b[0m \n", expected, expression);
	}
	else {
		printf("\x1b[31m Test Error : \n\t expected %d and got %d \x1b[0m \n", expected, expression);
	}
	printf("\n");
}

/**
 * @fn int testInt(int expression, int expected)
 * @brief Check if evaluated expression and expected string are equal and print it
 * @param expression the expression to evaluate
 * @param expected the value expected
 * @return nothing
 */
int testString(char* expression, char* expected) {
	if (!strcmp(expected, expression)) {
		printf("\x1b[32m Test Succesfully passed : \n\t expected %s and got %s \x1b[0m \n", expected, expression);
	}
	else {
		printf("\x1b[31m Test Error : \n\t expected %s and got %s \x1b[0m \n", expected, expression);
	}
	printf("\n");
}

/**
 * @fn int testInt(int expression, int expected)
 * @brief Check if evaluated expression and expected pointer are equal and print it
 * @param expression the expression to evaluate
 * @param expected the value expected
 * @param equal a boolean value if value must be equal (true) or different (false)
 * @return nothing
 */
int testPointer(void* expression, void* expected, bool equal) {
	char temp[4] = "";
	if (!equal) sprintf(temp, "not");

	if ((equal && expected == expression) || (!equal && expected != expression)) {
		printf("\x1b[32m Test Succesfully passed : \n\t expected %s %p and got %p \x1b[0m \n", temp, expected, expression);
	}
	else {
		printf("\x1b[31m Test Error : \n\t expected %s %p and got %p \x1b[0m \n", temp, expected, expression);
	}
	printf("\n");
}