#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data.h"
#include "directives.h"

void textDirective(char *string, int index) {
    int tokenIndex = 0;
    int currentIndex = index;

    while (tokenIndex < strlen(string)) {
        bitfield_t *bitfield = (bitfield_t *) memory + currentIndex;

        char *upper = (char *) malloc(sizeof(char));
        strncpy(upper, string + tokenIndex + 1, 1);

        bitfield->upper = strtol(upper, NULL, 16);
        free(upper);

        char *lower = (char *) malloc(sizeof(char));
        strncpy(lower, string + tokenIndex, 1);

        bitfield->lower = strtol(lower, NULL, 16);
        free(lower);

        tokenIndex += 2;
        currentIndex++;
    }
}

void byteDirective(char *string, int index) {
    int value;
    sscanf(string, "%2x", &value);
    memory[index] = (char) value;
}

void longDirective(char *string, int index) {
    int value;
    sscanf(string, "%d", &value);
    memory[index] = value;
}

void stringDirective(char *string, int index) {
    while (*string != '\0') {
        memory[index] = *string;
        index++;
        string++;
    }
}