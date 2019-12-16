#include <stdio.h>				/* required for IO */
#include <ctype.h>				/* required to convert char array to int */

#define ASCII_ZERO 48			/* used to convert int in char repre. into int */
#define BOTTOM_LEFT 36			/* used to verify if inputted cell is in bottom row */
#define CELL_NUMBER 4			/* user input should only be of size 4 */
#define COLUMNS 7				/* number of columns in game grid */
#define DOUBLE_DIGIT 3			/* size of struct cell number char array */
#define FIRST_CELL 0			/* used to identify first cell of row */
#define FIRST_NUMBER 1			/* used to verify whether input is out of range */
#define FIRST_ROW 0				/* identify the first row of game grid */
#define HORIZONTAL 2			/* used to identify type of win */
#define LAST_NUMBER 42			/* used to verify whether input is out of range */
#define LEFT_DIAGONAL 3			/* used to identify type of win */
#define MAX_POSSIBLE_MOVES 42	/* max number of moves allowed in game */
#define NEGATIVE -1				/* determines input to be negative */
#define NO_ERROR 0				/* zero for no errors */
#define NO_WIN 0				/* used if player did not win with last move */
#define PLAYER_CHAR 1			/* the location of the player char in cell number variable */
#define POSITIVE 1				/* determines the input to be positive */
#define RESIGN -1				/* assigned value to signify resignation */
#define RIGHT_DIAGONAL 4		/* used to identify type of win */
#define ROWS 6					/* number of rows in game grid */
#define VERTICAL 1				/* used to identify type of win */
#define WINNING_FOUR 4			/* required number of consec. markers to win */
#define NULL_CHAR '\0'			/* terminate char arrays */
#define RED 'R'					/* represents player 'Red' */
#define SPACE ' '				/* used with single digits and individ. char */
#define YELLOW 'Y'				/* represents player 'Yellow' */

/* 
Cell structure
- used to represent each cell in the 6 x 7 game grid
- they store their corresponding number plus the null character
- when updated to a player char, they store a space, player char
and null character
*/
typedef struct {
	char number[DOUBLE_DIGIT];
} Cell;

enum BOOLEAN { FALSE, TRUE }; /* boolean values */

/* Function Prototypes */
void startGame(Cell *); 
void storeNumber(Cell *, int, int);
void displayGameInstructions(void);
void switchPlayer(char *);
void displayGameBoard(Cell *);
void makeMove(char, char[]);
int getInt(char[]);
int isValid(char[], Cell *);
int hasResigned(int);
void performIfMoveValid(int, int *, char, char[], Cell *);
void changeCell(char, char[], Cell *);
int hasPlayerWon(char, char[], Cell *);
int isFull(int);
int verticalWin(char, char[], Cell *);
int horizontalWin(char, char[], Cell *);
int leftDiagonalWin(char, char[], Cell *);
int rightDiagonalWin(char, char[], Cell *);
void finalProcedure(int, int, char *, Cell *);
