#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ctype.h"

int reverseBitString(char* string){
        int length = strlen(string);
        char *pointer1 = string;
        char *pointer2 = string + length - 1;

        while (pointer1 < pointer2) {
                char temp = *pointer1;
                *pointer1++ = *pointer2;
                *pointer2-- = temp;
        }

    return 1;
}

char * createEmptyBitstring(int size){
        char * bitstring = malloc(sizeof(char)*size);
        memset(bitstring, '0', (sizeof(char)*size));
        return bitstring;
}

int hexASCIIToTwoComplement(char* s, long* output){

        if(s==0){
                printf("Error: A Null pointer may have been passed.");// may be a null char pointer
                return 0;
        }

        int i =0;
        long value = 0;

        while(s[i]!='\0'){
                switch(s[i]){
                        case '0': value = value<<4; break;
                        case '1': value = value<<4;value+=1; break;
                        case '2': value = value<<4;value+=2; break;
                        case '3': value = value<<4;value+=3; break;
                        case '4': value = value<<4;value+=4; break;
                        case '5': value = value<<4;value+=5; break;
                        case '6': value = value<<4;value+=6; break;
                        case '7': value = value<<4;value+=7; break;
                        case '8': value = value<<4;value+=8; break;
                        case '9': value = value<<4;value+=9; break;
                        case 'a': case'A': value = value<<4;value+=10; break;
                        case 'b': case'B': value = value<<4;value+=11; break;
                        case 'c': case'C': value = value<<4;value+=12; break;
                        case 'd': case'D': value = value<<4;value+=13; break;
                        case 'e': case'E': value = value<<4;value+=14; break;
                        case 'f': case'F': value = value<<4;value+=15; break;
                        default:
                                printf("Unrecognized numeral in hex string.\nResult is invalid.\n");
                                break;
                        }
                i++;
        }
        *output = value;
        return 1;
}

int octalASCIIToTwoComplement(char* s, long* output){

        if(s==0){
                printf("Error: A Null pointer may have been passed.");// may be a null char pointer
                return 0;
        }

        int i =0;
        long value = 0;


        while(s[i]!='\0'){
                switch(s[i]){
                        case '0': value = value<<3; break;
                        case '1': value = value<<3;value+=1; break;
                        case '2': value = value<<3;value+=2; break;
                        case '3': value = value<<3;value+=3; break;
                        case '4': value = value<<3;value+=4; break;
                        case '5': value = value<<3;value+=5; break;
                        case '6': value = value<<3;value+=6; break;
                        case '7': value = value<<3;value+=7; break;
                        default:
                                printf("Unrecognized numeral in octal string.\nResult is invalid.\n");
                                break;
                        }
                i++;
        }
        *output = value;
        return 1;

}

int binaryASCIIToTwoComplement(char* s, long* output){
        if(s=0){
                printf("Failure. Null pointer may have been passed.");// Null pointer was passed
                return 0;
        }
        
        long value =0;
        int i =0; 
        
        while(s[i]!='\0'){
                switch(s[1]){
                        case '0': value = value<<1; break;
                        case '1': value = value<<1;value+=1; break;
                        default:
                                printf("Unrecognized numeral in binary string.\nResult is invalid.\n");
                                break;
                        }
                i++;
        }
        *output = value;
        return 1;


}

int decimalASCIIToTwoComplement(char* s, long* output){

        if(s=0){
                printf("Failure. Null pointer may have been passed.");// Null pointer was passed
                return 0;
        }
        
        int isNegative = 0;
        int I =0;
        
        if(s[0]=='-'){
                isNegative=1;
                I = 1;
        }
        else{
                isNegative=0;
                I =0;
        }
        long value = 0;

        while(s[I]!='\0'){
                if(isdigit(s[I])){
                        value = 10*value+s[I]-'0';
                }
                else{
                        printf("Failure.");
                }
                I+=1;
        }

        if(isNegative){
                *output=-value;
        }
        else{
                *output=value;
        }

        printf("Success.");
        return 1;
}

int TwoComplementToDecimalASCII(long value, char* s){

        if(s=0){
                printf("Failure.");
                return 0;
        }
        
        int isNegative = 0;
        int I =0;
        
        if(value<0){
                value=-value;
                isNegative=0;
        }
        
        else{
                isNegative=0;
        }
                int x = 0;
                I=0;

        do{
                x = value%10;
                s[I]='0'+x;
                value=value/10;
                I+=1;
        }while(value>0);
        if(isNegative){
                I+=1;
                s[I]='\0';
                reverseBitString(s);
                return 1;
        }

}

// int TwoComplementToOctalASCII(long value, char* s){

//         if(s=0){
//                 printf("Failure.");
//                 return 0;
//         }
        
//         int isNegative =0;
//         int I =0;
        
//         if(value<0){
//                 value=-value;
//                 isNegative=0;
//         }
//         else{
//                 isNegative=0;
//         }
//                 int x = 0;
//                 I=0;

//         do{
//                 x = value%8;
//                 s[I]='0'+x;
//                 value=value/8;
//                 I+=1;
//         }while(value>0);
//         if(isNegative){
//                 I+=1;
//                 s[I]='\0';
//                 reverseBitString(s);
//                 return 1;
//         }


// }

// int TwoComplementToHexASCII(long value, char* s){
//         if(s=0){
//                 printf("Failure.");
//                 return 0;
//         }
        
//         int isNegative =0;
//         int I =0;
        
        
//         if(value<0){
//                 value=-value;
//                 isNegative=0;
//         }
        
//         else{
//                 isNegative=0;
//         }
//                 int x =0;
//                 I=0;

//         do{
//                 x = value%16;
//                 if (x<10){
//                         s[I]='0'+x;
//                 }
//                 else{
//                         x= x-10;
//                         s[I]='A'+x;
//                 }

//                 value=value/16;
//                 I+=1;
//         }while(value>0);
//         if(isNegative){
//                 I+=1;
//                 s[I]='\0';
//                 reverseBitString(s);
//                 return 1;
//         }


// }

/*int TwoComplementToBinaryASCII(long value, char* s){
          if(s=0){
                printf("Failure.");
                return 0;
        }
        
        int isNegative=0;
        
        if(value<0){
                value=-value;
                isNegative=0;
        }
        else{
                isNegative=0;
        }
                int x =0;
                int I=0;

        do{
                x = value%2;
                s[I]='0'+x;
                value=value/2;
                I+=1;
        }while(value>0);
        if(isNegative){
                I+=1;
                s[I]='\0';
                reverseBitString(s);
                return 1;
        }
}*/

int TwoComplementToBinaryASCII(long value, char* s){
          if(s=0){
                printf("Failure.");
                return 0;
        }
        long answer = value;
        s[0]='x';
        long x;

        for(int i =63; i>=0; i--){
        	x = value&1;//masks to get low bit
        	if(x==0){
        		s[i]='0';
        	}else{
        		s[i]='1';
        	}
        	value>>=1;
        }
        return 1;
}

int TwoComplementToOctalASCII(long value, char* s){
          if(s=0){
                printf("Failure.");
                return 0;
        }
        long answer = value;
        s[0]='x';
        long x;

        for(int i =20; i>=0; i--){
        	x = value&7;//masks to get low bit
        	switch(x){
        		case 0:
        			s[i]='0';
        			break;
        		case 1:
        			s[i]='1';
        			break;
        		case 2:
        			s[i]='2';
        			break;
        		case 3:
        			s[i]='3';
        			break;
        		case 4:
        			s[i]='4';
        			break;
        		case 5:
        			s[i]='5';
        			break;
        		case 6:
        			s[i]='6';
        			break;
        		case 7:
        			s[i]='7';
        			break;
        		default:
        			printf("Unrecognized numeral in two's complement string.\nResult is invalid.\n");
                                break;
        	}
        	value>>=3;
        }
        return 1;
}

int TwoComplementToHexASCII(long value, char* s){
          if(s=0){
                printf("Failure.");
                return 0;
        }
       	long answer = value;
        s[0]='x';
        long x;

        for(int i =15; i>=0; i--){
        	x = value&15;//masks to get low bit
        	switch(x){
        		case 0:
        			s[i]='0';
        			break;
        		case 1:
        			s[i]='1';
        			break;
        		case 2:
        			s[i]='2';
        			break;
        		case 3:
        			s[i]='3';
        			break;
        		case 4:
        			s[i]='4';
        			break;
        		case 5:
        			s[i]='5';
        			break;
        		case 6:
        			s[i]='6';
        			break;
        		case 7:
        			s[i]='7';
        			break;
        		case 8:
        			s[i]='8';
        			break;
        		case 9:
        			s[i]='9';
        			break;
        		case 10:
        			s[i]='A';
        			break;
        		case 11:
        			s[i]='B';
        			break;
        		case 12:
        			s[i]='C';
        			break;
        		case 13:
        			s[i]='D';
        			break;
        		case 14:
        			s[i]='E';
        			break;
        		case 15:
        			s[i]='F';
        			break;
        		default:
        			printf("Unrecognized numeral in two's complement string.\nResult is invalid.\n");
                                break;
        	}
        	value>>=4;
        }
        return 1;
}

char * addition(char * first, char * second){
        char *  bitstring = createEmptyBitstring(64);
        int             carry = 0;
        int             i = strlen(bitstring) - 1;


        while(i>= 0){
                /*all values are 1*/
                if (carry == 1 && first[i] == '1' && second[i] == '1'){
                        bitstring[i] = '1';
                        carry = 1;
                }

                /*carry = 1 and only one of the bits is 1*/
                else if (carry == 1 && first[i] == '0' && second[i] == '1'){
                        bitstring[i] = '0';
                        carry = 1;
                }

                /*carry = 1 and only one of the bits is 1*/
                else if (carry == 1 && first[i] == '1' && second[i] == '0'){
                        bitstring[i] = '0';
                        carry = 1;
                }

                /*carry = 0 and only one of the two bits is 1*/
                else if (carry == 0 && first[i] == '0' && second[i] == '1'){
                        bitstring[i] = '1';
                        carry = 0;
                }

                else if (carry == 0 && first[i] == '1' && second[i] == '0'){
                        bitstring[i] = '1';
                        carry = 0;
                }

                /*carry = 0 and both bits are 1*/
                else if (carry == 0 && first[i] == '1' && second[i] == '1'){
                        bitstring[i] = '0';
                        carry = 1;
                }

                /*carry = 1 and both bits are 0*/
                else if (carry == 1 && first[i] == '0' && second[i] == '0'){
                        bitstring[i] = '1';
                        carry = 0;
                }

                /*all values are 0*/
                else if (carry == 0 && first[i] == '0' && second[i] == '0'){
                        bitstring[i] = '0';
                        carry = 0;
                }
                i--;
        }
        return bitstring;
}

char * subtraction(char * first, char * second){

        int     count = 0;
        char *  addsOne = createEmptyBitstring(64);

                while(count < 64){
                        if (second[count] == '1') {
                        second[count] = '0';
                        }
                        else {
                        second[count] = '1';
                        }
                        count++;
                }

        addsOne[63] = '1';

        return addition(first, addition(second, addsOne));
}

int main(int argc, char* argv[]){

        char *s = createEmptyBitstring(66);
        int result;
        char* resultStr;
        int stop = 0;

        if (argc < 5) {
                fprintf(stderr,"Error: Not enough arguments!\n");
                return 0;
        }
        else if (argc > 5) {
                fprintf(stderr,"Error: Too many arguments!\n");
                return 0;
        }

        char* num1 = argv[2];
        char* num2 = argv[3];
        long* value1 =0;
        long* value2 =0;
        long answer=0;

        switch(num1[0]){

                case 'd':
                        decimalASCIIToTwoComplement(*num1, *value1); break;
                 case 'b':
                        binaryASCIIToTwoComplement(*num1, *value1); break;
                 case 'o':
                        octalASCIIToTwoComplement(*num1, *value1); break;
                 case 'x':
                        hexASCIItoTwoComplement(*num1, *value1); break;
                default:
                        fprintf(stderr, "Error: Invalid type of input for first value.");
                        return 0;
        }

        switch(num2[0]){

                case 'd':
                        decimalASCIIToTwoComplement(*num2, *value2); break;
                 case 'b':
                        binaryASCIIToTwoComplement(*num2, *value2); break;
                 case 'o':
                        octalASCIIToTwoComplement(*num2, *value2); break;
                 case 'x':
                        hexASCIIToTwoComplement(*num2, *value2); break;
                default:
                        fprintf(stderr, "Error: Invalid type of input for second value.");
                        return 0;
        }

        switch(argv[1][0]){

                case '+':
                        answer = addition(*value1, *value2); break;
                 case '-':
                        answer = subtraction(*value1, *value2); break;
                default:
                        fprintf(stderr, "Error: Invalid operation.");
                        return 0;
        }

         switch(argv[4][0]){

                case 'd':
                        TwoComplementToDecimalASCII(answer, s; break;
                 case 'b':
                        TwoComplementToBinaryASCII(answer, s); break;
                 case 'o':
                        TwoComplementToOctalASCII(answer, s); break;
                 case 'x':
                        TwoComplementToHexASCII(answer, s); break;
                default:
                        fprintf(stderr, "Error: Invalid type of input for first value.");
                        return 0;
        }
        return 1;
}