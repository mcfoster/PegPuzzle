Author: Martin C. Foster
Date: April 21,2019

Program to find solutions to the mind game Triangular Peg Board game. 
The pegs are referenced by index as follows:
        0       
      1  2      
     3  4  5    
    6  7  8  9  
  10 11 12 13 14

The game rules are simple, start with one empty peg hole, the remove pegs by jumping them one at a time. Your objective is to end up with only one remaining peg.

This is a console application written in C++ to find all posible solutions starting with any selected vacent peg hole. This code uses a recursive function call to find all solutions to the puzzle.

To compile this under linux, I found there is no conio.h, and so no getch() function. So just un-comment the "#define LINUX_APP" statement to use the alternate getch() function.

If you run the game with no commandline arguments, it will prompt you for a starting empty peg hole, otherwise it will expect that the first parameter is the desired empty peg hole. The application will begin testing all jump paths and displaying all successfull solutions. I would redirect the solutions to a test file as shown in example #3.

Examples #1:
E:\MyProjects\PegPuzzle>PegPuzzle
Enter starting peg hole, 0 to 14 (0):2
... Hundreds of solutions will scroll past the screen ...
E:\MyProjects\PegPuzzle>

Examples #2, with the empty peg hole specified in the command line parameter:
E:\MyProjects\PegPuzzle>PegPuzzle 2
... Hundreds of solutions will scroll past the screen ...
E:\MyProjects\PegPuzzle>

Examples #3. where solutions are redirected to the specified text file:
E:\MyProjects\PegPuzzle>PegPuzzle 2 > output.txt
E:\MyProjects\PegPuzzle>


