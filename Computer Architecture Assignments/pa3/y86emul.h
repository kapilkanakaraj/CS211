#ifndef _Y86EMUL_H_
#define _Y86EMUL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define eax 0
#define ecx 1
#define edx 2
#define ebx 3
#define esp 4
#define ebp 5
#define esi 6
#define edi 7

#define AOK "Everything is working.\n"
#define INS "Invalid instruction.\n"
#define ADR "Invalid address.\n"
#define HLT "Halt instruction.\n"

typedef union {
	unsigned char c;

	struct {
		unsigned int regB:4;
		unsigned int regA:4;
	} part;
} Byte;

typedef struct {
	
	int reg[8];
	int counter;
	unsigned int ZF:1;
	unsigned int OF:1;
	unsigned int SF:1;

} computer;

/*Main functions that facilitate the fetch-decode-execute loop*/
int createcopyinmemory (char * inputfile);
int readCases (Byte * program, computer * cpu);

/*Helper functions*/
void resetCPU(computer * cpu); //sets all registers and programs to 0
int hexvalue(char hex);
void getRegisters(Byte registers, int * first, int * second);
int getlong(Byte * program, computer * cpu, int offset);
int copyfrommemory(Byte * program, computer * cpu, int displacement, int reg);
void writetomemory (Byte * program, computer * cpu, int offset, int reg, int value);
void flagreset(computer * cpu);
void setflags(computer * cpu, char operation, int left, int right, int result);
char * numbers(unsigned int reg);
#endif /* _Y86EMUL_H_ */
