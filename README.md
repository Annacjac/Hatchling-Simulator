# Hatchling Simulator
This project is a computer simulator application written in C that runs a language called Hatchling Machine Language (HML). It can perform several actions such as mathematical operations and line jumping, as well as simulates memory that stores and loads words, and an accumulator register that executes instructions. Each instruction is a 4-digit hexadecimal number: The first 2 digits indicate which operation should be performed, and the second 2 digits indicate the address of the "memory" location containing the word that the instruction applies to. Read up on software documentation [here](https://hatchlingdocumentation.netlify.app).

This Github repository includes a few example programs that you can use for the program (Note: all input numbers must be in hexadecimal).
1. one.hml - adds words in locations 04 and 05 together and stores the result in location 06.
2. two.hml - takes user input for 7 numbers (positive and negative) and computes the average.
3. three.hml - reads a series of numbers from user input and prints the largest number. The first number input should indicate how many numbers will be read

Instructions on downloading and running the program:
1. Download the Hatchling-Simulator repository and extract to your desired location.
2. Open a command terminal and redirect to the location of the repository on your computer.
3. If you're not using a pre-made HML program, simply type 'hatchling' and press enter. You can then input your instructions.
4. If you are using a pre-made program, type 'hatchling' followed by the path of the program. If it's in the same location as the rest of the files, you can just type the name of the program, and if it's in a subdirectory that's in the same location as the rest of the files, you can type the relative path. Example: 'hatchling one.hml'. After pressing enter, it will automatically execute the instructions and prompt for input accordingly.
5. If you'd like to make your own separate HML program, you can create a new text file in that same folder and type your instructions, with one on each line. It is recommended that you change the file extention to .hml, just so it's easier to distinguish as a HML program.

Finally, the C code is available to look at as well, in the file hatchling.c.
