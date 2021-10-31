/*Explanation of ifndef
#ifndef: conditional statement, checking if the following token (ULTRON_H) is already defined; If not defined, it will excecute the code
between itself and the #endif statement. If defined, then it will skip the whole thing and jump right to #endif

in this case, #ifndef checks if ULTRON_H has been defined to avoid duplicate declaration.
*/
#ifndef ULTRON_H
#define ULTRON_H

//MACROS (ex: ULTRON_MEMORY_SIZE, READ, LOAD, etc.) it's like static variable in java
// Ultron computers have only 32 words worth of memory
#define ULTRON_MEMORY_SIZE 32

// Abstract type that defines an Ultron computer
//typedef struct: similar to how constructor works in java
typedef struct{
    int memory [ULTRON_MEMORY_SIZE];
    int pc;//program counter: index of memory to store instruction
    int ac;//hold the value currently in calculation
} Ultron;


// Ultron methods
//method are defined in header file, BUT the codes for it is in the implementation file (ultron.c)
void ultron_init(Ultron* ultron);
void ultron_dump(Ultron* ultron);
int ultron_memory(Ultron* ultron, int location);
int ultron_accumulator(Ultron* ultron);
int ultron_pc(Ultron* ultron);
void ultron_load(Ultron* ultron, int size, int* instructions);
int ultron_run(Ultron* ultron);

// Ultron instructions
//MACROS definition
#define READ         10         // read a word from input into memory
#define WRITE        11         // write a word from memory to the screen

#define LOAD         20         // load a word from memory into accumulator
#define STORE        21         // store a word from accumulator into memory

#define ADD          30         // add to accumulator the value from memory
#define SUBTRACT     31         // subtract from accum the value in memory

#define BRANCHNEG    40         // branch if accumulator is negative to location
#define HALT         43         // stop executing

#endif // ULTRON_H
