

#include "Main Header.h"


/***  PROTOTYPES  ***/


static void findMoves(SingleSourceMovesTreeNode* root, char MakeCapture, char change, char player, char rival);
static void findMovesLeft(SingleSourceMovesTreeNode* root, char MakeCapture, char change, char player, char rival);
static void findMovesRight(SingleSourceMovesTreeNode* root, char MakeCapture, char change, char player, char rival);
static SingleSourceMovesTree* allocateTree(Board board, checkersPos *pos);
static SingleSourceMovesTreeNode* allocateTreeNode(Board board, checkersPos *pos);


/***  IMTLEMENTS  ***/


// this function gets a board and a single pawn position, it checks all of his possible move option and return 
// those options in a binary tree
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos *src)
{

	SingleSourceMovesTree* tree;
	char player = board[src->row - 'A'][src->col - '1'];
	char MakeCapture = 0;
	int change = 0;
	char rival;

	UpDatePlayerRivalChange(&change, player, &rival);

	if (!change)
		return NULL;

	tree = allocateTree(board, src);

	findMoves(tree->source, MakeCapture, change, player, rival);

	return tree;
}

// this function find the over all moves for a single pawn from a given position
static void findMoves(SingleSourceMovesTreeNode* root, char MakeCapture, char change, char player, char rival)
{

	if (root->pos->col != '1')
		findMovesLeft(root, MakeCapture, change, player, rival);
	else
		root->next_move[0] = NULL;

	if (root->pos->col != '8')
		findMovesRight(root, MakeCapture, change, player, rival);
	else
		root->next_move[1] = NULL;

}

// this function find the moves a pawn can make to  his left from a given position
static void findMovesLeft(SingleSourceMovesTreeNode* root, char MakeCapture, char change, char player, char rival)
{
	checkersPos * newPos;
	SingleSourceMovesTreeNode* newNodeL;

	newNodeL = allocateTreeNode(root->board, root->pos);
	newPos = createPos();

	if (root->board[root->pos->row - change - 'A'][root->pos->col - 1 - '1'] == rival)
	{
		if (player == 'B'  &&  root->pos->row - 'A' == 1)
			return NULL;
		if (player == 'T'  &&  root->pos->row - 'A' == 6)
			return NULL;


		if (root->pos->col - 1 - '1' == 0)
			return NULL;


		if (root->board[root->pos->row - (2 * change) - 'A'][root->pos->col - 2 - '1'] != rival
			&& root->board[root->pos->row - (2 * change) - 'A'][root->pos->col - 2 - '1'] != player)
		{
			newPos->col = root->pos->col - 2;
			newPos->row = root->pos->row - (2 * change);

			newNodeL = allocateTreeNode(root->board, newPos);
			newNodeL->total_captures_so_far = root->total_captures_so_far + 1;
			root->next_move[0] = newNodeL;
			MakeCapture = 1;

			newNodeL->board[root->pos->row - change - 'A'][root->pos->col - 1 - '1'] = ' ';
			newNodeL->board[root->pos->row - 'A'][root->pos->col - '1'] = ' ';
			newNodeL->board[newNodeL->pos->row - 'A'][newNodeL->pos->col - '1'] = player;

			findMoves(root->next_move[0], MakeCapture, change, player, rival);
		}
		else
			root->next_move[0] = NULL;
	}
	else
	{
		if (root->board[root->pos->row - change - 'A'][root->pos->col - 1 - '1'] == player)
			root->next_move[0] = NULL;
		else
		{
			if (MakeCapture == 1)
				root->next_move[0] = NULL;
			else
			{
				newPos->col = root->pos->col - 1;
				newPos->row = root->pos->row - 1 * change;
				newNodeL = allocateTreeNode(root->board, newPos);

				newNodeL->board[root->pos->row - 'A'][root->pos->col - '1'] = ' ';
				newNodeL->board[newNodeL->pos->row - 'A'][newNodeL->pos->col - '1'] = player;

				root->next_move[0] = newNodeL;
			}
		}
	}
}

// this function find the moves a pawn can make to  his right from a given position
static void findMovesRight(SingleSourceMovesTreeNode* root, char MakeCapture, char change, char player, char rival)
{
	checkersPos * newPos;
	SingleSourceMovesTreeNode* newNodeR;

	newNodeR = allocateTreeNode(root->board, root->pos);
	newPos = createPos();

	if (root->board[root->pos->row - change - 'A'][root->pos->col + 1 - '1'] == rival)
	{

		if (player == 'B'  &&  root->pos->row - 'A' == 1)
			return NULL;
		if (player == 'T'  &&  root->pos->row - 'A' == 6)
			return NULL;

		if (root->pos->col + 1 - '1' == 7)
			return NULL;


		if (root->board[root->pos->row - (2 * change) - 'A'][root->pos->col + 2 - '1'] != rival
			&& root->board[root->pos->row - (2 * change) - 'A'][root->pos->col + 2 - '1'] != player)
		{
			newPos->col = root->pos->col + 2;
			newPos->row = root->pos->row - 2 * change;

			newNodeR = allocateTreeNode(root->board, newPos);
			newNodeR->total_captures_so_far = root->total_captures_so_far + 1;
			root->next_move[1] = newNodeR;
			MakeCapture = 1;

			newNodeR->board[root->pos->row - change - 'A'][root->pos->col + 1 - '1'] = ' ';
			newNodeR->board[root->pos->row - 'A'][root->pos->col - '1'] = ' ';
			newNodeR->board[newNodeR->pos->row - 'A'][newNodeR->pos->col - '1'] = player;


			findMoves(root->next_move[1], MakeCapture, change, player, rival);
		}
		else
			root->next_move[1] = NULL;
	}
	else
	{
		if (root->board[root->pos->row - change - 'A'][root->pos->col + 1 - '1'] == player)
			root->next_move[1] = NULL;
		else
		{
			if (MakeCapture == 1)
				root->next_move[1] = NULL;
			else
			{
				newPos->col = root->pos->col + 1;
				newPos->row = root->pos->row - change;
				newNodeR = allocateTreeNode(root->board, newPos);

				newNodeR->board[root->pos->row - 'A'][root->pos->col - '1'] = ' ';
				newNodeR->board[newNodeR->pos->row - 'A'][newNodeR->pos->col - '1'] = player;

				root->next_move[1] = newNodeR;
			}
		}
	}
}

// this function allocate and return a tree 
static SingleSourceMovesTree* allocateTree(Board board, checkersPos *pos)
{
	SingleSourceMovesTree* tree;


	tree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
	checkMalloc(tree);

	tree->source = allocateTreeNode(board, pos);

	return tree;
}

// this function allocate a treeNode, set the board and the checkerspos and the next_Moves to null 
static SingleSourceMovesTreeNode* allocateTreeNode(Board board, checkersPos *pos)
{
	SingleSourceMovesTreeNode* node;
	int i, j;

	node = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	checkMalloc(node);

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			node->board[i][j] = board[i][j];

		}
	}

	node->pos = pos;

	node->total_captures_so_far = 0;

	node->next_move[0] = NULL;
	node->next_move[1] = NULL;


	return node;
}
