# Hatchling Simulator
This project is a computer simulator application that runs a language called Hatchling Machine Language (HML). It can perform several actions such as mathematical operations and line jumping, as well as simulates memory that stores and loads words, and an accumulator register that executes instructions. Each instruction is a 4-digit hexadecimal number: The first 2 digits indicate which operation should be performed, and the second 2 digits indicate the address of the "memory" location containing the word that the instruction applies to. The operation codes are as follows:

**Mathematical Operations:**  
&nbsp;&nbsp;&nbsp;&nbsp;0x10 : Adds a word from a specific location in memory to the word in the accumulator. The result is left in the accumulator.  
&nbsp;&nbsp;&nbsp;&nbsp;0x11 : Subtracts a word from a specific location in memory from the word in the accumulator. The result is left in the accumulator.  
&nbsp;&nbsp;&nbsp;&nbsp;0x12 : Multiplies a word from a specific location in memory by the word in the accumulator. The result is left in the accumulator.  
&nbsp;&nbsp;&nbsp;&nbsp;0x13 : Divides the word in the accumulator by a word from a specific location in memory. The result is left in the accumulator.  
&nbsp;&nbsp;&nbsp;&nbsp;0x14 : Computes the integer remainder when dividing the word in the accumulator by a word from a specific location in memory. The result &nbsp;&nbsp;&nbsp;&nbsp;is left in the accumulator.  
**Logical Instructions:**  
&nbsp;&nbsp;&nbsp;&nbsp;0x20 : Computes the binary AND of a specific location in memory and the accumulator. The result is left in the accumulator.  
&nbsp;&nbsp;&nbsp;&nbsp;0x21 : Computes the binary OR of a specific location in memory and the accumulator. The result is left in the accumulator.  
&nbsp;&nbsp;&nbsp;&nbsp;0x22 : Computes the binary NOT of a specific location in memory and the accumulator. The result is left in the accumulator.  
&nbsp;&nbsp;&nbsp;&nbsp;0x23 : Computes the binary XOR of a specific location in memory and the accumulator. The result is left in the accumulator.  
&nbsp;&nbsp;&nbsp;&nbsp;0x24 : Computes the binary logical shift right of the accumulator. The result is left in the accumulator.  
&nbsp;&nbsp;&nbsp;&nbsp;0x25 : Computes the binary arithmetic shift right of the accumulator. The result is left in the accumulator.  
&nbsp;&nbsp;&nbsp;&nbsp;0x26 : Computes the binary logical shift left of the accumulator. The result is left in the accumulator.  
**Branching Instructions:**  
&nbsp;&nbsp;&nbsp;&nbsp;0x30 : Branch to a specific location in memory.  
&nbsp;&nbsp;&nbsp;&nbsp;0x31 : Branch to a specific location in memory if the accumulator is negative.  
&nbsp;&nbsp;&nbsp;&nbsp;0x32 : Branch to a specific location in memory if the accumulator is positive.  
&nbsp;&nbsp;&nbsp;&nbsp;0x33 : Branch to a specific location in memory if the accumulator is zero.  
**Load/Store Instructions:**  
&nbsp;&nbsp;&nbsp;&nbsp;0x40 : Loads a word from a specific location in memory to the accumulator.  
&nbsp;&nbsp;&nbsp;&nbsp;0x41 : Stores the word in the accumulator into a specific location in memory.  
**I/O Instructions:**  
&nbsp;&nbsp;&nbsp;&nbsp;0x50 : Reads a word from the terminal into a specific location in memory.  
&nbsp;&nbsp;&nbsp;&nbsp;0x51 : Writes a word from a specific location in memory to the terminal.  
**Halt Instruction:**  
&nbsp;&nbsp;&nbsp;&nbsp;0xFF : Stops the program.  

Instructions will be stored in memory starting at location 00. Hatchling's "memory" has a capacity of 256 words, so the operand part of the instruction can be any hexadecimal number between 00 and FF (inlcusive). Variables can also be created by putting a hexadecimal value in the line number of the program that corresponds to the desired place in memory if the line numbers start at 0, or the desired place in memory + 1 if the line numbers start at 1.
An example program may look something like this (The numbers on the left hand side indicate the memory location where the instruction/word is stored. A real HML program would only include the 4-digit instructions, not the memory locations or comments.):
```
00   4004  //Loads the word in location 04 into the accumulator.  
01   1005  //Adds the word in location 05 to the word in the accumulator.  
02   4106  //Stores the word in the accumulator into location 06.  
03   FF00  //Halts the program  
04   00FF  //A variable that holds the value FF. This value is what is loaded into the accumulator in the first instruction.  
05   001E  //A variable that holds the value 1E. This value is what is added to the word in the accumulator in the second instruction.  
06   //The result of FF + 1E will be stored here.  
```
A HML program can be run through the simulator in 2 ways:
1. It can be written in a separate text file, and its path can be passed in as a command line argument when executing the program.
2. It can be written directly in the terminal if the user does not pass in a command line argument. After each instruction, press enter. Type -99999 and press enter when you are done inputing instructions to start executing your program.

When the HML program is done executing, it will print the values in the registers and memory.

This Github repository includes a few example programs that you can use for the program (Note: all input numbers must be in hexadecimal).
1. one.hml - adds words in locations 04 and 05 together and stores the result in location 06.
2. two.hml - takes user input for 7 numbers (positive and negative) and computes the average.
3. three.hml - reads a series of numbers from user input and prints the largest number. The first number input should indicate how many numbers will be read

Instructions on downloading and running the program:
1. Download the Hatchling-Simulator repository and extract to your desired location.
2. Open a command terminal and redirect to the location of the repository on your computer.
3. If you're not using a pre-made HML program, simply type 'hatchling' and press enter. You can then input your instructions.
4. If you are using a pre-made program, type 'hatchling' followed by the name of the program. Example: 'hatchling one.hml'. The program must be in the same location as the files of the repository. After pressing enter, it will automatically execute the instructions and prommt for input accordingly.
5. If you'd like to make your own separate HML program, you can create a new text file in that same folder and type your instructions. It is recommended that you change the file extention to .hml, just so it's easier to distinguish as a HML program.
