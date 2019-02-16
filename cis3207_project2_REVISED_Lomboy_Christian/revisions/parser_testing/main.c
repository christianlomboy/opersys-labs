#include <stdio.h>
#include <string.h>

int countArgc(char *argv[]) {
    int count = -1;
    for (int i = 0; argv[i] != NULL; i++) {
        count++;
    };
    return count;
}

/// Function being tested
void parse(const char *src, char *dst[], int count, char *split) {
    char *token = strtok((char *) src, split);
    while (token != NULL) {
        dst[count] = token;
        token = strtok(NULL, split);
        count++;
    }
    dst[count] = NULL;
}

int main() {
    printf("Testing 'parse' function...\n");

    char input[100];
    char *destination[100];
    int count = 0;

    // String will be delimited and parsed using '_' char
    // You may replace with any string or char
    char *split = "_";

    printf(" Enter a string to be parsed: ");

    // Reads in string to be parsed
    fgets(input, 100, stdin);

    // Calls the parse function
    parse(input, destination, count, split);

    // Used to count elements to be printed below
    count = countArgc(destination);

    printf("\n Here is the parsed string:");
    for (int i = 0; i <= count; i++) {
        printf("\n  %s", destination[i]);
    }

    return 0;
}