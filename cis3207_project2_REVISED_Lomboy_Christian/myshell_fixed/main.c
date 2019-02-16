#include <stdio.h> // System libraries
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include "util.h" // User libraries
#include "internals.h"
#include "commands.h"


int main() {

    // Char array holds the current working directory of process
    char dir[FILENAME_MAX];

    // progLoc holds the location of the executable
    char progLoc[FILENAME_MAX];
    getcwd(progLoc, FILENAME_MAX);

    // Holds user input
    char theLine[100];



    while (endCondition != 1) {

        // argv and argc hold parameters and no. of parameters, respectively
        char *argv[100];
        int argc = 0;

        // environ array holds the environment variables for the process
        // PATH holds default paths, plus the process's original file path
        environ[PATH] = concat(getenv("PWD"), ":", "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
        environ[PWD] = getenv("PWD");
        environ[HOME] = getenv("HOME");
        environ[shell] = progLoc;

        getcwd(dir, FILENAME_MAX);
        printf("\n%s> ", dir);

        // Reads user input until newline
        scanf("%[^\n]s", theLine);

        printf("\n Command was: %s\n\n", theLine);

        // Checks if user inputs exit keywords
        if (strstr(theLine, "^D") || strstr(theLine, "exit")) {
            endCondition = 1;
        } else {
            // Parse user input word-by-word, places into argv array and
            // increments argc
            parse(theLine, argv, argc, " ");
            argc = countArgc(argv);
            handler(argv, argc);
        }
//        printf(" %s\n %s\n %s\n", argv[0], argv[1], argv[2]);2
        // Consumes newline char left in theLine, allows loop-able user input
        fgets(theLine, 100, stdin);
        clearStr(argv, argc);
    }
}


