

#include "Main Header.h"


/*** PROTOTYPES ***/

static MultipleSourceMovesList* createMultipleSourceEmptyList();
static MultipleSourceMovesListCell* createMultipleSourceCell(SingleSourceMovesList* data);
static void add_Cell_To_Multiple_Source_List(MultipleSourceMovesList* list, MultipleSourceMovesListCell* cell);



/*** IMPLEMENTS ***/



// this function gets the board and the player that is playing and return a list of all the optimal moves for each tool on the board
MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player)
{
	MultipleSourceMovesList* multipleSourceList;
	MultipleSourceMovesListCell* multipleSourceNewCell;
	SingleSourceMovesTree* singleSourceTree;
	SingleSourceMovesList* singleSourceList;
	checkersPos* pos;
	int i, j, maxNumOfTools = 12, turnPlayerToolCounter;

	multipleSourceList = createMultipleSourceEmptyList();

	pos = createPos();

	for (i = 0, turnPlayerToolCounter = 0; i < BOARD_SIZE && turnPlayerToolCounter < maxNumOfTools; i++) {
		for (j = 0; j < BOARD_SIZE && turnPlayerToolCounter < maxNumOfTools; j++) {

			if (board[i][j] == player) {
				turnPlayerToolCounter++;
				pos->row = i + 'A';
				pos->col = j + '1';

				singleSourceTree = FindSingleSourceMoves(board, pos);
				singleSourceList = FindSingleSourceOptimalMove(singleSourceTree);

				if (singleSourceList) {
					multipleSourceNewCell = createMultipleSourceCell(singleSourceList);
					add_Cell_To_Multiple_Source_List(multipleSourceList, multipleSourceNewCell);

				}
			}
		}
	}
	return multipleSourceList;
}

// this function create a multiple source empty list
MultipleSourceMovesList * createMultipleSourceEmptyList()
{
	MultipleSourceMovesList* list;

	list = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
	checkMalloc(list);

	list->head = NULL;
	list->tail = NULL;

	return list;
}

// this function create a multiple source cell for the list
MultipleSourceMovesListCell * createMultipleSourceCell(SingleSourceMovesList * data)
{
	MultipleSourceMovesListCell* cell;

	cell = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
	checkMalloc(cell);

	cell->single_source_moves_list = data;
	cell->next = NULL;

	return cell;
}

// this function add's a cell to the end of an exist list
void add_Cell_To_Multiple_Source_List(MultipleSourceMovesList * list, MultipleSourceMovesListCell * cell)
{

	if (!list->head) {							 // the list is empty
		list->head = cell;
		list->tail = cell;
	}

	else {
		list->tail->next = cell;
		list->tail = cell;
	}
}
