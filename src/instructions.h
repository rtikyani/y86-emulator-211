#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_

#define NOP (unsigned char) 0x00
#define HALT (unsigned char) 0x10
#define RRMOVL (unsigned char) 0x20
#define IRMOVL (unsigned char) 0x30
#define RMMOVL (unsigned char) 0x40
#define MRMOVL (unsigned char) 0x50
#define ADDL (unsigned char) 0x60
#define SUBL (unsigned char) 0x61
#define ANDL (unsigned char) 0x62
#define XORL (unsigned char) 0x63
#define MULL (unsigned char) 0x64
#define CMPL (unsigned char) 0x65
#define JMP (unsigned char) 0x70
#define JLE (unsigned char) 0x71
#define JL (unsigned char) 0x72
#define JE (unsigned char) 0x73
#define JNE (unsigned char) 0x74
#define JGE (unsigned char) 0x75
#define JG (unsigned char) 0x76
#define CALL (unsigned char) 0x80
#define RET (unsigned char) 0x90
#define PUSHL (unsigned char) 0xA0
#define POPL (unsigned char) 0xB0
#define READB (unsigned char) 0xC0
#define READL (unsigned char) 0xC1
#define WRITEB (unsigned char) 0xD0
#define WRITEL (unsigned char) 0xD1
#define MOVSBL (unsigned char) 0xE0

void nop();

void rrmovl();

void irmovl();

void rmmovl();

void mrmovl();

void addl();

void subl();

void andl();

void xorl();

void mull();

void cmpl();

void jmp();

void jle();

void jl();

void je();

void jne();

void jge();

void jg();

void call();

void ret();

void pushl();

void push(int);

void popl();

void pop(int);

void readb();

void readl();

void writel();

void writeb();

#endif