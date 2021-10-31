# Ultron-Computer-System-Sim

A simulation of computer system, called Ultron, for CSCI 247 at Western Washington Univeristy in 2021.

Ultron computer has: a memory size of 32 integers, which is reprensted as an array; 2 registers, acummulator (AC) and program counter (PC).
Each instruction and value is store in memory. AC stores the latest value in calculation, and PC tells where the current instruction is at in the memory.

Ultron could only do simple instructions like read from user input, write out results, and add and subtract. 

Instruction in Ultron language is the form of 4-digit number. The first 2 digits tell what instruction Ultron should do, the last 2 digits tell Ultron where to put the value into the memory. For example, 1009 tells Ultron to read user's input and store it at location 09 in the memory.

More details about instructions are included in ultron.h.

When running the program, Ultron can only do either takes instruction from keyboard or by reading from a file.
To read from keyboard: ./a.out -i [numbers of instructions]
To read from file: ./a.out -f [filename]; in this case, a provided file is called count.u, which is a program counting from 1 to the number of user input.
