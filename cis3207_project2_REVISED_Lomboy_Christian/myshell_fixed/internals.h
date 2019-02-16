//
// Created by Christian Lomboy on 10/15/18.
//

#ifndef PROJECT2_INTERNALS_H
#define PROJECT2_INTERNALS_H

// Definitions for environment variable positions in array
#define PATH 0
#define PWD 1
#define HOME 2
#define shell 3


// Maximum string token size in user input
#define MAX_WORD_SIZE 100

// Environment variables for processes
extern char *environ[100];

// Signals when to end program loop
int endCondition;


#endif //PROJECT2_INTERNALS_H
