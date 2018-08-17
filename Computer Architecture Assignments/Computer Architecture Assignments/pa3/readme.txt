Y86 Emulator

This project details a massive checklist around running a fetch, decode, and execute cycle. It was by far the most difficult of all the assigned projects as it required us to combine almost all the topics covered in the class. Luckly, Professor Russell's instructions about the flag usages were very thorough.  I used two main functions where the first would store the input file's directives and the second to execute the instructions as specified in the directive.

The most difficult part of the first half came when storing input that was of multiple bytes. The only time the program's runtime grows with size is with the length of the largest input string.

The challenges with the second half really came down to organization. I used a switch statement within a
do while loop which would exit if a halt instruction was encountered. Other than that, most of the loop's operations were facilitated by C, espsecially in the case of movsbl#.

This project was especially difficult because syntax errors caused major errors in the stack. The code for the diassembler was very similar to the emulator, so once the emulator was completed, the disassembler was not too difficult, especially as almost all of the methods are shared between both functions. 

Everything in the execution loop runs in O(1) time.  The fetching in the loading functions runs in time
dependent the number of directives given the input and the length of the largest string, or O(ns).
