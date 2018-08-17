Numerical Base Conversion Calculator

The hardest part of this method was printing out the results of the two's complement operations in the different requested formats.  Printing out as a binary bit string was simple enough, but printing out into decimal involved multiple steps from bitstring to integer to strings one character long.  Octal
representation was also difficult since 3 bits do not divide evenly into 64 bits.  The final bit of the octal representation was considered to be a 001 or 000.

All of the strings have 64 elements, and the number of inputs is constant.  As such, since I loop through each string based on its
size, the time it takes to traverse is constant.  However, the only times when the number of loops is variable are when I am
taking an input (as the number o loops depends on the number of alphanumeric characters are input) and when outputting a decimal.  Thus, the program runs in linear time (O(n), in which n is the size of my decimal input and/or output).



Format Interpretation

This part of the project was a lot easier to implement than the previous one. The union was especially important in this part of the project as it allowed me to return either a correct float or int answer in the same way.  Professor Russell also provided us with a lot of the necessary knowledge on how to access the sign bit, exponent, as well as the mantissa part of the unsigned bitstring. The most difficult part of tis program was identifying NaN, pinf, and ninf, and that the compiler preserves the rightmost bit's sign when shifting right (arithmetic). The program runs in linear time because it loops each additional number in the inputted argv[1].
The following test cases were used to check if format was running correctly. 

Test Cases


./format 01111111100000000000000000000001 float
NaN

./format 01111111100000000000000000000000 float
pinf

./format 11111111100000000000000000000000 float
ninf

./format 11111101011111111111111000000000 float
-2.126700E+37  

./format 10011111001111111111111100000000 float
-4.065675E-20 

./format 10011111001111111111111000000000 double
The requested output format is not supported.