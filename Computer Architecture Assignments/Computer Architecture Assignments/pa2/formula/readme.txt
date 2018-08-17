Writing x86 Assembly Code

formula.c and nCr.s

The difficulty in this project was learning how to understand and write assembly.  However, once I learned to recognize how the registers worked in memory, understanding the arithmetic operations between moving the data became much easier.  I also attempted to implement detection of overflow, a calculation for the time it takes for the program to calculate the expression, and support for negative inputs.

The written solution for factorial is iterative. nCr just consists of repeatedly taking factorials and multiplying or dividing the results. Thankfully n! does not run in factorial time. Given that the loops run based on the size of n, the program runs in linear time, or O(n).


