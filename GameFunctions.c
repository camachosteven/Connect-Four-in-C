#include "ProtoConstDef.h"

/*---------------------------- startGame ----------------------------
		|  Function startGame (game)
		|
		|  Purpose: Fill the game grid with the cell numbers. The storeNumber
		|			method handles the intricacies of instantiating the cells
		|			with their corresponding numbers. 
		|
		|  @param  the game board pointer to the first cell in the grid
		|
		|  @return  none
		*-------------------------------------------------------------------*/
void startGame(Cell* game) {
	for (int rowCounter = 0; rowCounter < ROWS; rowCounter++) {
		for (int cellCounter = 0; cellCounter < COLUMNS; cellCounter++) {
			storeNumber(game++, rowCounter, cellCounter);
		}
	}
} // end function

/*---------------------------- storeNumber ----------------------------
		|  Function storeNumber (cell, row, column)
		|
		|  Purpose: This method stores the number into its respective cell. 
		|			The cell struct has a number char variable of size 3. 
		|			If the number is less than 10, then what is stored is 
		|			a space followed by the number and the null terminating
		|			character. If the number is greater than or equal to 10,
		|			then the number is stored followed by the null terminating
		|			character. The number value is calculated by initially 
		|			multiplying its row number by the COLUMNS constant of 7
		|			and adding 1. This is because for the first element of 
		|			the ith row, number must be (7 * i) + 1. Lastly, we add 
		|			the column number. For example, to calculate the number 
		|			in row 0 and column 2, then number = 7 * 0 + 1 + 2 = 2.
		|			For number in row 4 and column 7,  7 * 4 + 1 + 5 = 35.
		|			(Since game grid is represented by a 2-D array, rows 
		|			are counted starting from 0 instead of 1.)
		|
		|  @param  cell pointer to the desired cell to be filled
		|  @param  the cell's row
		|  @param  the cell's column
		|
		|  @return  none
		*-------------------------------------------------------------------*/
void storeNumber(Cell* cell, int row, int column) {
	int index = 0;
	int number = COLUMNS * row + column + 1;		

	/* 10 is used to reduce the 2 digit number into one. 
	   (15 / 10 = 1.5 = 1) */
	char firstDigit = (number / 10) + ASCII_ZERO; 
	char secondDigit = (number % 10) + ASCII_ZERO;
	cell->number[index++] = (firstDigit == ASCII_ZERO) 
		? SPACE 
		: firstDigit;
	cell->number[index++] = secondDigit;
	cell->number[index++] = NULL_CHAR;
} // end function

/*---------------------------- displayInstructions ----------------------------
		|  Function displayInstructions (void)
		|
		|  Purpose: This method displays the game's name and the instructions
		|			on how to play the game. It informs the user on how to
		|			make moves and how a player can win the game.
		|
		|  @param   none
		|
		|  @return  none
		*-------------------------------------------------------------------*/
void displayGameInstructions(void) {
	printf("%s", "Welcome to the game of Connect Four!!\n");
	printf("%s", "To win the game, a player must form a four-way tic-tac-toe "
		"either horizontally, vertically, or diagonally.\n");
	printf("%s", "Each player alternates in choosing where to place their marker.\n");
	printf("%s", "Red player goes first. In the subsequent games, the players "
		"take turns as the Red player.\n");
	printf("%s", "When choosing where to place marker, player must choose an empty "
		"cell that has an occupied cell right below it. \nThe only exceptions "
		"are the cells in the bottom of the game board. \n\n");
} // end function

/*---------------------------- switchPlayer ----------------------------
		|  Function switchPlayer (lastPlayer)
		|
		|  Purpose: The method switches the player character with will be
		|			used as players take turns or to determine if a player
		|			has resigned and the other player must be crowned the
		|			winner.
		|
		|  @param   pointer to the player variable
		|
		|  @return  none
		*-------------------------------------------------------------------*/
void switchPlayer(char* lastPlayer) {
	if (*lastPlayer == YELLOW)* lastPlayer = RED;
	else *lastPlayer = YELLOW;
} // end function

/*---------------------------- displayGameBoard ----------------------------
		|  Function displayGameBoard (game)
		|
		|  Purpose: This method displays the entire game grid. It is called
		|			to display the initial empty game and when each move is
		|		    made to show how the game progresses.
		|
		|  @param  the pointer to the first element of the game grid
		|
		|  @return  none
		*-------------------------------------------------------------------*/
void displayGameBoard(Cell* game) {
	for (int rowCounter = 0; rowCounter < ROWS; rowCounter++) {
		printf("%s\n", "------------------------------------");
		for (int columnCounter = 0; columnCounter < COLUMNS; columnCounter++) {
			printf("| %s ", (*game++).number);
		}
		puts("|");
	}
	printf("%s", "------------------------------------\n");
} // end function

/*---------------------------- makeMove ----------------------------
		|  Function makeMove (player, input)
		|
		|  Purpose: The method prompts the user to select a cell to place
		|			their marker in and simply stores it into the local
		|			input's character array.
		|
		|  @param  the player's character
		|  @param  the char array to store the cell number
		|
		|  @return  none
		*-------------------------------------------------------------------*/
void makeMove(char player, char input[]) {
	char* color = (player == YELLOW) ? "Yellow" : "Red";
	printf("%s%s%s", "\nPlayer '", color, "', ");
	printf("%s", "please enter a number to place marker. \nOnly empty cells "
		"can be selected and there must be an occupied cell below it.\n");
	printf("%s", "Cell Number: ");
	char num = 'J'; // initialize with arbitrary character
	int index;
	for (index = 0; index < CELL_NUMBER - 1 && (num = getchar()) != EOF
		&& num != '\n'; index++) {
		input[index] = num;
	}
	if (num == '\n')  input[index++] = num;
	input[index] = NULL_CHAR;
} // end function

/*---------------------------- getInt ----------------------------
		|  Function getInt (input)
		|
		|  Purpose: This method simply converts the user's input into an
		|			integer. If the char array can be converted into an int,
		|			the return value is the number itself, if not then the
		|			return value is 0 (FALSE).
		|
		|  @param   input char array
		|
		|  @return  0 (FALSE) if array cannot be converted to int
		|			int otherwise
		*-------------------------------------------------------------------*/
int getInt(char input[]) {
	int index, sign;
	int number = 0;

	/* remove all spaces from input */
	for (index = 0; index < CELL_NUMBER && isspace(input[index]); index++);

	/* determine sign of number */
	if (input[index] == '-') {
		sign = NEGATIVE;
		index++;
	}
	else {
		sign = POSITIVE;
	}

	/* if char is not a digit, then input is not a number */
	while (input[index] != '\0' && input[index] != '\n') {
		if (!isdigit(input[index])) return FALSE;
		number *= 10;
		number += input[index++] - '0';
	}
	return sign * number;
} // end function

/*---------------------------- isValid ----------------------------
		|  Function isValid (input, game)
		|
		|  Purpose: The method checks whether the input by the user is valid.
		|			It does so by first checking whether the user has
		|			resigned. If they haven't then they check if they entered
		|			outside of the range of the game grid. If it isn't, it
		|			checks whether the cell is occupied. If it is unoccupied,
		|			the program then checks if the cell below is unoccupied.
		|			If it is occupied, then the move is valid. If at any
		|			stage the number does not meet any one of the
		|			requirements, the move is invalid.
		|
		|  @param  input given by user
		|  @param  pointer to the game grid
		|
		|  @return  1 (TRUE) if all tests are "passed", 0 (FALSE) otherwise
		*-------------------------------------------------------------------*/
int isValid(char input[], Cell* game) {
	int num = getInt(input);
	if (hasResigned(num)) return FALSE;
	if (num < FIRST_NUMBER || num > LAST_NUMBER) {
		printf("%s", "The number you entered is out of the grid's range. "
			"You must select a number between 1 and 42.\n");
		return FALSE;
	}
	/* 1 is subtracted because to access ith item
	   the offset must be i - 1 */
	game += num - 1;
	if (game->number[PLAYER_CHAR] == RED || game->number[PLAYER_CHAR] == YELLOW) {
		printf("%s", "The number you entered has its corresponding cell already occupied."
			"\nPlease select an unoccupied cell from the bottom or an unoccupied cell"
			" that is on top of an occupied cell ('R' or 'Y' below it).\n\n");
		return FALSE;
	}
	game += COLUMNS;
	if (game->number[PLAYER_CHAR] != RED && game->number[PLAYER_CHAR] != YELLOW) {
		if (num < BOTTOM_LEFT) {
			printf("%s", "The number you entered cannot be selected because it does"
				" not have an occupied cell below it. \nPlease select an unoccupied"
				"cell from the bottom or an unoccupied cell that is on top of an "
				"occupied cell\n('R' or 'Y' below it).\n\n");
			return FALSE;
		}
	}
	return TRUE;
} // end function

/*---------------------------- hasResigned ----------------------------
		|  Function hasResigned (input)
		|
		|  Purpose: This method checks to see if the player entered the
		|			number -1, which means that they have resigned.
		|
		|  @param  the number inputted
		|
		|  @return  1 (TRUE) if number is -1, 0 (FALSE) otherwise
		*-------------------------------------------------------------------*/
int hasResigned(int input) {
	return input == RESIGN;
} // end function

/*---------------------------- performIfMoveValid ----------------------------
		|  Function performIfMoveValid (validation, movePtr,
		|								player, moveInput, game)
		|
		|  Purpose: This method adds to the total number of moves and changes
		|			the cell inputted by the user, only if the move is valid
		|			which is determined by the validation integer.
		|
		|  @param validation number that determines if move is valid
		|  @param pointers to the moves variable in main
		|  @param the player's character
		|  @param the cell to change its value to the player char
		|  @param the pointer to the game grid
		|
		|  @return  none
		*-------------------------------------------------------------------*/
void performIfMoveValid(int validation, int* movePtr,
	char player, char moveInput[], Cell* game) {
	if (validation) {
		(*movePtr)++;
		changeCell(player, moveInput, game);
		printf("%s", "\nThe move is valid.\n");
	}
} // end function

/*---------------------------- changeCell ----------------------------
		|  Function changeCell (player, input, game)
		|
		|  Purpose: This method is called when a move is validated and the 
		|			cell must be updated. The method access the number 
		|			variable in the cell struct has changes it to a space 
		|			with the player's character and the null terminating 
		|			character. 
		|
		|  @param  the player's character, 'R' for Red, 'Y' for Yellow
		|  @param  the number inputted by the user
		|  @param  the pointer to the first element of the game grid
		|
		|  @return  none
		*-------------------------------------------------------------------*/
void changeCell(char player, char input[], Cell * game) {
	int index = 0;
	int number = getInt(input);

	/* 1 is subtracted because to access ith item
	   the offset must be i - 1 */
	Cell* cellLocationPtr = game + number - 1;
	cellLocationPtr->number[index++] = SPACE;
	cellLocationPtr->number[index++] = player;
	cellLocationPtr->number[index] = NULL_CHAR;

} // end function

/*---------------------------- hasPlayerWon ----------------------------
		|  Function hasPlayerWon (player, lastMove, game)
		|
		|  Purpose: This method is the caller to the possible ways the 
		|			player can win: vertically, horizontally, or 
		|			diagonally. If player has won, the return value is 
		|			either 1, 2, 3, or 4 depending on how the player
		|			won so that the win type can be known outside the 
		|			function. 
		|
		|  @param  the player's character
		|  @param  the last move made
		|  @param  the pointer to the game grid
		|
		|  @return  1 (TRUE) if the player won, 0 (FALSE) otherwise 
		*-------------------------------------------------------------------*/
int hasPlayerWon(char player, char lastMove[], Cell* game) {
	if (verticalWin(player, lastMove, game)) {
		return VERTICAL;
	}
	else if (horizontalWin(player, lastMove, game)) {
		return HORIZONTAL;
	}
	else if (leftDiagonalWin(player, lastMove, game)) {
		return LEFT_DIAGONAL;
	}
	else if (rightDiagonalWin(player, lastMove, game)) {
		return RIGHT_DIAGONAL;
	}
	else {
		return NO_WIN;
	}
} // end function

/*---------------------------- isFull ----------------------------
		|  Function isFull (numOfMoves)
		|
		|  Purpose: This method checks whether the game has reached the max
		|			number of moves. In the program, if this is true and 
		|			no player has won, then the game ends in a tie.
		|
		|  @param  the number of moves made in the game
		|
		|  @return  1 (TRUE) if maximum number of moves is reached,
		|			0 (FALSE) otherwise
		*-------------------------------------------------------------------*/
int isFull(int numOfMoves) {
	return numOfMoves == MAX_POSSIBLE_MOVES;
}

/*---------------------------- verticalWin ----------------------------
		|  Function verticalWin (player, lastMove, game)
		|
		|  Purpose: This is the 1st of 4 ways a player can win the game.
		|			To check for a four-way vertical line, the method counts
		|			the current cell as one, because it was just entered. 
		|			The cell below is then checked to determine if it is the 
		|			same character as the player's. If it is, then vertical 
		|			count is incremented. This repeats until a cell that 
		|			doesn't match is found. Once it reaches an unmatching cell
		|			OR it reaches the bottom row, the loop ends and goes
		|			back to original cell. The cell above is then checked in 
		|			same procedure as before. Once it reaches an unmatched 
		|			cell or the top of the game grid, the loop ends.
		|			Finally the method returns TRUE if the fullVertical, which
		|			represents the number of vertical consecutive markers 
		|			equals 4, FALSE if otherwise. 
		|
		|			In topOfboardPtr and bottomOfBoardPtr, the only exception 
		|			is when the number is from the rightmost column. This 
		|			assignment was required	so that all numbers were 
		|			pointed to correctly. For bottomOfBoardPtr, ROWS * 
		|			ROWS - 1 is the first element in the bottom row. then 
		|			lastCell % COLUMNS - 1 is added	to know specifically 
		|			where the number is in its row.
		|
		|  @param  the player's character
		|  @param  last move made by the player
		|  @param  pointer to the game grid
		|
		|  @return  1 (TRUE) if fullVertical equal to 4, 0 (FALSE) otherwise
		*-------------------------------------------------------------------*/
int verticalWin(char player, char lastMove[], Cell* game) {
	int fullVertical = 1;
	int lastCell = getInt(lastMove);

	/* 1 is subtracted because to access ith item
	   the offset must be i - 1;
	   lastCell % COLUMNS is where the number is in its row */
	Cell* const topOfBoardPtr = (lastCell % COLUMNS == 0)
		? game + COLUMNS - 1 
		: game + lastCell % COLUMNS - 1; 
	Cell* const bottomOfBoardPtr = (lastCell % COLUMNS == 0)
		? game + ROWS * COLUMNS - 1 
		: game + (ROWS * ROWS - 1) + (lastCell % COLUMNS - 1); 
	Cell* currentCellPtr = game + lastCell - 1; // return to original cell

	/* since currentCell has player's char, begin with cell right below */
	game = currentCellPtr + COLUMNS;
	while (game->number[PLAYER_CHAR] == player && bottomOfBoardPtr >= game) {
		fullVertical++;
		game += COLUMNS;
	}

	/* since currentCell has player's char, begin with cell right above */
	game = currentCellPtr - COLUMNS;
	while (game->number[PLAYER_CHAR] == player && topOfBoardPtr <= game) {
		fullVertical++;
		game -= COLUMNS;
	}
	return fullVertical == WINNING_FOUR;
} // end function

/*---------------------------- horizontalWin ----------------------------
		|  Function horizontalWin (player, lastMove, game)
		|
		|  Purpose: This is the 2nd of 4 ways a player can win the game.
		|			To check for a four-way horizontal line, method counts
		|			the current cell as one, because it was just entered.
		|			The cell immediate to the right is then checked to 
		|			determine if it is the same character as the player's. 
		|			If it is, then the horizontal count is incremented. This 
		|			repeats until a cell that doesn't match is found. Once 
		|			it reaches an unmatching cell OR it reaches the right 
		|			column, the loop ends and goes back to original cell.
		|			The cell immediate to the left is then checked in same 
		|			procedure as before. Once it reaches an unmatched cell 
		|			or the left of the game grid, the loop ends. Finally 
		|			the method returns TRUE if the fullHorizontal, which
		|			represents the number of horizontal consecutive markers
		|			equals 4, FALSE if otherwise. 
		|
		|			Wherever there's a subtraction of 1 to end result, this
		|			is because to get the ith element, offset must be equal
		|			to i - 1. For leftOfBoardPtr, the exception is when the 
		|			cell number is from rightmost column. lastCell / COLUMNS
		|			calculates the row the number is in. However, since row
		|			counting starts from 0, you subtract 1. Else, you add 
		|			the number to the pointer and then you subtract its 
		|			position in its row, which is calculated by 
		|			lastCell % COLUMNS. 
		|
		|  @param  the player's character
		|  @param  last move made by the player
		|  @param  pointer to the game grid
		|
		|  @return  1 (TRUE) if fullHorizonal equal to 4, 0 (FALSE) otherwise
		*-------------------------------------------------------------------*/
int horizontalWin(char player, char lastMove[], Cell* game) {
	int fullHorizontal = 1;
	int lastCell = getInt(lastMove);
	Cell* const leftOfBoardPtr = (lastCell % COLUMNS == 0) 
		? game + COLUMNS * (lastCell / COLUMNS - 1)
		: game + lastCell - (lastCell % COLUMNS);
	Cell* const rightOfBoardPtr = leftOfBoardPtr + COLUMNS - 1;
	Cell* currentCellPtr = game + lastCell - 1; 
	game = currentCellPtr + 1; /* begin with the cell immediate to the right */
	while (game->number[PLAYER_CHAR] == player && rightOfBoardPtr >= game) {
		fullHorizontal++;
		game += 1;
	}

	game = currentCellPtr - 1; /* begin with the cell immediate to the left */
	while (game->number[PLAYER_CHAR] == player && leftOfBoardPtr <= game) {
		fullHorizontal++;
		game -= 1;
	}

	return fullHorizontal == WINNING_FOUR;
} // end function

/*---------------------------- leftDiagonalWin ----------------------------
		|  Function leftDiagonalWin (player, lastMove, game)
		|
		|  Purpose: This is the 3rd of 4 ways a player can win the game.
		|			To check for a four-way left diagonal line, method counts
		|			the current cell as zero, because that way the four 
		|			pointers don't need to be reassigned their cell when 
		|			checking in the other direction. The cell below to 
		|			the right is then checked to determine it is the same 
		|			character as the player's. If it is, then leftDiagonal 
		|			count is incremented. This repeats until a cell that
		|			doesn't match is found. Once it reaches an unmatching 
		|			cell OR it reaches the bottom row or the right column, 
		|			the loop ends and goes back to original cell. The 
		|			fullLeftDiagonal must be decremented because the original 
		|			cell was already accounted for and will be counted again 
		|			in the next loop. The cell above to the left is then 
		|			checked in same procedure as before. Once it reaches 
		|			an unmatched cell or the top row or left column, the 
		|			loop ends. Finally the method returns TRUE if the 
		|			fullLeftDiagonal, which represents the number of left 
		|			diagonal consecutive markers, equals 4, FALSE if 
		|			otherwise.
		|
		|			The explanation for why the top pointer, bottom pointer, 
		|			left pointer, and right pointer have the values they have
		|			are in the verticalWin and horizontalWin documentation.
		|			All four pointers are need since the cells checked are in
		|			a diagonal so the loops must know to terminate when the
		|			game pointer passes one of those boundaries. 
		|
		|  @param  the player's character
		|  @param  last move made by the player
		|  @param  pointer to the game grid
		|
		|  @return  1 (TRUE) if fullLeftDiagonal equal to 4
		|			0 (FALSE) otherwise
		*-------------------------------------------------------------------*/
int leftDiagonalWin(char player, char lastMove[], Cell* game) {
	int fullLeftDiagonal = 0;
	int lastCell = getInt(lastMove);
	Cell* topOfBoardPtr = (lastCell % COLUMNS == 0)
		? game + COLUMNS - 1
		: game + lastCell % COLUMNS - 1;
	Cell* bottomOfBoardPtr = (lastCell % COLUMNS == 0)
		? game + (ROWS * COLUMNS - 1)
		: game + (ROWS * ROWS - 1) + lastCell % COLUMNS - 1;
	Cell* leftOfBoardPtr = (lastCell % COLUMNS == 0)
		? game + COLUMNS * (lastCell / COLUMNS - 1)
		: game + lastCell - (lastCell % COLUMNS);
	Cell* rightOfBoardPtr = leftOfBoardPtr + COLUMNS - 1;
	Cell* currentCellPtr = game + lastCell - 1;

	game = currentCellPtr;
	while (game->number[PLAYER_CHAR] == player
		&& bottomOfBoardPtr >= game
		&& rightOfBoardPtr >= game) {
		fullLeftDiagonal++;
		bottomOfBoardPtr += 1;
		rightOfBoardPtr += COLUMNS;
		game += COLUMNS + 1;
	}

	game = currentCellPtr;
	fullLeftDiagonal--;
	while (game->number[PLAYER_CHAR] == player
		&& topOfBoardPtr <= game
		&& leftOfBoardPtr <= game) {
		fullLeftDiagonal++;
		topOfBoardPtr -= 1;
		leftOfBoardPtr -= COLUMNS;
		game = game - COLUMNS - 1;
	}

	return fullLeftDiagonal == WINNING_FOUR;
} // end function

/*---------------------------- rightDiagonalWin ----------------------------
		|  Function leftDiagonalWin (player, lastMove, game)
		|
		|  Purpose: This is the 4th of 4 ways a player can win the game.
		|			To check for a four-way right diagonal line, method counts
		|			the current cell as zero, because that way the four 
		|			pointers don't need to be reassigned their cell when 
		|			checking in the other direction. The cell below to the 
		|			left is then checked to determine it is the same 
		|			character as the player's. If it is, then rightDiagonal 
		|			count is incremented. This repeats until a cell that 
		|			doesn't match is found. Once it reaches an unmatching 
		|			cell OR it reaches the bottom row or the left column, 
		|			the loop ends and goes back to original	cell. The 
		|			fullRightDiagonal must be decremented because the 
		|			original cell was already accounted for and will be 
		|			counted again in the next loop.The cell above to the 
		|			right is then checked in same procedure as before. 
		|			Once it reaches an unmatched cell or the top row or 
		|			right column, the loop ends. Finally the method returns 
		|			TRUE if the fullRightDiagonal, which represents the 
		|			number of right diagonal consecutive markers, equals 
		|			4, FALSE if otherwise.
		|
		|			The explanation for why the top pointer, bottom pointer, 
		|			left pointer, and right pointer have the values they have
		|			are in the verticalWin and horizontalWin documentation.
		|			All four pointers are need since the cells checked are in
		|			a diagonal so the loops must know to terminate when the
		|			game pointer passes one of these boundaries. 
		|
		|  @param  the player's character
		|  @param  last move made by the player
		|  @param  pointer to the game grid
		|
		|  @return  1 (TRUE) if fullRightDiagonal equal to 4
		|			0 (FALSE) otherwise
		*-------------------------------------------------------------------*/
int rightDiagonalWin(char player, char lastMove[], Cell* game) {
	int fullRightDiagonal = 0;
	int lastCell = getInt(lastMove);
	Cell* topOfBoardPtr = (lastCell % COLUMNS == 0)
		? game + COLUMNS - 1
		: game + lastCell % COLUMNS - 1;
	Cell* bottomOfBoardPtr = (lastCell % COLUMNS == 0)
		? game + (ROWS * COLUMNS - 1)
		: game + (ROWS * ROWS - 1) + lastCell % COLUMNS - 1;
	Cell* leftOfBoardPtr = (lastCell % COLUMNS == 0)
		? game + COLUMNS * (lastCell / COLUMNS - 1)
		: game + lastCell - (lastCell % COLUMNS);
	Cell* rightOfBoardPtr = leftOfBoardPtr + COLUMNS - 1;
	Cell* currentCellPtr = game + lastCell - 1;

	game = currentCellPtr;
	while (game->number[PLAYER_CHAR] == player
		&& bottomOfBoardPtr >= game
		&& leftOfBoardPtr <= game) {
		fullRightDiagonal++;
		bottomOfBoardPtr -= 1;
		leftOfBoardPtr += COLUMNS;
		game += COLUMNS - 1;
	}

	game = currentCellPtr;
	fullRightDiagonal--;
	while (game->number[PLAYER_CHAR] == player
		&& topOfBoardPtr <= game
		&& rightOfBoardPtr >= game) {
		fullRightDiagonal++;
		topOfBoardPtr += 1;
		rightOfBoardPtr -= COLUMNS;
		game = game - COLUMNS + 1;
	}

	return fullRightDiagonal == WINNING_FOUR;
} // end function

/*---------------------------- finalProcedure ----------------------------
		|  Function finalProcedure (winner, lastCell, player, game)
		|
		|  Purpose: This finalizes the game. When the loop ends, it can be
		|			because someone won, someone resigned, or the game is 
		|			tied. Therefore, this method determines the reason for 
		|			the loop ending and outputs the necessary message.
		|
		|  @param   winner int (BOOL) value
		|  @param   last number entred to see if a player resigned
		|  @param   player's character to display who is the winner
		|  @param   the pointer to the game grid
		|
		|  @return  none
		*-------------------------------------------------------------------*/
void finalProcedure(int winner, int lastCell, char * player, Cell * game) {
	if (winner) {
		char* winningPlayer = (*player == YELLOW) ? "Yellow" : "Red";
		displayGameBoard(game);
		printf("%s%s%s", "\nPlayer '", winningPlayer, "' has won this game with ");
		if (winner == VERTICAL) {
			printf("%s", "a vertical four-way.\n");
		} 
		else if (winner == HORIZONTAL) {
			printf("%s", "a horizontal four-way.\n");
		}
		else if (winner == LEFT_DIAGONAL) {
			printf("%s", "a left diagonal four-way.\n");
		}
		else { // player won with a right diagonal
			printf("%s", "a right diagonal four-way.\n");
		}
	}
	else if (hasResigned(lastCell)) {
		switchPlayer(player);
		char* color = (*player == RED) ? "Red" : "Yellow";
		displayGameBoard(game);
		printf("%s%s%s", "\nPlayer '", color, "' has won due to the other "
			"player's resignation.\n");
	}
	else { // game has reached maximum number of moves
		displayGameBoard(game);
		printf("%s", "\nThe game has ended in a tie.\nBoth players failed"
			" to make a four-way tic-tac-toe.\n");
	}
} // end function