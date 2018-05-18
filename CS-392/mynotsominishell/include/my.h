/*
 * my.h library
 *
 * Contains various methods for operations such as printing strings, printing
 * numbers, reversing strings, and others.
 *
 * See below method comments for more information.
 *
 * Last Edit: 10/08/14 12:38 PM
 */

#ifndef _MY_H_
#define _MY_H_

#ifndef NULL
#define NULL ((void *) 0)
#endif

#define INVALID -1

#include <unistd.h>
#include <stdlib.h>

void   my_char(char); /* Print a character to the screen */
void   my_str(char*); /* Print a string to the screen */
void   my_int(int); /* Print an integer to the screen */
void   my_num_base(int, char*); /* Prints the int in the base represented by char* */
void   my_alpha(); /* Print every letter in the alphabet from a-z */
int    my_atoi(char*); /* Convert a string to int */
void   my_digits(); /* Prints every digit in base 10 from 0-9 */
int    my_strlen(char*); /* Gets the length of a string */
int    my_revstr(char*); /* Reverse a string. Returns the length of the string  */
int    my_strpos(char*, char); /* Returns the index of the first occurance of the char in the char* */
int    my_strrpos(char*, char); /* Returns the index of the last occurance of the char in the char* */
char*  my_strdup(char*); /* Allocates and duplicate a string */
int    my_strcmp(char*, char*); /* Compares two strings, will return a negative, 0, or positive */
int    my_strncmp(char*, char*, unsigned int); /* Same as strcmp. Compare num characters of the second string to num characters in the first */
char*  my_strcpy(char*, char*); /* Copies src into dst, adding a \0 at the end */
char*  my_strncpy(char*, char*, unsigned int); /* Copy up to the first int characters from src to dst */
char*  my_strconcat(char*, char*); /* Creates a new string, concatinating s1 with s2 */
char*  my_strcat(char*, char*); /* Puts s2 at the end of s1 */
char*  my_strnconcat(char*, char*, unsigned int); /* Creates a new string with all of s1, and n characters of s2 */
char*  my_strfind(char*, char); /* Returns a pointer to the first instance of char in the char* */
char*  my_strrfind(char*, char); /* Same as above, but last instead of first */
char*  my_vect2str(char**); /* Convert a vector to a string */
char** my_str2vect(char*); /* Convert a string to a vector */
void   my_freevect(char**); /* Free the memory of a vector */
void*  xmalloc(unsigned int); /* malloc wrapper function */

#endif
