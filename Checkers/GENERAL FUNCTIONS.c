
#include "Main Header.h"


// this function checks if a malloc went well
void checkMalloc(void * po)
{
	if (po == 0) {
		printf("ERROR");
		exit(MALLOC_ERROR);
	}
}

// this function checks if fopen went well
void checkFile(void * po)
{
	if (po == 0) {
		printf("ERROR");
		exit(FILE_ERROR);
	}
}

// this function allocate a checkerpos and set it to zero
checkersPos* createPos()
{
	checkersPos* pos;

	pos = (checkersPos*)malloc(sizeof(checkersPos));
	checkMalloc(pos);

	pos->col = 0;
	pos->row = 0;

	return pos;
}

// this function set the rival to B or T based on the player and set the change to 1 or -1
void UpDatePlayerRivalChange(char* change, char player, char* rival)
{
	if (player == 'B')
	{
		*rival = 'T';
		*change = 1;
	}
	else if (player == 'T')
	{
		*rival = 'B';
		*change = -1;
	}
}