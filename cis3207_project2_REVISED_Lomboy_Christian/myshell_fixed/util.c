//
// Created by Christian Lomboy on 10/15/18.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <printf.h>
#include "util.h"
#include "commands.h"
#include "internals.h"

static int fd;
static fpos_t pos;

void clearStr(char *arr[], int count) {
    for (int i = 0; i < count; i++) {
        arr[i] = NULL;
    }
}

void output(const char *fPath) {
    int count = 0;
    int c;
    FILE *file;
    file = fopen(fPath, "r");
    if (file) {
        while ((c = getc(file)) != EOF) {
            putchar(c);
        }
        fclose(file);
    }
}

int countArgc(char *argv[]) {
    int count = -1;
    for (int i = 0; argv[i] != NULL; i++) {
        count++;
    };
    return count;
}


int charPosCheck(const char *c, char *input[], int count) {
    for (int i = 0; i < count; i++) {
        if (strcmp(input[i], c) == 0) {
            return i;
        }
    }
    return 0;
}

char *concat(const char *s1, const char *between, const char *s2) {
    char *retStr = malloc(strlen(s1) + strlen(between) + strlen(s2) + 1);
    strcpy(retStr, s1);
    if (strcmp(between, "\0") != 0) {
        strcat(retStr, between);
    }
    strcat(retStr, s2);
    return retStr;
}

void parse(const char *src, char *dst[], int count, char *split) {
    char *token = strtok((char *) src, split);
    while (token != NULL) {
        dst[count] = token;
        token = strtok(NULL, split);
        count++;
    }
    dst[count] = NULL;
}

char *findPath(const char *file, const char *path) {
    // Commented printf statements are for debugging...
    char *path_toks[100];
    char *file_path[100];
    int count = 0;

    // Parses path list into tokens
    parse(path, path_toks, count, ":");

    for (int i = 0; path_toks[i + 1] != NULL; i++) {
        // Combines path and file name
        file_path[i] = concat(path_toks[i], "/", file);
//        printf("\nFile path -> %s\n", file_path[i]);

        // Searches for file
        FILE *fp = fopen(file_path[i], "r");
        if (fp != NULL) {
//            printf("  FOUND in this path, ending path search... \n");
            fclose(fp);
            // Exits once file is found
            return file_path[i];
        }
    }
    // If this point is reached, file DNE in path
    printf("\nUnable to find file in PATH. \n");
    return NULL;
}


