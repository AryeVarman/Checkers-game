#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// SECTION A //


						/*** DEFINE ***/

#define BOARD_SIZE 8
#define MALLOC_ERROR -1
#define FILE_ERROR -2
#define  DRAW -3
						/*** TYPEDEF ***/

typedef struct _checkersPos {
	char row, col;
}checkersPos;

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef unsigned char Player;

typedef struct _SingleSourceMovesTreeNode {
	Board board;
	checkersPos *pos;
	unsigned short total_captures_so_far;
	struct _SingleSourceMovesTreeNode *next_move[2];
}SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree {
	SingleSourceMovesTreeNode *source;
}SingleSourceMovesTree;



/***  PROTOTYPES  ***/

SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos *src);




// SECTION B //

						/*** TYPEDEF ***/

typedef struct _SingleSourceMovesListCell {
	checkersPos *position;
	unsigned short captures;
	struct _SingleSourceMovesListCell *next;
}SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList {
	SingleSourceMovesListCell *head;
	SingleSourceMovesListCell *tail;
}SingleSourceMovesList;


/*** PROTOTYPES ***/

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree);




// SECTION C //

						/*** TYPEDEF ***/

typedef struct _MultipleSourceMovesListCell {
	SingleSourceMovesList *single_source_moves_list;
	struct _MultipleSourceMovesListCell *next;
}MultipleSourceMovesListCell;

typedef struct _MultipleSourceMovesList {
	MultipleSourceMovesListCell *head;
	MultipleSourceMovesListCell *tail;
}MultipleSourceMovesList;


/*** PROTOTYPES ***/

MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player);



// SECTION D //

					/*** PROTOTYPES ***/

void Turn(Board board, Player player);



// SECTION E //

					/*** PROTOTYPES ***/

void StoreBoard(Board board, char * filename);




// SECTION F //

					/*** PROTOTYPES ***/

void LoadBoard(char* filename, Board board);



// SECTION G //

					/*** PROTOTYPES ***/

void PlayGame(Board board, Player starting_Player);









/*** PROTOTYPES ***/


void checkMalloc(void * po);
void checkFile(void * po);
checkersPos* createPos();
void UpDatePlayerRivalChange(char* change, char player, char* rival);