//================================================
//
// ANNA JACOBSON
//
// Hatchling Simulator
// Computer System Fundamentals
//
//================================================


//================================================
// includes and defines
//================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ACC-MEM Arithmetic Instructions
#define ADD     "10"    // Add a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator)
#define SUB     "11"    // Subtract a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator)
#define MUL     "12"    // Multiple a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator)
#define DIV     "13"    // Divide a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator)
#define MOD     "14"    // Compute the integer remainder when dividing a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator)

// ACC-MEM Logical Instructions
#define AND     "20"    // Compute the binary AND of a specific memory location and the accumulator (leave the result in the accumulator)
#define ORR     "21"    // Compute the binary OR of a specific memory location and the accumulator (leave the result in the accumulator)
#define NOT     "22"    // Compute the logical NOT of the accumulator (leave the result in the accumulator)
#define XOR     "23"    // Compute the binary XOR of a specific memory location and the accumulator (leave the result in the accumulator)
#define LSR     "24"    // Compute the binary logical shift right (1-bit) of the accumulator (leave the result in the accumulator)
#define ASR     "25"    // Compute the binary arithmetic shift right (1-bit) of the accumulator (leave the result in the accumulator)
#define LSL     "26"    // Compute the binary logical shift left of the accumulator (leave the result in the accumulator)

// Branch Instructions
#define B       "30"    // Branch to a specific location in memory
#define BNEG    "31"    // Branch to a specific location in memory if the accumulator is negative
#define BPOS    "32"    // Branch to a specific location in memory if the accumulator is positive
#define BZRO    "33"    // Branch to a specific location in memory if the accumulator is zero

// ACC-MEM Load/Store Instructions
#define LOAD    "40"    // Load a word from a specific location in memory into the accumulator
#define STOR    "41"    // Store a word from the accumulator into a specific memory location

// I/O (Standard) Instructions
#define READ    "50"    // Read a word from the terminal into a specific location in memory
#define WRTE    "51"    // Write a word from a specific location in memory to the terminal

// HALT Instruction
#define HALT    "FF"    // Halt, i.e. the program has completed its task

//================================================
// global type statements
//================================================


//================================================
// function prototypes
//================================================
int hatchling(int numArgs, char fileName[100]);
void getInput(int memory[256]);
void loadFile(char fileName[100], int memory[256]);
void printOutput(void);

//================================================
// main function
//================================================
int main(int argc, char *argv[]){

    hatchling(argc, argv[1]);

    return(0);
}

//================================================
// hatchling function
//================================================
int hatchling(int numArgs, char fileName[100]){
    
    //variable definitions
    int accReg = 0;          //Accumulator register
    int insCount = 0;        //Instruction counter
    int insReg = 0;          //Instruction register
    char opCode[3] = "00";   //Operation code
    char operand[3] = "00";  //Operand
    int mem[256];            //Memory
    int canLoad = 1;         //Error Checker
    int canExecute = 1;

    for (int ii = 0; ii < 256; ii++){
        mem[ii] = 0;
    }
    
    //checks the number of command line arguments and executes appropriate code
    if(numArgs == 1){
        //printf("0 arguments\n");
        getInput(mem);
    }
    else if(numArgs == 2){
        //printf("1 argument\n");
        loadFile(fileName, mem);
    }
    else{
        printf("Too many arguments.\n");
    }

    //checks if there's space left in memory
    int jj = 0;
    while(mem[jj] != 0){
        if(jj > 256){
            printf("*** MEMORY FULL ***\n");
            canLoad = 0;
        }
        jj++;
    }

    //checks if the instructions are within the range of 0000-FFFF
    jj = 0;
    while(mem[jj] != 0){
        if(mem[jj] < 0 || mem[jj] > 65535){
            printf("*** BAD INSTRUCTION ON LINE %X ***\n", jj);
            canLoad = 0;
        }
        jj++;
    }
    
    //if any loading errors occurred, the program will not be executed.
    if(canLoad == 0){
        printf("*** CANNOT LOAD PROGRAM ***\n");
    }
    else{
        printf("*** PROGRAM LOADING COMPLETED ***\n");
        printf("*** PROGRAM EXECUTION STARTED ***\n");

        //executes the appropriate operation/action for each code before halting. Many instructions check for fatal errors.
        while(strcmp(opCode, "FF") != 0){
            char hex[10];
            insReg = mem[insCount];
            sprintf(hex, "%X", mem[insCount]);
            
            //splits the hex number into opCode and operand            
            for(int ii = 0; ii < 2; ii++){
                opCode[ii] = hex[ii];
            }
            for(int ii = 2; ii < 4; ii++){
                operand[ii-2] = hex[ii];
            }

            //Operations
            if(strcmp(opCode, ADD) == 0){
                //printf("ADD\n");
                accReg += mem[(long int) strtol(operand, NULL, 16)];
                if(accReg > 65535){
                    printf("*** ACCUMULATOR OVERFLOW ***\n");
                    opCode[0] = 'F';
                    opCode[1] = 'F';
                    canExecute = 0;
                }
                else
                    insCount++;
            }
            else if(strcmp(opCode, SUB) == 0){
                //printf("SUB\n");
                accReg -= mem[(long int) strtol(operand, NULL, 16)];
                if(accReg > 65535){
                    printf("*** ACCUMULATOR OVERFLOW ***\n");
                    opCode[0] = 'F';
                    opCode[1] = 'F';
                    canExecute = 0;
                }
                else
                    insCount++;
            }
            else if(strcmp(opCode, MUL) == 0){
                //printf("MUL\n");
                accReg *= mem[(long int) strtol(operand, NULL, 16)];
                if(accReg > 65535){
                    printf("*** ACCUMULATOR OVERFLOW ***\n");
                    opCode[0] = 'F';
                    opCode[1] = 'F';
                    canExecute = 0;
                }
                else
                    insCount++;
            }
            else if(strcmp(opCode, DIV) == 0){
                //printf("DIV\n");
                if(mem[(long int) strtol(operand, NULL, 16)] != 0){
                    accReg /= mem[(long int) strtol(operand, NULL, 16)];
                }
                else{
                    printf("*** CANNOT DIVIDE BY ZERO ***\n");
                    opCode[0] = 'F';
                    opCode[1] = 'F';
                    canExecute = 0;
                }
                printf("\n");
                insCount++;
            }
            else if(strcmp(opCode, MOD) == 0){
                //printf("MOD\n");
                accReg %= mem[(long int) strtol(operand, NULL, 16)];
                insCount++;
            }
            else if(strcmp(opCode, AND) == 0){
                //printf("AND\n");
                accReg = accReg & mem[(long int) strtol(operand, NULL, 16)];
                insCount++;
            }
            else if(strcmp(opCode, ORR) == 0){
                //printf("ORR\n");
                accReg = accReg | mem[(long int) strtol(operand, NULL, 16)];
                insCount++;
            }
            else if(strcmp(opCode, NOT) == 0){
                //printf("NOT\n");
                accReg = ~accReg;
                insCount++;
            }
            else if(strcmp(opCode, XOR) == 0){
                //printf("XOR\n");
                accReg = accReg ^ mem[(long int) strtol(operand, NULL, 16)];
                insCount++;
            }
            else if(strcmp(opCode, LSR) == 0){
                //printf("LSR\n");
                accReg = (unsigned int) accReg >> 1;
                insCount++;
            }
            else if(strcmp(opCode, ASR) == 0){
                //printf("ASR\n");
                accReg = accReg >> 1;
                insCount++;
            }
            else if(strcmp(opCode, LSL) == 0){
                //printf("LSL\n");
                accReg = accReg << 1;
                insCount++;
            }
            else if(strcmp(opCode, B) == 0){
                //printf("B\n");
                insCount = (long int) strtol(operand, NULL, 16);
            }
            else if(strcmp(opCode, BNEG) == 0){
                //printf("BNEG, ");
                if(accReg < 0)
                    insCount = (long int) strtol(operand, NULL, 16);
                else
                    insCount++;
            }
            else if(strcmp(opCode, BPOS) == 0){
                //printf("BPOS\n");
                if(accReg > 0)
                    insCount = (long int) strtol(operand, NULL, 16);
                else
                    insCount++;
            }
            else if(strcmp(opCode, BZRO) == 0){
                //printf("BZRO\n");
                if(accReg == 0)
                    insCount = (long int) strtol(operand, NULL, 16);
                else
                    insCount++;
            }
            else if(strcmp(opCode, LOAD) == 0){
                //printf("LOAD\n");
                accReg = mem[(long int) strtol(operand, NULL, 16)];
                if(accReg > 65535){
                    printf("*** ACCUMULATOR OVERFLOW ***\n");
                    opCode[0] = 'F';
                    opCode[1] = 'F';
                    canExecute = 0;
                }
                else
                    insCount++;
            }
            else if(strcmp(opCode, STOR) == 0){
                //printf("STOR\n");
                mem[(long int) strtol(operand, NULL, 16)] = accReg;
                accReg = 0;
                insCount++;
            }
            else if(strcmp(opCode, READ) == 0){
                printf("READ ");
                char num[6];
                fgets(num, 6, stdin);
                mem[(long int) strtol(operand, NULL, 16)] = (long int) strtol(num, NULL, 16);
                insCount++;
            }
            else if(strcmp(opCode, WRTE) == 0){
                int result = mem[(long int) strtol(operand, NULL, 16)];
                if(result < 0){
                    result *= -1;
                    printf("WRIT -%X\n", result);
                }
                else
                    printf("WRIT %X\n", result);
                insCount++;
            }
            else if(strcmp(opCode, HALT) == 0){
            printf("*** PROGRAM SUCCESSFULLY EXECUTED ***\n");
            }
            else{
                printf("*** INSTRUCTION ON LINE %X DOES NOT EXIST ***\n", insCount);
                opCode[0] = 'F';
                opCode[1] = 'F';
                canExecute = 0;
            }
        }

        if(canExecute == 0){
            printf("*** PROGRAM ABNORMALLY TERMINATED ***\n");
        }
        else{
             //prints output values
            printf("\nREGISTERS\n");
            printf("ACC      %04X\n", accReg);
            printf("InstCtr  %02X\n", insCount);
            printf("InstReg  %04X\n", insReg);
            printf("OpCode   %s\n", opCode);
            printf("Operand  %s\n\n", operand);
            
            printf("MEMORY\n");
            printf("           0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F\n");
            for(int nn = 0; nn < 16; nn++){
                printf("%X0      ", nn);
                for(int mm = nn*16; mm < (nn+1)*16; mm++){
                    if(mem[mm] != 0)
                        printf("%04X  ", mem[mm]);
                    else
                        printf("0000  ");
                }
                printf("\n");
            }
        }
       
    }


    return 0;
}

//================================================
// getInput function
//================================================
void getInput(int memory[256]){
    char code[10] = "";
    long int hexDec;
    int ii = 0;

    //takes input from terminal
    while (strcmp(code, "-99999") != 0){   //converts each hex input to decimal and stores it to memory
        fgets(code, 10, stdin);
        code [strcspn(code, "\n")] = 0;
        if(strcmp(code, "-99999") != 0){
            hexDec = (long int) strtol(code, NULL, 16);
            //printf("%li\n", hexDec);
            memory[ii] = hexDec;
        }
        ii++;
    }
}

//================================================
// loadFile function
//================================================
void loadFile(char fileName[100], int memory[256]){
    char code[10] = "";
    long int hexDec;
    int ii = 0;
    FILE* file;

    fileName [strcspn(fileName, "\n")] = 0;
    file = fopen(fileName, "r");
    
    //checks if file can be opened, throws error if not
    if(file == NULL){
        printf("File cannot be opened, try again.\n");
    }
    else{    
        //reads contents of file and stores to memory    
        do{
            fscanf(file, "%s", code);
            if(code != NULL){
                hexDec = (long int) strtol(code, NULL, 16);
                memory[ii] = hexDec;
            } 
            ii++; 
        }while(fgets(code, sizeof code, file) != NULL);
    }
    fclose(file);
    
}