//
// Created by Christian Lomboy on 10/16/18.
//

#include <stdio.h>
#include <dirent.h>
#include <stddef.h>
#include <string.h>
#include <printf.h>
#include <unistd.h>
#include "commands.h"
#include "internals.h"
#include "util.h"
#include "exec.h"

void changeDir(char *arg) {
    if (chdir(arg) == 0) {
        printf("\nWorking directory changed to: %s\n", arg);
        getcwd(environ[PWD], FILENAME_MAX);
    } else {
        printf("\nError: directory '%s' does not exist\n", arg);
    }
}

void clear() {
    // ANSI escape code
    printf("\033[H\033[J");
}

void dirContents(char *arg) {
    DIR *dir;
    struct dirent *stream;
    if ((dir = opendir(arg)) != NULL) {
        while ((stream = readdir(dir)) != NULL) {
            if (!strcmp(stream->d_name, ".") || !strcmp(stream->d_name, "..")) {
                // do nothing (filters out '.' and '..' entries)
            } else {
                printf("%s\n", stream->d_name);
            }
        }
        closedir(dir);
    } else {
        printf("Error: contents of directory '%s' could not be listed", arg);
    }
}

void listEnvVars() {
    printf("PATH: %s\n", environ[PATH]);
    printf("PWD: %s\n", environ[PWD]);
    printf("HOME: %s\n", environ[HOME]);

}

void echo(char *line[]) {
    for (int i = 1; line[i] != NULL; i++) {

        // checks if string is a tab character
        // if it is, it doesn't get printed
        if (strcmp(line[i], "\t") != 0) {
            for (int j = 0; j < strlen(line[i]); j++) {

                // checks if string contains tab character
                if (line[i][j] == '\t') {
                    // if found, don't print it
                    // (do nothing)
                } else {
                    printf("%c", line[i][j]);
                }
            }
            printf(" ");
        }
    }
    printf("\n");
}

void help() {
    char input[10];
    fgets(input, 100, stdin);

    int count = 0;
    int c;
    FILE *file;

    // readme.txt is opened using WHERE path variable
    // this allows the shell to access readme from anywhere in the system
    file = fopen(concat(environ[shell], "/", "readme.txt"), "r");
    if (file) {
        while ((c = getc(file)) != EOF) {
            putchar(c);
            // line counter
            if (c == '\n') {
                count++;
            }
            // if statement interrupts printing to prompt user - 'more' or 'q'
            if (count >= 10) {
                while ((strcmp(input, "more") != 0) && (strcmp(input, "q") != 0)) {
                    printf("\ntype 'more' to continue, or 'q' to return to shell: ");
                    scanf("%[^\n]s", input);
                    // 'q' ends printing and returns to shell
                    if (strcmp(input, "q") == 0) {
                        fclose(file);
                        return;
                    }
                }
                count = 0;
                fgets(input, 100, stdin);
            }
        }
        fclose(file);
    } else {
        printf("\n'readme' not found. Please make sure 'readme' is in the executable folder.\n");
    }
}

void pauseExec() {
    char input[10];
    fgets(input, 100, stdin);
    while (strcmp(input, "\n") != 0) {
        scanf("%s", input);
    }
}

void handler(char *input[], int count) {
    char *cmd = input[0];
    char *arg = input[1];


    // makeshift switch statement using if-else ladder
    if (strcmp(cmd, "cd") == 0) {
        // change current working dir to <directory>
        changeDir(arg);
    } else if (strcmp(cmd, "clr") == 0) {
        // clear screen
        clear();
    } else if (strcmp(cmd, "dir") == 0) {
        // list contents in <directory>
        dirContents(arg);
    } else if (strcmp(cmd, "environ") == 0) {
        // list environment strings
        listEnvVars();
    } else if (strcmp(cmd, "echo") == 0) {
        // display <comment> on the display followed
        // by a new line (multiple spaces/tabs may be reduced to a
        // single space)
        echo(input);
    } else if (strcmp(cmd, "help") == 0) {
        // display user manual w/ 'more' functionality
        help();
    } else if (strcmp(cmd, "pause") == 0) {
        // pause operation of shell until 'enter' key is hit
        pauseExec();
    } else if (strcmp(cmd, "quit") == 0) {
        endCondition = 1;
        printf("\nShell terminated");
    } else {
        // input[0] is a program
        doIt(input, count);
    }
}

