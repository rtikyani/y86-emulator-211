#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y86emul.h"
#include "data.h"
#include "instructions.h"
#include "directives.h"
#include "parse.h"

void decode(unsigned char *instruction) {
    switch (*instruction) {

        case NOP:
            nop();
            break;

        case HALT:
            status = HLT;
            break;

        case RRMOVL:
            rrmovl();
            break;

        case IRMOVL:
            irmovl();
            break;

        case RMMOVL:
            rmmovl();
            break;

        case MRMOVL:
            mrmovl();
            break;

        case ADDL:
            addl();
            break;

        case SUBL:
            subl();
            break;

        case ANDL:
            andl();
            break;

        case XORL:
            xorl();
            break;

        case MULL:
            mull();
            break;

        case CMPL:
            cmpl();
            break;

        case JMP:
            jmp();
            break;

        case JLE:
            jle();
            break;

        case JL:
            jl();
            break;

        case JE:
            je();
            break;

        case JNE:
            jne();
            break;

        case JGE:
            jge();
            break;

        case JG:
            jg();
            break;

        case CALL:
            call();
            break;

        case RET:
            ret();
            break;

        case PUSHL:
            pushl();
            break;

        case POPL:
            popl();
            break;

        case READB:
            readb();
            break;

        case READL:
            readl();
            break;

        case WRITEB:
            writeb();
            break;

        case WRITEL:
            writel();
            break;

        case MOVSBL:
            mrmovl();
            break;

        default:
            status = ERR;
            break;
    }
}

void run(char *memory) {

    while (status == AOK) {
        unsigned char *instruction = (unsigned char *) (memory + counter);
        decode(instruction);
    }

    if (status == HLT) {
        exit(0);
    } else {
        fprintf(stderr, "ERROR: Invalid instruction or address.");
        exit(1);
    }

}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Error: You must have 2 arguments.\n");
        exit(1);
    }

    if (strcmp(argv[1], "-h") == 0) {
        printf("Usage: y86emul <y86 input file>\n");
        exit(0);
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        fprintf(stderr, "ERROR: The file does not exist.\n");
        exit(1);
    }

    parse_file(file);

    fclose(file);

    status = AOK;
    run(memory);

    return 0;
}