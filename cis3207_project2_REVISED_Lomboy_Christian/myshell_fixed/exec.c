//
// Created by Christian Lomboy on 10/16/18.
//

#include <printf.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "exec.h"
#include "util.h"
#include "internals.h"

char *fileExecArgv(const char *in_f) {
    char fileIn[100];
    char *fileArgv[100];
    int fileArgc = 0;

    // batchfile is read into a char array
    FILE *file;
    file = fopen(in_f, "r");
    if (file) {
        while (fgets(fileIn, sizeof(fileIn), file));
    }
    // char array is parsed into argv array, then passed back into execute function
    parse(fileIn, fileArgv, fileArgc, " ");
    fclose(file);
    return *fileArgv;
}

void batchExec() {
    char fileIn[100];
    char *batchArgv[100];
    int batchArgc = 0;

    // batchfile is read into a char array
    FILE *batch;
    batch = fopen("batchfile.txt", "r");
    if (batch) {
        while (fgets(fileIn, sizeof(fileIn), batch));
    }
    // char array is parsed into argv array, then passed back into execute function
    parse(fileIn, batchArgv, batchArgc, " ");
    doIt(batchArgv, 0);
    fclose(batch);
}

void redirHandler(const char *filepath, char **input, int outPos, int d_outPos, int inPos) {
    // command holds program and arguments
    // redir holds input/output following > or <
    // outFile holds output file name
    char *command[100];
    char *redir[100];
    int flag;
    int i;
    int j = 0;

    // output handler '>'
    if (outPos > 0) {
        char *outFile;
        flag = SINGLE_OUTPUT;
        for (i = 0; i < outPos; i++) {
            command[i] = input[i];
        }
        command[i] = NULL;
        for (i = outPos + 1; input[i] != NULL; i++) {
            redir[j] = input[i];
        }
        redir[j + 1] = NULL;
        outFile = concat(redir[0], ".", "txt");
        FILE *fp = fopen(outFile, "a");
        fclose(fp);

        printf("Executing: %s\n\n", command[0]);
        redirExecute(filepath, command, outFile, NULL, flag);
    }

    // output handler '>>'
    if (d_outPos > 0) {
        char *outFile;
        flag = DOUBLE_OUTPUT;
        for (i = 0; i < d_outPos; i++) {
            command[i] = input[i];
        }
        command[i] = NULL;
        for (i = d_outPos + 1; input[i] != NULL; i++) {
            redir[j] = input[i];
        }
        redir[j + 1] = NULL;
        outFile = concat(redir[0], ".", "txt");

        printf("Executing: %s\n\n", command[0]);
        redirExecute(filepath, command, outFile, NULL, flag);
    }

    // input handler '<'
    if (inPos > 0) {
        char *inFile;
        flag = SINGLE_INPUT;
        for (i = 0; i < inPos; i++) {
            command[i] = input[i];
        }
        command[i] = NULL;
        for (i = inPos + 1; input[i] != NULL; i++) {
            redir[j] = input[i];
        }
        redir[j + 1] = NULL;
        inFile = concat(redir[0], ".", "txt");

        printf("Executing: %s\n\n", command[0]);
        redirExecute(filepath, command, NULL, inFile, flag);
    }
}


void redirExecute(const char *fp, char **args, const char *out_f, const char *in_f, int flag) {
    if (fork() == 0) {
        int fid;
        if (flag == SINGLE_OUTPUT) {
            // opens file, create it if it DNE
            // truncates if '>'
            fid = open(out_f, O_TRUNC | O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
            dup2(fid, STDOUT_FILENO);
            dup2(fid, STDERR_FILENO);
        } else if (flag == DOUBLE_OUTPUT) {
            // appended if '>>'
            fid = open(out_f, O_APPEND | O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
            dup2(fid, STDOUT_FILENO);
            dup2(fid, STDERR_FILENO);
        } else {
            // file opened to read stdin redirection
            fid = open(in_f, O_RDONLY, S_IRUSR | S_IWUSR);
            dup2(fid, STDIN_FILENO);
        }
        close(fid);
        execvp(fp, args);
    } else {
        int child = 0;
        wait(&child);
        printf("\nProcess exited with ID: %i\n", child);
    }
}

void bkgdExecute(char *fp, char *args[]) {
    if (fork() == 0) {
        // if child process
        execvp(fp, args);
    }
}


void execute(char *fp, char *args[], int argc) {
//    char *a = args[0];
//    char *b = args[1];
//    char *c = args[2];
//
//    printf(" %s\n %s\n %s\n", a, b, c);

    if (strchr(args[argc], '&') != NULL) {
        bkgdExecute(fp, args);
        return;
    };
    if (fork() == 0) {
        // if child process
        execvp(fp, args);
    } else {
        // if parent process, wait for child
        int status = 0;
        wait(&status);
        printf("\nChild exited with a status of %i\n", status);
    }
}


void doIt(char *input[], int count) {
    char *filePath = findPath(input[0], environ[PATH]);
    if (filePath != NULL) {

        // finds positions of redir chars (if used)
        int outPos = charPosCheck(">", input, count);
        int d_outPos = charPosCheck(">>", input, count);
        int inPos = charPosCheck("<", input, count);

        if (outPos != 0 || d_outPos != 0 || inPos != 0) {
            redirHandler(filePath, input, outPos, d_outPos, inPos);
            return;
        }

        // if command has arguments
        if (count > 1) {
            // if executing process from batchfile
            if (strcmp(input[1], "batchfile") == 0) {
                // execute program with batchfile commands
                batchExec();
                return;
            }
        }

        // execute the process
        execute(filePath, input, count);

    } else {
        printf("\nError: file not found\n");
        return;
    }
}
