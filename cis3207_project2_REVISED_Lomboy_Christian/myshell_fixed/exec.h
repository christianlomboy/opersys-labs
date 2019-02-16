//
// Created by Christian Lomboy on 10/16/18.
//

#ifndef PROJECT2_EXEC_H
#define PROJECT2_EXEC_H

#define SINGLE_INPUT 0
#define SINGLE_OUTPUT 1
#define DOUBLE_OUTPUT 2

// Finds associated batchfile and executes program with it
void batchExec();

// Redirects I/O from stdout and/or stdin to a selected file output/input
void redirHandler(const char *filepath, char **input, int outPos, int d_outPos, int inPos);

// Executes process and redirects it to outf according to redirHandler
void redirExecute(const char *fp, char **args, const char *out_f, const char *in_f, int flag);

// Forks process then calls execvp
void execute(char *fp, char *args[], int argc);

// Finds and executes a program
void doIt(char *input[], int count);

#endif //PROJECT2_EXEC_H
