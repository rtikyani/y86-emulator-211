#include <stdio.h>
#include "instructions.h"
#include "data.h"

void nop() {
    counter += 1;
}

void rrmovl() {
    bitfield_t *bitfield = (bitfield_t *) (memory + counter + 1);
    int upper = bitfield->upper;
    int lower = bitfield->lower;

    if (upper >= 0 && upper <= 8 && lower >= 0 && lower <= 8) {
        registers[upper] = registers[lower];
        counter += 2;
    } else {
        status = ERR;
    }
}

void irmovl() {
    bitfield_t *bitfield = (bitfield_t *) (memory + counter + 1);
    int index = bitfield->upper;

    if (bitfield->lower == 0xf && index >= 0 && index <= 8) {
        int value = *(int *) (memory + counter + 2);
        registers[index] = value;
        counter += 6;
    } else {
        status = ERR;
    }
}

void rmmovl() {
    bitfield_t *bitfield = (bitfield_t *) (memory + counter + 1);
    int value = *(int *) (memory + counter + 2);
    int upper = bitfield->upper;
    int lower = bitfield->lower;

    if (upper >= 0 && upper <= 8 && lower >= 0 && lower <= 8) {
        int upperValue = registers[upper];
        int lowerValue = registers[lower];
        int address = upperValue + value;
        int *memArray = (int *) (memory + address);
        *memArray = lowerValue;
        counter += 6;
    } else {
        status = ERR;
    }
}

void mrmovl() {
    bitfield_t *bitfield = (bitfield_t *) (memory + counter + 1);
    int value = *(int *) (memory + counter + 2);
    int upper = bitfield->upper;
    int lower = bitfield->lower;

    if (upper >= 0 && upper <= 8 && lower >= 0 && lower <= 8) {
        int valueOfUpperRegister = registers[upper];
        int address = valueOfUpperRegister + value;
        registers[lower] = *(int *) (memory + address);
        counter += 6;
    } else {
        status = ERR;
    }
}

void addl() {
    bitfield_t *bitfield = (bitfield_t *) (memory + counter + 1);
    int upper = bitfield->upper;
    int lower = bitfield->lower;

    if (upper >= 0 && upper <= 8 && lower >= 0 && lower <= 8) {
        int upperValue = registers[upper];
        int lowerValue = registers[lower];
        int sum = upperValue + lowerValue;
        registers[upper] = sum;

        if (sum == 0) {
            ZF = 1;
        } else {
            ZF = 0;
        }

        if ((lowerValue > 0 && upperValue > 0 && sum < 0) || (lowerValue < 0 && upperValue < 0 && sum > 0)) {
            OF = 1;
        } else {
            OF = 0;
        }

        if (sum < 0) {
            SF = 1;
        } else {
            SF = 0;
        }

        counter += 2;
    } else {
        status = ERR;
    }
}

void subl() {
    bitfield_t *bitfield = (bitfield_t *) (memory + counter + 1);
    int upper = bitfield->upper;
    int lower = bitfield->lower;

    if (upper >= 0 && upper <= 8 && lower >= 0 && lower <= 8) {
        int upperValue = registers[upper];
        int lowerValue = registers[lower];
        int difference = upperValue - lowerValue;

        registers[upper] = difference;

        if (difference == 0) {
            ZF = 1;
        } else {
            ZF = 0;
        }

        if ((lowerValue < 0 && upperValue > 0 && difference < 0) ||
            (lowerValue > 0 && upperValue < 0 && difference > 0)) {
            OF = 1;
        } else {
            OF = 0;
        }

        if (difference < 0) {
            SF = 1;
        } else {
            SF = 0;
        }

        counter += 2;
    } else {
        status = ERR;
    }
}

void andl() {
    bitfield_t *bitfield = (bitfield_t *) (memory + counter + 1);
    int upper = bitfield->upper;
    int lower = bitfield->lower;

    if (upper >= 0 && upper <= 8 && lower >= 0 && lower <= 8) {
        int upperValue = registers[upper];
        int lowerValue = registers[lower];
        int and = upperValue & lowerValue;
        registers[upper] = and;
        if (and == 0) {
            ZF = 1;
        } else {
            ZF = 0;
        }
        if (and < 0) {
            SF = 1;
        } else {
            SF = 0;
        }
        OF = 0;
        counter += 2;
    } else {
        status = ERR;
    }
}

void xorl() {
    bitfield_t *bitfield = (bitfield_t *) (memory + counter + 1);
    int upper = bitfield->upper;
    int lower = bitfield->lower;

    if (upper >= 0 && upper <= 8 && lower >= 0 && lower <= 8) {
        int upperValue = registers[upper];
        int lowerValue = registers[lower];
        int xor = upperValue ^lowerValue;

        registers[upper] = xor;

        if (xor == 0) {
            ZF = 1;
        } else {
            ZF = 0;
        }

        if (xor < 0) {
            SF = 1;
        } else {
            SF = 0;
        }

        OF = 0;

        counter += 2;
    } else {
        status = ERR;
    }
}

void mull() {
    bitfield_t *bitfield = (bitfield_t *) (memory + counter + 1);
    int upper = bitfield->upper;
    int lower = bitfield->lower;

    if (upper >= 0 && upper <= 8 && lower >= 0 && lower <= 8) {
        int upperValue = registers[upper];
        int lowerValue = registers[lower];
        int product = upperValue * lowerValue;

        registers[upper] = product;

        if (product == 0) {
            ZF = 1;
        } else {
            ZF = 0;
        }

        if ((lowerValue > 0 && upperValue > 0 && product < 0) || (lowerValue < 0 && upperValue < 0 && product < 0) ||
            (lowerValue < 0 && upperValue > 0 && product > 0) || (lowerValue > 0 && upperValue < 0 && product > 0)) {
            OF = 1;
        } else {
            OF = 0;
        }

        if (product < 0) {
            SF = 1;
        } else {
            SF = 0;
        }

        counter += 2;
    } else {
        status = ERR;
    }
}

void cmpl() {
    counter += 2;
}

void jmp() {
    int value = *(int *) (memory + counter + 1);
    counter = value;
}

void jle() {
    int value = *(int *) (memory + counter + 1);

    if (((SF ^ OF) | ZF) == 1) {
        counter = value;
    } else {
        counter += 5;
    }
}

void jl() {
    int value = *(int *) (memory + counter + 1);

    if ((SF ^ OF) == 1) {
        counter = value;
    } else {
        counter += 5;
    }
}

void je() {
    int value = *(int *) (memory + counter + 1);

    if (ZF == 1) {
        counter = value;
    } else {
        counter += 5;
    }
}

void jne() {
    int value = *(int *) (memory + counter + 1);

    if (ZF == 0) {
        counter = value;
    } else {
        counter += 5;
    }
}

void jge() {
    int value = *(int *) (memory + counter + 1);

    if ((SF ^ OF) == 0) {
        counter = value;
    } else {
        counter += 5;
    }
}

void jg() {
    int value = *(int *) (memory + counter + 1);

    if (((SF ^ OF) & ZF) == 0) {
        counter = value;
    } else {
        counter += 5;
    }
}

void call() {
    int value = *(int *) (memory + counter + 1);
    registers[8] = counter + 5;
    push(8);
    counter = value;
}

void ret() {
    pop(8);
    counter = registers[8];
}

void pushl() {
    bitfield_t *bitfield = (bitfield_t *) (memory + counter + 1);

    int registerIndex = bitfield->lower;
    if (bitfield->upper == 0xf && registerIndex >= 0 && registerIndex <= 8) {
        push(registerIndex);
    } else {
        status = ERR;
    }
}

void push(int idx) {
    int value = registers[idx];
    int esp = registers[4] - 4;
    int *memArray = (int *) (memory + esp);
    *memArray = value;
    registers[4] = esp;
    counter += 2;
}

void popl() {
    bitfield_t *bitfield = (bitfield_t *) (memory + counter + 1);

    int registerIndex = bitfield->lower;
    if (bitfield->upper == 0xf && registerIndex >= 0 && registerIndex <= 8) {
        pop(registerIndex);
    } else {
        status = ERR;
    }
}

void pop(int idx) {
    int value = registers[4];
    int esp = value + 4;
    int memArray = *(int *) (memory + value);
    registers[4] = esp;
    registers[idx] = memArray;
    counter += 2;
}

void readl() {
    bitfield_t *bitfield = (bitfield_t *) (memory + counter + 1);
    int lower = bitfield->lower;
    int *value = (int *) (memory + counter + 2);
    int input;

    if (bitfield->upper == 0xf && lower >= 0 && lower <= 8) {

        OF = 0;
        SF = 0;

        if (scanf("%d", &input) == EOF) {
            ZF = 1;
        } else {
            int *longValue = (int *) (memory + registers[lower] + *value);
            *longValue = input;

            ZF = 0;
        }

        counter += 6;
    } else {
        status = ERR;
    }
}

void readb() {
    bitfield_t *bitfield = (bitfield_t *) (memory + counter + 1);
    int lower = bitfield->lower;
    int *num = (int *) (memory + counter + 2);

    unsigned char input;

    if (bitfield->upper == 0xf && lower >= 0 && lower <= 8) {
        OF = 0;
        SF = 0;

        if (scanf("%c", &input) == EOF) {
            ZF = 1;
        } else {
            unsigned char *byte = (unsigned char *) (memory + registers[lower] + *num);
            *byte = input;
            ZF = 0;
        }

        counter += 6;
    } else {
        status = ERR;
    }
}

void writeb() {
    bitfield_t *bitfield = (bitfield_t *) (memory + counter + 1);
    int lower = bitfield->lower;
    int value = *(int *) (memory + counter + 2);

    if (bitfield->upper == 0xf && lower >= 0 && lower <= 8) {
        unsigned char *byte = (unsigned char *) (memory + registers[lower] + value);
        printf("%c", *byte);
        counter += 6;
    } else {
        status = ERR;
    }
}

void writel() {
    bitfield_t *bitfield = (bitfield_t *) (memory + counter + 1);
    int lower = bitfield->lower;
    int value = *(int *) (memory + counter + 2);

    if (bitfield->upper == 0xf && lower >= 0 && lower <= 8) {
        int *longToWrite = (int *) (memory + registers[lower] + value);
        printf("%d", *longToWrite);
        counter += 6;
    } else {
        status = ERR;
    }
}