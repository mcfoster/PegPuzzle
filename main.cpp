/****************************************************************************
Author: Martin C. Foster
Date: April 21,2019
The getch functions were found here:
https://www.daniweb.com/programming/software-development/
                                     threads/410155/gcc-equivalent-for-getch
The object is to remove remove the pegs by jumping over them.
You will have solved the puzzle by ending up with only a single remaining peg.
  Layout      Indexes
    1            0
   1 1         1  2
  1 1 1       3  4  5
 1 1 1 1     6  7  8  9
1 1 1 1 1  10 11 12 13 14

***************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Uncomment the following if building on linux.
//#define LINUX_APP

#ifdef LINUX_APP
#include <termios.h>
#else
#include <conio.h>
#endif
#include <unistd.h>
#include <stdio.h>
#include "CJumpChoices.h"

#ifndef FALSE
#define FALSE 0
#define TRUE !FALSE
#endif // FALSE


const int PegHoles = 15;
char puzzleBoard[] = "111111111111111";

int FetchEmptyPeg();
void showPuzzle(char board[]);
#ifdef LINUX_APP
int getch(void);
int getche(void);
#endif

const int TotalJumpOptions = 36;
// All choices {from, to, jumped} indexes
JumpChoice AllChoices[TotalJumpOptions] = {{0, 3, 1}, {0, 5, 2}, {1,6,3},
        {1,8,4},{2,7,4},
        {2,9,5}, {3,0,1}, {3,5,4}, {3,10,6}, {3,12,7}, {4,11,7}, {4,13,8},
        {5,0,2}, {5,3,4}, {5,12,8}, {5,14,9}, {6,1,3}, {6,8,7}, {7,2,4},
        {7,9,8}, {8,1,4}, {8,6,7}, {9,2,5}, {9,7,8}, {10,3,6}, {10,12,11},
        {11,4,7}, {11,13,12}, {12,3,7}, {12,5,8}, {12,10,11}, {12,14,13},
        {13,4,8}, {13,11,12}, {14,5,9}, {14,12,13}};


void DoJumps(char *board, CJumpChoices *history);
int RemainingJumps(char *board);
CJumpChoices *findChoices(char *board);
void jump(JumpChoice choice, char *board);
int countPegs(char *board);
void printHistory(CJumpChoices *history);


/****************************************************************************
*
****************************************************************************/
int main(int argc, char** argv) {
    int startPg;
    CJumpChoices *historyList = new CJumpChoices();
    //showPuzzle(puzzleBoard);
    if (argc > 1) {
        startPg =   atoi(argv[1]);
        if((startPg < 0) ||(startPg >= PegHoles))
            startPg = 0;
    } else {
        startPg = FetchEmptyPeg();
    }
    puzzleBoard[startPg] = '0';
    showPuzzle(puzzleBoard);
    DoJumps(puzzleBoard, historyList);
    return 0;
}

/****************************************************************************
 * Recursif function to find all jumps
 * @param peg the jump from peg
 * @param board
 * @param history
 */
void DoJumps(char *board, CJumpChoices *history)
{
    CJumpChoices *jumps = findChoices(board);
    int count = jumps->RecCount;

    //showPuzzle(board);
    //printf("Jump count= %d\n",count);

    if(count < 1)
    {
        int pegCount = countPegs(board);
        if(pegCount == 1) // winner
        {
            printf("Winner\n");
            printHistory(history);
        }

        history->clear();
        // new board
    }
    else
    {
        for(int i = 0;i<count;i++)
        {
            char *myBoard  = strdup(board);
            CJumpChoices *myHistory = new CJumpChoices(history);
            JumpChoice jmp = jumps->get(i);
            //printf("Jump from %d, to %d\n", jmp.from, jmp.to);
            jump(jmp,myBoard);
            myHistory->add(jmp);
            DoJumps(myBoard, myHistory);
            delete myBoard;
        }
    }
    delete jumps;
}


/***************************************************************************
 * Get the number of pegs remaining in the board.
 * @param board
 * @return
 */
int countPegs(char *board)
{
    int count = 0;
    for(int i=0; (i < PegHoles) && board[i]; i++)
        if(board[i] == '1')
            count++;
    return count;
} // countPegs

/****************************************************************************
 * Locate all of the valid jump options from a given peg Index then
 * return the list of options.
 * @param fromPeg
 * @return
 */
CJumpChoices *findChoices(char *board)
{
    CJumpChoices *validJumps = new CJumpChoices();
    for (int i = 0; i < TotalJumpOptions; i++) {
        if (board[AllChoices[i].from] == '1') {
            if ((board[AllChoices[i].to] == '0') &&
                (board[AllChoices[i].jumped] == '1'))
                validJumps->add(AllChoices[i]);
        }
    } // next i
    return validJumps;
}

/****************************************************************************
 * Execute the jump on the board
 * @param choice
 * @param board
 */
void jump(JumpChoice choice, char *board)
{
    if((board[choice.from] == '1') && (board[choice.to] == '0')
       && (board[choice.jumped] == '1'))
    {
        board[choice.from] = '0';
        board[choice.jumped] = '0';
        board[choice.to] = '1';
    }
} // jump

/****************************************************************************
* Fetch a user selected blank peg. Default is zero.
****************************************************************************/
int FetchEmptyPeg()
{
    char c;

    int done = FALSE;
    int temp=0, rval = 0;
    printf("Enter starting peg hole, 0 to 14 (0): ");
    do{
        c = (char) getch();
        if((c >= '0') && (c <= '9'))
        {
            putchar(c); //show the digit
            temp = temp * 10 + (c - '0');
        }
        else if(c <= 13) // Return or linefeed
            done = TRUE;
        if(temp > 9) // two digits
            done = TRUE;
        if((temp > 0) &&(temp < 15))
            rval=temp;
    } while (!done);
    putchar('\n');
    return rval;
}

/****************************************************************************
* Output the puzzle to the console
****************************************************************************/
void showPuzzle(char board[])
{
    int buffer = 5;
    int rows = 5;
    int cols = 1;
    int idx = 0;
//    for(int i=0; i<rows; i++)
//    {
//        for(int j=0;j<buffer;j++)
//            putchar(' ');
//        buffer--;
//        for(int j=0;j<cols;j++){
//            putchar(board[idx++]);
//            putchar(' ');
//        }
//        cols++;
//        putchar('\n');
//    }

    for(int i=0; i<rows; i++)
    {
        for(int j=0;j<buffer;j++)
            printf("  ");
        buffer--;
        for(int j=0;j<cols;j++){
            printf("%c[%02d] ", board[idx], idx);
            idx++;
        }
        cols++;
        putchar('\n');
    }

} // showPuzzle

/****************************************************************************
 * Print thejump history
 */
void printHistory(CJumpChoices *history)
{
    for(int i=0; i<history->RecCount; i++)
    {
       printf("From: %d, to: %d\n",
              history->get(i).from, history->get(i).to);
    } // next i
} // printHistory

#ifdef LINUX_APP
/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
/* reads from keypress, echoes */
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
#endif
