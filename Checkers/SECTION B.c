
#include "Main Header.h"



/*** PROTOTYPES ***/


static SingleSourceMovesList* createSingleSourceEmptyList();

static SingleSourceMovesTreeNode* FindOptimalRoot(SingleSourceMovesTreeNode* root, SingleSourceMovesTreeNode* maxCaptureNode);

static void buildOptimalRootList(SingleSourceMovesTreeNode* root, SingleSourceMovesTreeNode* maxCapureNode,
	SingleSourceMovesList* list, char *isFound);

static SingleSourceMovesListCell* createSingleSourceListCell(checkersPos* pos, short Capures, SingleSourceMovesListCell* next);

static void free_tree(SingleSourceMovesTree* tree);

static void free_treeAux(SingleSourceMovesTreeNode* root);



/*** IMPLEMENTS ***/


// this function gets a binary tree of all tool's move option and create's and return a list that contain the tool's optimal route
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree * moves_tree)
{
	SingleSourceMovesTreeNode* maxCaptureNode = NULL;
	SingleSourceMovesList* list = createSingleSourceEmptyList();

	char isFound = 0;


	if (moves_tree->source->next_move[0] == NULL && moves_tree->source->next_move[1] == NULL)
	{
		return NULL;
	}


	maxCaptureNode = FindOptimalRoot(moves_tree->source, maxCaptureNode);

	buildOptimalRootList(moves_tree->source, maxCaptureNode, list, &isFound);

	free_tree(moves_tree);

	return list;
}

// this function find the treenode that is located at the end of the optimal route based on maximal captures possible
SingleSourceMovesTreeNode* FindOptimalRoot(SingleSourceMovesTreeNode* root, SingleSourceMovesTreeNode* maxCaptureNode)
{

	if (!root->next_move[0] && !root->next_move[1])
	{
		if (maxCaptureNode == NULL)
			maxCaptureNode = root;

		else {
			if (maxCaptureNode->total_captures_so_far < root->total_captures_so_far)
				maxCaptureNode = root;
		}
	}

	else
	{
		if (root->next_move[0])
			maxCaptureNode = FindOptimalRoot(root->next_move[0], maxCaptureNode);

		if (root->next_move[1])
			maxCaptureNode = FindOptimalRoot(root->next_move[1], maxCaptureNode);

	}
	return maxCaptureNode;
}

// this function get's the last node in the optimal route and create the list of the route that start whith the tool's position and end whith said node
void buildOptimalRootList(SingleSourceMovesTreeNode* root, SingleSourceMovesTreeNode* maxCapureNode,
	SingleSourceMovesList* list, char *isFound)
{

	SingleSourceMovesListCell* temp;

	if (root == maxCapureNode) {
		*isFound = 1;
		list->head = list->tail = createSingleSourceListCell(root->pos, root->total_captures_so_far, NULL);
		return;
	}

	else
	{
		if (root->next_move[0])
			buildOptimalRootList(root->next_move[0], maxCapureNode, list, isFound);

		if (*isFound)
		{
			temp = list->head;
			list->head = createSingleSourceListCell(root->pos, root->total_captures_so_far, temp);
			return;
		}

		if (root->next_move[1])
			buildOptimalRootList(root->next_move[1], maxCapureNode, list, isFound);

		if (*isFound)
		{
			temp = list->head;
			list->head = createSingleSourceListCell(root->pos, root->total_captures_so_far, temp);
			return;
		}

	}
}

// this function create's a cell for the single source optimal list
SingleSourceMovesListCell * createSingleSourceListCell(checkersPos * pos, short Capures, SingleSourceMovesListCell * next)
{

	SingleSourceMovesListCell *cell;
	cell = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	checkMalloc(cell);

	cell->position = createPos();

	cell->position->row = pos->row;
	cell->position->col = pos->col;

	cell->captures = Capures;

	cell->next = next;


	return cell;
}

// this function create's a single source empty list
SingleSourceMovesList * createSingleSourceEmptyList()
{
	SingleSourceMovesList* list;

	list = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkMalloc(list);

	list->head = NULL;
	list->tail = NULL;

	return list;
}

// this function free's the tree that contain all of the possible route for a single tool
static void free_tree(SingleSourceMovesTree* tree)
{

	if (tree->source)
	{
		free_treeAux(tree->source);
	}
	free(tree);
}

// this function is an auxillary function for " free_tree"
static void free_treeAux(SingleSourceMovesTreeNode* root)
{
	if (!root->next_move[0] && !root->next_move[1])
	{
		free(root->pos);
		free(root);
		return;
	}

	if (root->next_move[0])
		free_treeAux(root->next_move[0]);


	if (root->next_move[1])
		free_treeAux(root->next_move[1]);

	free(root);
}