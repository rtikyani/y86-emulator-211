#ifndef _DIRECTIVES_H_
#define _DIRECTIVES_H_

#define TEXT_DIRECTIVE ".text"
#define BYTE_DIRECTIVE ".byte"
#define LONG_DIRECTIVE ".long"
#define STRING_DIRECTIVE ".string"

void textDirective(char *string, int index);

void byteDirective(char *string, int index);

void longDirective(char *string, int index);

void stringDirective(char *string, int index);

#endif