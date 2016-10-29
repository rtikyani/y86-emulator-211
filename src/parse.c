#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "data.h"
#include "directives.h"

void parse_file(FILE *file) {
    char line[2000];
    char string[6];
    int index;

    int lineIndex = 0;
    while (fgets(line, 2000, file) != NULL) {

        if (lineIndex == 0) {
            int size;
            sscanf(line, "%s %x\n", string, &size);
            memory = (char *) malloc(sizeof(char) * size);

            lineIndex++;
            continue;
        }

        char *token = strtok(line, TOKENIZE_STRING);

        if (strcmp(token, TEXT_DIRECTIVE) == 0) {

            token = strtok(NULL, TOKENIZE_STRING);
            sscanf(token, "%x", &index);
            counter = index;

            token = strtok(NULL, TOKENIZE_STRING);
            textDirective(token, index);

        } else if (strcmp(token, LONG_DIRECTIVE) == 0) {

            token = strtok(NULL, TOKENIZE_STRING);
            sscanf(token, "%x", &index);

            token = strtok(NULL, TOKENIZE_STRING);
            longDirective(token, index);

        } else if (strcmp(token, BYTE_DIRECTIVE) == 0) {

            token = strtok(NULL, TOKENIZE_STRING);
            sscanf(token, "%x", &index);

            token = strtok(NULL, TOKENIZE_STRING);
            byteDirective(token, index);

        } else if (strcmp(token, STRING_DIRECTIVE) == 0) {

            token = strtok(NULL, TOKENIZE_STRING);
            sscanf(token, "%x", &index);

            token = strtok(NULL, TOKENIZE_STRING);
            token++;

            while (token != NULL) {
                char *next = strtok(NULL, TOKENIZE_STRING);

                size_t length;
                if (next != NULL) {

                    length = strlen(token);
                    stringDirective(token, index);

                    index += length;
                    memory[index] = ' ';

                    index++;
                    token = next;
                } else {
                    token[strlen(token) - 1] = '\0';

                    length = strlen(token);
                    stringDirective(token, index);

                    index += length;

                    index++;
                    memory[index] = '\0';
                    break;
                }

            }

        } else {
            fprintf(stderr, "ERROR: Invalid directive.\n");
            exit(1);
        }

        lineIndex++;
    }

}