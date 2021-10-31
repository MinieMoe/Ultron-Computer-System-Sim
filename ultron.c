//implemetation file
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ultron.h"


/*Initilaztion for Ultron object
    set pc and ac to 0
    reset all values in memory[] to 0
*/
void ultron_init(Ultron* ultron) {
    /*These lines won't work:
    Ultron computer;
    ultron = &computer;//make pointer point to computer
    */
    ultron->ac = 0;//memory index for the current variable in calculation
    ultron->pc = 0;//memory index for the current instruction
    ultron->memory[ULTRON_MEMORY_SIZE];

    /*Reset array value to zero vs Initialize array values to zero
    computer.memory = {0};//initialize to zero
        this line will give an error saying that it's not modifable bc
        memory[] is already initialized
    HOW TO FILL A BLOCK OF MEMORY WITH A SPECIFIC VALUE
        memset(*pointer, int value, size numOfBytes)
    pointer - starting address of memory to be filled
    numOfBytes - number of bytes to be filled starting from pointer
    */
    //reseting values in memory to 0
    memset((*ultron).memory,0,ULTRON_MEMORY_SIZE*sizeof(int));//there are 32 integers, so the number of bytes = byte size of 1 int * 32
}

/*Dumping memory - print out the contents of memory
    PC: memory index  of the current/latest instruction
    AC: current value in calculation
    memory index (0-32)        value at that index
*/
void ultron_dump(Ultron* ultron) {
    printf("PC: %d\n", (*ultron).pc);
    printf("AC: %d\n", (*ultron).ac);
    //printing memory index and its value
    for(int i = 0; i < ULTRON_MEMORY_SIZE; i++){
        printf(" %d %d\n", i, (*ultron).memory[i]);
    }
}

/*Return memory value at given location

*/
int ultron_memory(Ultron* ultron, int location) {
    return (*ultron).memory[location];
}

/*Return the current value in accumulator
*/
int ultron_accumulator(Ultron* ultron) {
    return (*ultron).ac;
}

/*Return the value of program counter (index or instruction?)

*/
int ultron_pc(Ultron* ultron) {
    return (*ultron).pc;
}

/*Loading a program into ultron's memory
    Copy the size number of instructions from the array of integer instructions into Ultron's memory,
    starting at memory location 0.

    int* instructions is pointer to the array of integer instruction?
        to access the value in the array: *(instruction + i)
        with with instruction probably starts as 0 and increament by 1 till reaches the end of instructions array
*/
void ultron_load(Ultron* ultron, int size, int* instructions) {
    for (int i = 0; i < size; i++){
        (*ultron).memory[i] = *(instructions + i);
    }
}

/*Run the program till it's halted or encounter an error
    use while loop to check when user asks to halt the program
        inside while loop:
            a lot of if-else statements to check which error is met
            if no error:
                bunch of code to run the program
What does the program do when running?
    fetch the next instruction from memory: instruction = memory[pc]
        decode from the instruction (4 digits): first 2 digits - shows what operation to call (READ - 10; WRITE - 11, etc.)
                                                last 2 digits - operand, or memory location to put variable into
    once we know what instruction to call, use switch case to get the chosen operation
*/
int ultron_run(Ultron* ultron) {
    while((*ultron).memory[(*ultron).pc]/100 != HALT){
        //pc counter move out of range --> stop the program
        if((*ultron).pc > ULTRON_MEMORY_SIZE){
            return -3;
            break;
        }
        //break down instruction
        int instruction = (*ultron).memory[(*ultron).pc];//get the latest instruction
        int operation = instruction / 100;//first 2 digits
        int operand = instruction % 100;//last 2 digits

        //check for error before calling operations using switch case
        //location user wants to get is outside of range --> stop the program
        if(operand > ULTRON_MEMORY_SIZE){
            return -2;
            break;
        }
        switch (operation)
        {
        case READ:
            printf("?");
            scanf("%d", &(*ultron).memory[operand]);
            break;
        case WRITE:
            printf("= %d\n", (*ultron).memory[operand]);
            break;
        case LOAD:
            (*ultron).ac = (*ultron).memory[operand];
            break;
        case STORE:
            (*ultron).memory[operand] = (*ultron).ac;
            break;
        case ADD:
            (*ultron).ac += (*ultron).memory[operand];
            break;
        case SUBTRACT:
            (*ultron).ac -= (*ultron).memory[operand];
            break;
        case BRANCHNEG://move pc counter to new location if ac is negative
            if((*ultron).ac < 0){
                (*ultron).pc = operand;
                (*ultron).pc--;//the counter stays the same for BRANCHNEG, but pc is coded to always increment, so have to set this one back
            }
            break;
        case HALT:
            return 0;
            break;
        default://if not matching any of the operation above, break
            return -1;
            break;
        }

        //after working on the current instruction, move to the next one
        (*ultron).pc++;
        
    }
    
}
