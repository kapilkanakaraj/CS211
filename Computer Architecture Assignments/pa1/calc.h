#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int reverseBitString(char* string);
char * createEmptyBitstring(int size);

/*Functions for turning input into two's complement binary*/
int binaryASCIIToTwoComplement(char* s, long* output);
int octalASCIIToTwoComplement(char* s, long* output);
int decimalASCIIToTwoComplement(char* s, long* output);
int hexASCIIToTwoComplement(char* s, long* output);

/*Output functions*/
int TwoComplementToBinaryASCII(long value, char* s);
int TwoComplementToDecimalASCII(long value, char* s);
int TwoComplementToHexASCII(long value, char* s);
int TwoComplementToOctalASCII(long value, char* s);

char * addition(char * first, char * second, int size);
char * subtraction(char * first, char * second, int size);



#endif