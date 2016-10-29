#ifndef _DATA_H_
#define _DATA_H_

typedef struct {
    unsigned char upper: 4;
    unsigned char lower: 4;
} bitfield_t;

typedef enum {
    AOK, HLT, ERR
} state_t;

int registers[9];
int counter;
char *memory;
int ZF, OF, SF;

state_t status;

#endif