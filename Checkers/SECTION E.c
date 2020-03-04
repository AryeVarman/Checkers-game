
#include "Main Header.h"

/***  IMTLEMENTS  ***/

// this function convert the board data to short int and store it on a binary file
void StoreBoard(Board board, char * filename)
{
	unsigned short int arr[8] = { 0 };
	unsigned short int mask_T = 0x4000;
	unsigned short int mask_B = 0x8000;
	FILE* file;
	int i, j;

	for (i = 0; i < BOARD_SIZE; i++)
	{

		for (j = 0, mask_T = 0x4000, mask_B = 0x8000; j < BOARD_SIZE; j++, mask_B = mask_B >> 2, mask_T = mask_T >> 2)
		{
			if (board[i][j] == 'T')
				arr[i] = arr[i] | mask_T;

			if (board[i][j] == 'B')
				arr[i] = arr[i] | mask_B;
		}

	}

	file = fopen(filename, "wb");
	checkFile(file);

	fwrite(arr, sizeof(unsigned short int), 8, file);

	fclose(file);
}
