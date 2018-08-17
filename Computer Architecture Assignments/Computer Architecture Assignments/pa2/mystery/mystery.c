#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


/*Iterator will never go beyond this point, left some extra space in the array*/
int numberArray[250];

int add(int int1, int int2){
	return int1 + int2;
}

int formula(int inputNumber){
	if (numberArray[inputNumber] == -1){ //start state of the num array from main
		if (inputNumber == 0){  //if at fibonacci(0)
			numberArray[inputNumber] = 0; //first value is 0
		}
		else if (inputNumber == 1){  //if at fibonacci(1)
			numberArray[inputNumber] = 1; //second value is 1
		}		/*Efficiency is improved by storing old values in an array*/
		else{	
			numberArray[inputNumber] = add(formula(inputNumber - 2), formula(inputNumber - 1)); 
		}
	}
	return numberArray[inputNumber];	//adds all fibonacci numbers in sequence until it reaches the input

}

int main(int argc, char * argv[]){

	int inputNumber = atoi(argv[1]);
	int count = 0; 	//iterator through loop

	while (count< 250) { 
		numberArray[count] = -1; 
		count++;
	}
	printf("Value:\t%d\n", formula(inputNumber));	
	return 0;
}
