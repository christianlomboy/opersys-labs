//
// Created by Christian Lomboy on 10/16/18.
//

#ifndef PROJECT2_COMMANDS_H
#define PROJECT2_COMMANDS_H

// Changes current working directory of process to pathname passed in
void changeDir(char *arg);

// Clears terminal screen
void clear();

// Lists contents of a passed in directory
void dirContents(char *arg);

// Function checks input for internal command
// If it is internal command, handler sends input to appropriate function
// If not, handler assumes command is a program, sends to file handler functions
void handler(char *input[], int count);

// Function prints input then starts new line
void echo(char *line[]);

// Finds readme.txt and prints it to prompt, features 'more' command
void help();

// Pauses execution of process
void pauseExec();

#endif //PROJECT2_COMMANDS_H
