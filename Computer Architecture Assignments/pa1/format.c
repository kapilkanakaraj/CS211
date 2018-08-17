#include <stdio.h>
#include <string.h>
#include <stdlib.h>

union type{
    int i;
    float f;
};

int binaryFormatCheck(char* pointer) {
        if (strlen(pointer) != 32){
                 return 0;
        }//First error check to see if bit string is longer or shorter than 64 bits
        while (*pointer != '\0') {
                if (*pointer != '0' && *pointer != '1'){
                  return 2;
                }
              pointer++;
        }//Second error check to see if any bits have a value other than 0 or 1 (not binary)
        return 1;
}

int main(int argc, char **argv){

        union type format;
        int  sign = format.i >> 31;
        unsigned int exponent = format.i >> 23 & 0x000000ff;
        unsigned int fractionalPart = format.i & 0x007fffff;

        if (exponent == 255 && fractionalPart != 0){
            printf("NaN\n");
        }

        else if (sign == 0 && exponent == 255 && fractionalPart == 0){
            printf("pinf\n");
        }

        else if (sign == -1 && exponent == 255 && fractionalPart == 0){
            printf("ninf\n");
        }

       if(argc<3){
                fprintf(stderr, "Error: Not enough arguments.");
                return 0;
        }
        if(argc>3){
                printf("%d",argc);
                fprintf(stderr, "Error: Too many arguments.");
                return 0;
        }
        switch (binaryFormatCheck(argv[1])){
                case (0):{
                     fprintf(stderr, "Error: The input bit string is not 32 bits.\n");
                     return 0;
                     break;
                    
                }
                case (2): {
                     fprintf(stderr, "Error: The input bit string contains digits other than 0 and 1.\n");
                     return 0;
                     break;
                }
                default:
                     break;
        }

        int result = 0;
        int count =0;

        while(argv[1][count]!='\0'){

            switch(argv[1][count]){
                case '0':
                    result = result<<1;
                break;

                case '1':
                    result = result<<1;
                    result++;
                break;

                default:
                    printf(stderr, "Failure: There is a value other than 0 or 1 in the binary.");
            }
                count++;
        }

        format.i = result;

        if(strcmp(argv[2],"int")==0){
            printf("%d\n", format.i);
            return 1;
        }

        if(strcmp(argv[2],"float")==0){
            fprintf("%E\n", format.f);
            return 1;
        }
        
        if(strcmp(argv[2],"float")!=0 && strcmp(argv[2],"int")!=0){
            fprintf(stderr, "Error: The requested output format is not supported.");
            return 1;
        }
}