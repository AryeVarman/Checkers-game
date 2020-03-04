
#include "Main Header.h"
#include <time.h> 

/*** PROTOTYPES ***/


static void UpDateBoard(Board board, SingleSourceMovesList* BestMove, Player player);
static void printMove(SingleSourceMovesList* move);
static void freeList(SingleSourceMovesList* List);
static void DeleteFromBeginningOfList(SingleSourceMovesList* List);
static void freeMuletipleLists(MultipleSourceMovesList* MainList);


/*** IMPLEMENTS ***/

// this function Performs the best move for the player
void Turn(Board board, Player player)
{

	char win = 0;
	int random;
	unsigned short MaxCaptures = 0, CurrCaptures;
	MultipleSourceMovesList* AllToolsMovesList = FindAllPossiblePlayerMoves(board, player);

	MultipleSourceMovesListCell* CurrAllToolsMovesListCell = AllToolsMovesList->head;

	SingleSourceMovesList* singleMovesList;

	SingleSourceMovesList* BestMove = NULL;

	if (CurrAllToolsMovesListCell == NULL)
	{
		printf("The game ended in a draw\n");
		exit(DRAW);
	}

	srand(time(0));
	while (CurrAllToolsMovesListCell)
	{
		singleMovesList = CurrAllToolsMovesListCell->single_source_moves_list;
		CurrCaptures = singleMovesList->tail->captures;
		if (MaxCaptures < CurrCaptures)
		{
			MaxCaptures = CurrCaptures;
			BestMove = singleMovesList;
		}
		else if (MaxCaptures == CurrCaptures)
		{
			random = rand() % 3;
			if (BestMove == NULL || (!win && random == 0))
			{
				BestMove = singleMovesList;
				if (singleMovesList->tail->position->row == 'A' || singleMovesList->tail->position->row == 'H')
					win = 1;
			}
			else if (singleMovesList->tail->position->row == 'A' || singleMovesList->tail->position->row == 'H') {
				BestMove = singleMovesList;
				win = 1;
			}
		}
		CurrAllToolsMovesListCell = CurrAllToolsMovesListCell->next;
	}

	UpDateBoard(board, BestMove, player);

	printMove(BestMove);

	freeMuletipleLists(AllToolsMovesList);
}

// this function Updating the board after playing
void UpDateBoard(Board board, SingleSourceMovesList* BestMove, Player player)
{
	char change;
	Player rival;
	UpDatePlayerRivalChange(&change, player, &rival);

	SingleSourceMovesListCell* currMove = BestMove->head;

	checkersPos* prevPos;
	prevPos = createPos();

	if (BestMove->tail->captures == 0)
	{
		board[BestMove->head->position->row - 'A'][BestMove->head->position->col - '1'] = ' ';
		board[BestMove->tail->position->row - 'A'][BestMove->tail->position->col - '1'] = player;
	}
	else
	{
		prevPos->col = currMove->position->col;
		prevPos->row = currMove->position->row;
		currMove = currMove->next;
		while (currMove)
		{
			board[prevPos->row - 'A'][prevPos->col - '1'] = ' ';
			board[currMove->position->row - 'A'][currMove->position->col - '1'] = player;
			if ((prevPos->col - '1') - (currMove->position->col - '1') > 0)
				board[prevPos->row - 'A' - change][prevPos->col - '1' - 1] = ' ';
			else
				board[prevPos->row - 'A' - change][prevPos->col - '1' + 1] = ' ';

			prevPos->col = currMove->position->col;
			prevPos->row = currMove->position->row;
			currMove = currMove->next;
		}
	}


}

// this function Prints the move that is being played
void printMove(SingleSourceMovesList* move)
{
	SingleSourceMovesListCell* currTool = move->head;

	printf("%c%c", currTool->position->row, currTool->position->col);
	currTool = currTool->next;

	while (currTool)
	{
		printf("->");
		printf("%c%c", currTool->position->row, currTool->position->col);

		currTool = currTool->next;
	}
	printf("\n");
}

// this function Free the main list
void freeMuletipleLists(MultipleSourceMovesList* MainList)
{
	MultipleSourceMovesListCell* del_cell = MainList->head;

	while (MainList->head)
	{
		del_cell = MainList->head;
		MainList->head = MainList->head->next;
		if (MainList->head == NULL)
			MainList->tail = NULL;
		freeList(del_cell->single_source_moves_list);
		free(del_cell);
	}
	free(MainList);
}

// this function Free list
void freeList(SingleSourceMovesList* List)
{
	while (List->head)
		DeleteFromBeginningOfList(List);
	free(List);
}

// this function Deletes a cell from the beginning of the list
void DeleteFromBeginningOfList(SingleSourceMovesList* List)
{
	SingleSourceMovesListCell* del_cell = List->head;

	List->head = List->head->next;
	if (List->head == NULL)
		List->tail = NULL;
	free(del_cell->position);
	free(del_cell);
}
