

#include "Main Header.h"

/***  PROTOTYPES  ***/


static void printBoard(Board board);
static void printPlusMinusLine();
static void printNumbersForCols();
static void checkIfToolInEndBoard(Board board, Player playerTurn, int* ENDGAME);
static void checkToolsLeft(Board board, Player rival, int* ENDGAME);


/***  IMTLEMENTS  ***/

// this function Plays the game
void PlayGame(Board board, Player starting_player)
{
	int ENDGAME = 0;
	printBoard(board);
	int MakeCapture = 0;
	Player playerTurn = starting_player;

	while (!ENDGAME)
	{
		if (playerTurn == 'T')
			printf("Player TOP_DOWN's turn\n");
		else
			printf("Player BOTTOM_UP's turn\n");

		Turn(board, playerTurn);
		printBoard(board);
		checkIfToolInEndBoard(board, playerTurn, &ENDGAME);
		if (playerTurn == 'T')
			playerTurn = 'B';
		else
			playerTurn = 'T';
		if (!ENDGAME)
			checkToolsLeft(board, playerTurn, &ENDGAME);
	}
}

// this function Checks if one of the players has reached the last line of the opponent
void checkIfToolInEndBoard(Board board, Player playerTurn, int* ENDGAME)
{
	int i;

	if (playerTurn == 'T')
	{
		for (i = 0; i < BOARD_SIZE && !*ENDGAME; i++)
		{
			if (board[BOARD_SIZE - 1][i] == playerTurn)
			{
				*ENDGAME = 1;
				printf("Player TOP_DOWN WON!\n");
			}
		}
	}
	else
	{
		for (i = 0; i < BOARD_SIZE && !*ENDGAME; i++)
		{
			if (board[0][i] == playerTurn)
			{
				*ENDGAME = 1;
				printf("Player BOTTOM_UP WON!\n");
			}
		}
	}
}

// this function Checks whether the opponent has any tools left
void checkToolsLeft(Board board, Player rival, int* ENDGAME)
{
	int i, j;
	char found = 0;

	for (i = 0; i < BOARD_SIZE && !found; i++)
	{
		for (j = 0; j < BOARD_SIZE && !found; j++)
		{
			if (board[i][j] == rival)
				found = 1;
		}
	}
	if (found == 0)
	{
		if (rival == 'T')
			printf("Player BOTTOM_UP's turn\n");
		else
			printf("Player TOP_DOWN's turn\n");
		*ENDGAME = 1;
	}



}

// this function Prints the board
void printBoard(Board board)
{
	int i, j, row, col;
	char sign = '+';

	printPlusMinusLine();
	printNumbersForCols();
	printPlusMinusLine();

	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf("|%c", 'A' + i);
		for (j = 0; j < BOARD_SIZE; j++)
		{
			printf("|%c", board[i][j]);
		}
		printf("|\n");
		printPlusMinusLine();
	}

}

void printPlusMinusLine()
{
	int i;

	for (i = 0; i <= (BOARD_SIZE + 1) * 2; i++)
	{
		if (i % 2 == 0)
			printf("+");
		else
			printf("-");
	}
	printf("\n");
}

void printNumbersForCols()
{
	int i;

	printf("| ");
	for (i = 1; i <= BOARD_SIZE; i++)
	{
		printf("|%d", i);
	}
	printf("|\n");
}
