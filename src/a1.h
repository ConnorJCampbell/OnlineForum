#ifndef __A1_H__
#define __A1_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Checks the command line paramters and exits if there is not enough or too many
 */
void checkArg(int numArg);

/* Checks if the file that os entered exists, exits otherwise
 */
void nullFile(FILE* fptr);

/* Frees a 2D array that has been malloc'd for a specific size
 */
void freeArray(char ** array, int size);

/* Increases the size of a 2D array if its max is reached, takes its max size as a paramter
 */
char** extendArray(char ** array, int size);

/* Returns the next non-whitespace string in a 2D array, modifying the counter and printing out
 * the whitspace as it goes
 */
char* nextNonWhite(char** array, int* i, FILE* outFile);

/* Returns the next non-whitespace string in a 2D array, modifying the counter and concatenating
 * the whitspace onto the end of a string variable as it goes.
 */
char* nextNonWhiteCat(char** array, int* i, char* string);

/* Returns the next non-whitespace string in a 2D array, but does not alter the array or the counter,
 * and does not print anything to the file.
 */
char* nextNonWhiteSafe(char** array, int i);

/* Returns the index of the next non-whitespace string in a 2D array.
 */
int nextNonWhiteIndex(char** array, int i);

/* Returns the last non-whitespace string in a 2D array, but does not alter the array or the counter,
 * and does not print anything to the file.
 */
char* lastNonWhite(char** array, int i);

/* Returns the index of the last non-whitespace string in a 2D array.
 */
int lastNonWhiteIndex(char** array, int i);

/* Determines whether or not a set of parentheses represnt a function defintion
 * reutrns 1 if it is a finction definition, 0 if it is not. 
 */
int isFunctionDef(char** array, int i);

/* Takes in an array at the position of a function declaration, and modifies
 * the function name based on its parameters 
 */
void concatenateFunc(char* function, char** array, int i);

/* Returns the index of the next occurance of a comma string or left paranthesis string
 * in a 2D array.
 */
int commaIndex(char** array, int i);

/* Determines whether or not the previous string is a primitive data type such as int or double,
 * returns 1 if it matches one of these cases, 0 if not.
 */
int isVarType(char** array, int i);

/* Frees a 2D array that is the duplicate of another.
 */
void freeDuplicate(char** array, int size);

#endif
