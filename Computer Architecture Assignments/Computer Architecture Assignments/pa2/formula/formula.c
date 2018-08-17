#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "formula.h"
#include <ctype.h>
#include "nCr.h"
#include <sys/time.h>

int main (int argc, char * argv[]){

	struct	timeval start, end;
	gettimeofday(&start,NULL);
	int exponent;

	if (argc < 2){
		fprintf(stderr, "Too few arguments. Exiting now.\n\n");
		return 1;
	}

	if (argc > 2){
		fprintf(stderr, "Too many arguments. Exiting now.\n\n");
		return 1;
	}

	int traverse =1; // used for loop tranversal
	char* input = argv[1];

	if (argv[1][0] == '-' && strlen(argv[1]) > 1){
		if(strcmp(input, "-h") == 0){
			printf("Outputs (1 + x)^n as an expanded polynomial, where n is input by the user.\nFormat for input: ./formula <integer>\nNegative values will be ignored.\nWARNING: Integers over 12 cause overlow, and subsequently the coefficients will be returned as 0!\n\n");	
			return 1;
		}
		// traverses through looking for non numerical digits in the negative input
		while(traverse < strlen(argv[1])){	
			if (isdigit(argv[1][traverse]) == 0){
			printf("The number entered contains non-numerical characters in its digits.  Exiting now.\n\n");
			return 0;
			}
			traverse++;
		}
		traverse = 1;
	}

	int j =1; // used for loop traversal
	// traverses through looking for non numerical digits in the positive input
	while(j< strlen(argv[1])){
		if (isdigit(argv[1][j]) == 0){
			printf("The number entered contains non-numerical characters in its digits.  Exiting now.\n\n");
			return 1;
		}
		j++;
	}

	if (argv[1][0] == '-'){
		exponent = atoi(argv[1] + 1);
			printf("(1 + x)^-%d = ", exponent);
			printf("1 / ( ");
	}

	else{ 
		 	exponent = atoi(argv[1]);
			printf("(1 + x)^%d = ", exponent);
	}

	int		rem = 1;
	int		coeff = 0;
	/*Any number y ^ 0 = 1, so (1 + x)^n must include 1 even when n = 0*/
	printf("1");

	while(rem<= exponent){
		coeff = nCr(exponent, rem);
		if (coeff == 0){  
			printf("\n\nOverflow was detected.\n"); 
		}
		printf(" + %d*x^%d", coeff, rem);
		rem++;	
	}

	gettimeofday(&end, NULL);
	 printf("\nCalculation took %ld microseconds. \n", ((end.tv_sec * 1000000 + end.tv_usec)- (start.tv_sec * 1000000 + start.tv_usec)));

	return 1;

}
/*
int nCr(int n, int r){
    return factorial(n) / (factorial(r) * factorial(n - r));
}
 
// Returns factorial of n
int factorial(int input){
    int f = 1;
    int i =1;
    if (input == 0){
        return(f);
    }
    else{
        while(i <= input){
            f = f * i;
            i++;
		}
    }
    return(f);
}*/
