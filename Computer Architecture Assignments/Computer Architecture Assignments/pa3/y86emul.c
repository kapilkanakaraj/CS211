#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "y86emul.h"

int main(int argc, char **argv){
    if (argc<2){
		fprintf(stderr, "Too few arguments.");
	}
	if (argc>2){
		fprintf(stderr, "Too many arguments.");
	}
	
	if (argv[1][0]=='-' && argv[1][1]=='h'){
			fprintf(stderr, "This program executes Y86 code stored .y86 files.  Please execute the program again and provide a inputfile of the program you want to execute.\nFORMAT: ./y86emul prog1.y86\n");
			return -1;
	}

	return createcopyinmemory(argv[1]);
}

int createcopyinmemory (char * inputfile){
	FILE *			file;
	computer *		cpu;
	int				size;
	int				iterator;	//used as an iterator
	char *			datatype; // .text or .long or .byte or .string
	unsigned char	character;
	unsigned int	address; //all addresses are positive
	char *			arg; //used for .text and .string
	int				longarg; //used for .byte and .long
	Byte *			program;
	
	file = fopen(inputfile, "r");

	cpu = malloc(sizeof(computer));

	iterator = 0;

	if (file){ // checks for success
		while (!feof(file)){
			datatype = malloc(sizeof(char)*10);
			fscanf(file, "%s", datatype);

			if (strcmp(datatype, ".size") == 0){
				fscanf(file, "%x", &size);
				program = malloc(sizeof(Byte) * (size + 1));
			    memset(program, '0', sizeof(Byte) * (size + 1));	
				cpu->counter = 0; //has not been assigned yet
				resetCPU(cpu);		
			}	

			else if (strcmp(datatype, ".byte") == 0 || strcmp(datatype, ".long") == 0 || strcmp(datatype, ".string") == 0 || strcmp (datatype, ".text") == 0){

				fscanf(file, "%x", &address);
			
				if (strcmp(datatype, ".byte") == 0){
					/*byte chars can be thought of as longs*/
					fscanf(file, "%x", &longarg);
					program[address].c = (char)(longarg);
				}
				

				else if (strcmp(datatype, ".text") == 0){
					cpu->counter = address;
					arg = (char *) malloc(1000);
					fscanf(file, "%s", arg);

					while(iterator <= strlen(arg) - 2){	
						program[address + (iterator/2)].part.regA = hexvalue(arg[iterator]);
						program[address + (iterator/2)].part.regB = hexvalue(arg[iterator + 1]);
						iterator+=2;
					}
					
					iterator = 0;
					free(arg);
				}
				
				else if (strcmp(datatype, ".long") == 0){
					fscanf(file, "%d", &longarg);
					//uses union to address memory individually and allows abilty to overwrite 4 bytes at a time
					//int1 * talks about address pointed to casts data like an int, and stores at the pointer + address as an offset
					*(int *)(program + address) = longarg;
				}
				

				else if (strcmp(datatype, ".string") == 0){
					getc(file); //moves past tab
					getc(file); //moves past int1 quote
					iterator = 1;

					while ((character = getc(file)) != '"'){
						*(unsigned char *)(program + address + iterator - 1) = (unsigned char)character;
						iterator++;
					}

					
					iterator = 0;
				}

				else{
					printf(INS);
				}
			
				free(datatype);
			}
		}
	}

	 else { 
	 	printf("File doesn't exist.\n"); // File does not read
	 	return 0;
	 }

	fclose(file);

	return readCases(program, cpu);
}



int readCases(Byte * program, computer * cpu){
	int 			int1, int2;
	int 			address;
	char 			character;
	int 			integer;
	int32_t 		castint;
	int 			hasNext;

	hasNext = 1;	

	do{
		switch (program[cpu->counter].c){
			/*nop*/
			case 0x00:

				cpu->counter++;
				break;
			
			/*halt*/
			case 0x10:

				printf(AOK);
				printf(HLT);
				hasNext = 0;
				return 0;
				break;

			/*rrmovl*/
			case 0x20:

				getRegisters(program[cpu->counter + 1], &int1, &int2);
				cpu->reg[int2] = cpu->reg[int1];
			       	cpu->counter += 2;	
				break;

			/*irmovl*/
			case 0x30:

				getRegisters(program[cpu->counter + 1], &int1, &int2);
				cpu->reg[int2] = getlong(program, cpu, 2);
				cpu->counter += 6;
				break;

			/*rmmovl*/
			case 0x40:

				getRegisters(program[cpu->counter + 1], &int1, &int2);
				address = getlong(program, cpu, 2); //offset
				writetomemory(program, cpu, address, int2, cpu->reg[int1]);
				cpu->counter += 6;	
				break;	
			
			/*mrmovl*/
			case 0x50:
				
				getRegisters(program[cpu->counter + 1], &int1, &int2);
				address = getlong(program, cpu, 2); //offset
				cpu->reg[int1] = copyfrommemory(program, cpu, address, int2);
				cpu->counter += 6;
				break;

			/*addl*/
			case 0x60:

				getRegisters(program[cpu->counter + 1], &int1, &int2);
				integer = cpu->reg[int1] + cpu->reg[int2];
				setflags(cpu, '+', cpu->reg[int1], cpu->reg[int2], integer);
				cpu->reg[int2] = integer;
				cpu->counter += 2;		
				break;

			/*subl*/
			case 0x61:

				getRegisters(program[cpu->counter + 1], &int1, &int2);
				integer = cpu->reg[int2] - cpu->reg[int1];
				setflags(cpu, '-', cpu->reg[int2], cpu->reg[int1], integer);
				cpu->reg[int2] = integer;
				cpu->counter += 2;		
				break;

			/*andl*/
			case 0x62:

				getRegisters(program[cpu->counter + 1], &int1, &int2);
				integer = cpu->reg[int1] & cpu->reg[int2]; //bitwise AND
				setflags(cpu, '&', cpu->reg[int1], cpu->reg[int2], integer);
				cpu->reg[int2] = integer;
				cpu->counter += 2;	
				break;

			/*xorl*/
			case 0x63:

				getRegisters(program[cpu->counter + 1], &int1, &int2);
				integer = cpu->reg[int1] ^ cpu->reg[int2]; //bitwise OR
				setflags(cpu, '^', cpu->reg[int1], cpu->reg[int2], integer);
				cpu->reg[int2] = integer;
				cpu->counter += 2;	
				break;

			/*mull*/
			case 0x64:
			
				getRegisters(program[cpu->counter + 1], &int1, &int2);
				integer = cpu->reg[int1] * cpu->reg[int2];
				setflags(cpu, '*', cpu->reg[int1], cpu->reg[int2], integer);
				cpu->reg[int2] = integer;
				cpu->counter += 2;	
				break;

			/*cmpl*/
			case 0x65:

				getRegisters(program[cpu->counter + 1], &int1, &int2);
				integer = cpu->reg[int2] - cpu->reg[int1];
				setflags(cpu, '-', cpu->reg[int2], cpu->reg[int1], integer);
				cpu->counter += 2;
				break;
			
			/*jmp*/
			case 0x70:

				address = getlong(program, cpu, 1);
				cpu->counter = address;
				break;

			/*jle*/
			case 0x71:

				address = getlong(program, cpu, 1);
				/* (sf ^ of ) || zf*/
				if ( (cpu->SF == 1 && cpu->OF == 0) || (cpu->SF == 0 && cpu->OF == 1) || (cpu->ZF == 1) )
					cpu->counter = address;
				else
					cpu->counter += 5;
				break;

			/*jl*/
			case 0x72:

				address = getlong(program, cpu, 1);
				/* sf ^ ~of*/
				if ( (cpu->SF == 1 && cpu->OF == 0) || (cpu->SF == 0 && cpu->OF == 1) )
					cpu->counter = address;
				else
					cpu->counter += 5;
				break;

			/*je*/
			case 0x73:

				address = getlong(program, cpu, 1);
				/* zf*/
				if (cpu->ZF == 1)
					cpu->counter = address;
				else
					cpu->counter += 5;
				break;

			/*jne*/
			case 0x74:

				address = getlong(program, cpu, 1);
				/* ~zf*/
				if (cpu->ZF == 0)
					cpu->counter = address;
				else
					cpu->counter += 5;
				break;
							
			/*jge*/
			case 0x75:

				address = getlong(program, cpu, 1);
				/* ~(sf ^ of)*/
				if ( !( (cpu->SF == 1 && cpu->OF == 0) || (cpu->SF == 0 && cpu->OF == 1) ) )
					cpu->counter = address;
				else
					cpu->counter += 5;
				break;

			/*jg*/
			case 0x76:
				
				address = getlong(program, cpu, 1);
				/* ~(sf ^ of) && ~zf*/
				if ( !( (cpu->SF == 1 && cpu->OF == 0) || (cpu->SF == 0 && cpu->OF == 1) ) &&
						cpu->ZF == 0)
					cpu->counter = address;
				else
					cpu->counter += 5;
				break;

			/*call*/
			case 0x80:

				address = getlong(program, cpu, 1);
				cpu->reg[esp] -= 4;
				integer = cpu->counter + 5; //store current address for ret
				writetomemory(program, cpu, 0, esp, integer);
				cpu->counter = address;
				break;

			/*ret*/
			case 0x90:

				cpu->counter = copyfrommemory(program, cpu, 0, esp);
				cpu->reg[esp] += 4;
				break;

			/*pushl*/
			case 0xa0:

				getRegisters(program[cpu->counter + 1], &int1, &int2);
				cpu->reg[esp] -= 4;
				writetomemory(program, cpu, 0, esp, cpu->reg[int1]);
				cpu->counter += 2;
				break;

			/*popl*/
			case 0xb0:

				getRegisters(program[cpu->counter + 1], &int1, &int2);
				cpu->reg[int1] = copyfrommemory(program, cpu, 0, esp);
				cpu->reg[esp] += 4;
				cpu->counter += 2;
				break;

			/*readb*/
			case 0xc0:

				getRegisters(program[cpu->counter + 1], &int1, &int2);
				address = getlong(program, cpu, 2);

				flagreset(cpu);

				if (EOF == scanf("%c", &character))
					cpu->ZF = 1;
				else
					cpu->ZF = 0;
				
				program[cpu->reg[int1] + address].c = character;
				cpu->counter += 6;
				break;

			/*readl*/
			case 0xc1:

				getRegisters(program[cpu->counter + 1], &int1, &int2);
				address = getlong(program, cpu, 2);

				flagreset(cpu);

				if (EOF == scanf("%i", &integer) )
					cpu->ZF = 1;
				else
					cpu->ZF = 0;
				
				writetomemory(program, cpu, 0, int1, integer);
				cpu->counter += 6;
				break;

			/*writeb*/
			case 0xd0:
				
				getRegisters(program[cpu->counter + 1], &int1, &int2);
				address = getlong(program, cpu, 2);
				printf("%c", program[cpu->reg[int1] + address].c);
				cpu->counter += 6;
				break;

			/*writel*/
			case 0xd1:

				getRegisters(program[cpu->counter + 1], &int1, &int2);
				address = getlong(program, cpu, 2);
				integer = (int)copyfrommemory(program, cpu, address, int1);
				printf("%i", integer);
				cpu->counter += 6;
				break;

			/*movsbl*/
			case 0xe0:

				getRegisters(program[cpu->counter + 1], &int1, &int2);
				address = getlong(program, cpu, 2);
				character = program[cpu->reg[int2] + address].c;
				castint = (int32_t) character;
				cpu->reg[int1] = castint;
				cpu->counter += 6;
				break;

			default:
				printf(INS);
				return 0;
				break;
		}

	} while (hasNext = 1);


	free(program);
	free(cpu);
	return 0;
}


void flagreset(computer * cpu){
	// Resets all flags to 0
	cpu->ZF = 0;
	cpu->OF = 0;
	cpu->SF = 0;
}


void setflags(computer * cpu, char operation, int left, int right, int result){
	
	flagreset(cpu);

	switch (operation){
		case '+':
			if ( (left > 0 && right > 0 && result < 0) || (left < 0 && right < 0 && result > 0) )
				cpu->OF = 1; // Returns 0 flag
				// Given to us by Professor Russell
			break;
		case '-':
			//more complicated cases for left - right
			if ( (left > 0 && right < 0 && result < 0) || (left < 0 && right > 0 && result > 0) )
				cpu->OF = 1; // Returns  0 flag
				// Given to us by Professor Russell
			break;

		case '*':

			if ( (left > 0 && right < 0 && result > 0) || (left < 0 && right > 0 && result > 0) || (left < 0 && right < 0 && result < 0) || (left > 0 && right > 0 && result > 0) )
				cpu->OF = 1; // Returns 0 flag
				// Given to us by Professor Russell
			break;

		//nothing to be done for overflow flags
		case '&':
		case '^':
			break;

		default:
			printf("Unregonized operation.\n");
			flagreset(cpu);
	}
	
	if (result == 0)
		cpu->ZF = 1; // Throws 0 flag if result  is 0

	if (result < 0)
		cpu->SF = 1; // Throws sign flag if result is negative
}


/*ASSUMPTION: cpu->size has a value*/
void resetCPU(computer * cpu){
	int	count = 1;

	flagreset(cpu);

	while(count<=8){
		cpu->reg[count] = 0;
		count++;
	}
	
}


int hexvalue(char hex){
	/*CASE: numbers*/
	if (hex > 0x2F && hex < 0x3A) // covers all numbers
		return hex - '0';
	/*CASE: a - f*/
	else if (hex > 0x60 && hex < 0x67) // covers all lowercase letters
		return 0x0a + (hex - 'a');
	/*CASE: A - F*/
	else if (hex > 0x40 && hex < 0x47) // covers all uppercase letters
		return 0x0a + (hex - 'A');

	printf(ADR); // prints "Invalid address.""
	return 0;
}


void getRegisters(Byte registers, int * register1, int * register2){
	*register1 = registers.part.regA;
	*register2 = registers.part.regB;
}

int getlong(Byte * program, computer * cpu, int offset){
	return 	(int)( program[cpu->counter + offset].c + (program[cpu->counter + offset + 1].c << 8) + (program[cpu->counter + offset + 2].c << 16) + (program[cpu->counter + offset + 3].c << 24) );
	// Each additional byte causes an additional left shift by 8 bits
} 

int copyfrommemory(Byte * program, computer * cpu, int offset, int reg){
	return (int)( (program[cpu->reg[reg] + offset].c) + (program[cpu->reg[reg] + offset + 1].c << 8) + (program[cpu->reg[reg] + offset + 2].c << 16) + (program[cpu->reg[reg] + offset + 3].c << 24) );
	// Each additional byte causes an additional left shift by 8 bits
}

void writetomemory(Byte * program, computer * cpu, int offset, int reg, int value){
	program[cpu->reg[reg] + offset].c = (value & 0x000000ff); // 255
	program[cpu->reg[reg] + offset + 1].c = (value & 0x0000ff00) >> 8; // 65280
	program[cpu->reg[reg] + offset + 2].c = (value & 0x00ff0000) >> 16; // 16711680
	program[cpu->reg[reg] + offset + 3].c = (value & 0xff000000) >> 24; // 4278190080
}


char* numbers(unsigned int registerValue){

	switch (registerValue){
		case 0:
			return "%eax";
			break;
		case 1:
			return "%ecx";
			break;
		case 2:
			return "%edx";
			break;
		case 3:
			return "%ebx";
			break;
		case 4:
			return "%esp";
			break;
		case 5:
			return "%ebp";
			break;
		case 6:
			return "%esi";
			break;
		case 7:
			return "%edi";
			break;
		default:
			return "unknown register";
			break;
	}

	return "unknown register";
}
