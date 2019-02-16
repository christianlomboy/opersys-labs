//
// Created by Christian Lomboy on 10/15/18.
//

#ifndef PROJECT2_SHELL_H
#define PROJECT2_SHELL_H

#include <printf.h> // for fpos_t declaration

// File descriptor integer
static int fd;
// Static fpos_t variable used to remember position of its assigned file
static fpos_t pos;

// Frees (empties) a string array
void clearStr(char *arr[], int count);

// Writes characters to stdout
void output(const char *fPath);

// Counts elements in argv array
int countArgc(char *argv[]);

// Checks string for char, returns index if found
int charPosCheck(const char *c, char *input[], int count);

// Concatenates two strings, with a specified character between them (e.g. '/' or '.')
char *concat(const char *s1, const char *between, const char *s2);

// Parses input word-by-word and places parsed words into a char pointer array
void parse(const char *src, char *dst[], int count, char *split);

// Given a file name and a list of absolute pathnames, function checks if file
// is in one of the paths - returns absolute pathname of file if found, empty
// string if not found
char *findPath(const char *file, const char *path);

#endif //PROJECT2_SHELL_H
