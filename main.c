#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ultron.h"


/*Parse the command line ./ultron [- i instructions] [-f filename]
    -i instructions= is the number of instructions (customized or 32 by default)
    -f filename = is where to get the instructions from (a file or stdin)
./ultron = ** argv = argv [0]
- i instruction AND -f filename = ** argv + 1 = argv [1]
    -i and -f can NOT appear at the same time


char** argv is the same as char* argv[]
*/
int main(int argc, char* argv[]) {
    int num_instructions= 32;//by default
    int instructions [num_instructions];
    char buff_a_line[99];//buffer to read one line fron txt file

    //create the ultron computer
    Ultron computer;
    Ultron* pultron = &computer;//pointer to Ultron object

    /*TEST: reading from file
    
    FILE *file_to_read = fopen("test.txt", "r");
    int i = 0;//counter
    /*Read from the file
        feof(FILE*) checks if it reaches end of the file
            return non-zero if reach end
            else return zero
    WARNING: foef is dangerous because it reads the last line twice
    
        
    
    while(fgets(buff_a_line,7,file_to_read)){//read each line from file and put it into the buffer 
        buff_a_line[4] = '\0';
        printf("%d %s\n",i,buff_a_line);//testing
        instructions[i] = atoi(buff_a_line);
        printf("instruction: %d \n",instructions[i]);//testing
        i++;
    }
    //close the text file
    fclose(file_to_read);

    //testing
    // for(int n = 0; n < 7;n++){
    //     printf("%d\n", instructions[n]);
    // }
    
   //printf("%d\n", argc);*/

    //1. READ FROM THE PROGRAM - GOAL: retrieve instructions and put them into instruction[]
     if(argc <= 3){//can only take in 3 arguments
    
        //IF "-i" is the argument:
        if (argv[1][1] == 'i'){//this means the user wants to specify the number of instructions
            num_instructions = atoi(argv[2]);//change number of instructions

            //in this case, -f flag can't be called, so read from keyboard
            for(int i =0; i < num_instructions; i++){
                fgets(buff_a_line,99,stdin);
                buff_a_line[strlen(buff_a_line)-1] = '\0';
                instructions[i] = atoi(buff_a_line);
            }
        //IF "-f" is the argument:
        }else if (argv[1][1] == 'f'){//read from the user if file is specified
            //open the specified file
            printf("%s\n",argv[2]);
            FILE *file_to_read = fopen(argv[2], "r");
            int i = 0;//counter

            /*Read from the file
                feof(FILE*) checks if it reaches end of the file
                    return non-zero if reach end
                    else return zero
            WARNING: foef is dangerous because it reads the last line twice*/
            while(fgets(buff_a_line,99,file_to_read)){//read each line from file and put it into the buffer  
                buff_a_line[strlen(buff_a_line)-1] = '\0';
                instructions[i] = atoi(buff_a_line);
                i++;
            }
            //close the text file
            fclose(file_to_read);
        }

    }else{//what if the user doesn't put anything in
        printf("Usage: ./ultron [-i number of instruction] [-f filename]");
        exit(0);
    }
    //printf("you made it outside\n");NOTE: this line won't run if you don't put the new line at the end

    //2. LOAD THE PROGRAM'S INSTRUCTIONS INTO ULTRON'S MEMORY -after retrieve instruction[]
    ultron_init(pultron);//initialize Ultron computer and tie ultron pointer to the computer
    ultron_load(pultron,num_instructions,instructions);
    //3. RUN THE PROGRAM
    ultron_run(pultron);
    //4. PRINT THE RESULT OF THE PROGRAM: the result will be the latest number in the accumilator
    printf("= %d\n", ultron_accumulator(pultron));
    //5. DUMP THE MEMORY
    ultron_dump(pultron);

    return 0;
}
