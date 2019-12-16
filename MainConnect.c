/*=============================================================================
|   Source code: MainConnect.c GameFunctions.c
|           Author:  Steven Camacho
|     Student ID:  6128597
|    Assignment:  Program #4 Connect Four
|
|            Course:  COP 4338 (Programming III)
|           Section:  U03
|        Instructor:  William Feild
|        Due Date:  29 October 2019, at the beginning of class
|
|	I hereby certify that this collective work is my own
|	and none of it is the work of any other person or entity.
|	______________________________________ [Signature]
|
|        Language:  C
|  Compile/Run:	
|		make clean		(rebuild target consists of clean and build target
|		make build		clean is done in case some other file is named
|		./FinalGame		the same as the object files and the executable file
|					from this compile/run, the option -f ensures 
|					that no error message is displayed if files are not
|					found when trying to delete them. After clean, 
|					build makes the executable file, which will then be
|					executed.)
|				
| 	
|  +-----------------------------------------------------------------------------
|
|  Description:  This program is a virtual representation of the game of 
|				 Connect Four. This goal of the game is to form a four-way 
|				 tic-tac-toe. A player can win either by forming a horizontal,
|				 vertical, or diagonal line as mentioned above. Red and Yellow
|				 players take turns placing a marker in the game grid, which 
|				 will appear as the player's character. In order for the move
|				 to be legal, the selected cell must be unoccupied and the cell
|				 right below it must be occupied, unless the selected cell is 
|				 unoccupied from the bottom row. The game ends when either one
|				 wins, the game is completely full and there are no winners, 
|				 signifies a tie, or when a player resigns, which is
|				 represented by entering -1.
|
|        Input:  The input is the cell number the user desires to place their
|				 marker in. If the move is not legal, then the program will 
|				 reprompt the user for a valid cell number. 
|
|       Output:  The output is the updated game grid once each move is 
|				 validated, along with a message saying whether the move is 
|				 valid or not. Finally, if a player has either won or resigned
|				 or the game has ended in tie, the program will output it
|				 depending on the case.
|
|     Process:   The program's steps are as follows:
|					1. The game grid is initialized and is filled with
|					   the cell numbers. The instructions of the game
|					   are outputted and the game begins. 
|					2. The user is then asked to select a cell number
|					   to place their own marker in. The move is then 
|					   validated, if not valid, then the user is reprompted
|					   to enter a valid cell number. If valid, then the 
|					   game grid is updated with the move and then displayed.
|					3. After player makes his move, then next player makes 
|					   their move with the same protocol as the previous 
|					   player. 
|					4. When a player forms a four-marker line vertically,
|					   horizontally, or diagonally, they win the game. 
|					   When a player resigns, then the other player wins. 
|					   Finally, if the game grid is completely full and no
|					   player has won, then the game ends in a tie.
|
|   Required Features Not Included: All required features are included.
|
|   Known Bugs:  None; the program operates correctly.
|  *===========================================================================*/

#include "ProtoConstDef.h"		/* carries all constants, prototypes, etc. */

/* Main Program */
int main(void) {
	/* creating the game board as 2-D array */
	Cell gameBoard[ROWS][COLUMNS]; 

	/* creating this pointer simplifies passing a 2-D array into a function */
	Cell * gameBoardPtr = &gameBoard[FIRST_ROW][FIRST_CELL]; 

	/* other game variables */
	char currentMove[CELL_NUMBER];
	char player = YELLOW;
	int valid, winner;
	int moves = 0, lastCellNumber = 0;

	/* begin the game */
	startGame(gameBoardPtr);
	displayGameInstructions();

	/* players making moves */
	do {
		switchPlayer(&player); /* next player's turn */

		/* player will be prompted until they make a legal move or they resign */
		do {
			displayGameBoard(gameBoardPtr);
			makeMove(player, currentMove);
		} while (!(valid = isValid(currentMove, gameBoardPtr))
			&& !(hasResigned(lastCellNumber = getInt(currentMove))));

		performIfMoveValid(valid, &moves, player, currentMove, gameBoardPtr);

	} while (!(winner = hasPlayerWon(player, currentMove, gameBoardPtr))
		&& !hasResigned(lastCellNumber)
		&& !isFull(moves)); /* the game will end when someone wins, resigns, or
							   maximum number of moves is reached */

	/* A message must be outputted depending on the outcome of the game. */
	finalProcedure(winner, lastCellNumber, &player, gameBoardPtr);

	return NO_ERROR;
} // end main
