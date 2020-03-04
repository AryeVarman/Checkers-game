
#include "Main Header.h"

// this function reads a short int from a binary file and set the board based on the data on the file 
void LoadBoard(char* filename, Board board)
{
	int row = 0, col, move;
	unsigned short line;
	unsigned short res;
	unsigned short mask = 0xc000;
	FILE* fptr;

	fptr = fopen(filename, "rb");
	checkFile(fptr);

	while (!feof(fptr))
	{
		fread(&line, sizeof(unsigned short), 1, fptr);
		for (col = 0; col < BOARD_SIZE; col++)
		{
			if ((line & mask) == 0)
				board[row][col] = ' ';
			else
			{
				move = col * 2 + 1;
				res = (line & mask);
				res = res << move;
				if (res == 0)
					board[row][col] = 'B';
				else
					board[row][col] = 'T';
			}
			mask = mask >> 2;
		}
		row++;
		mask = 0xc000;
	}

	fclose(fptr);
}