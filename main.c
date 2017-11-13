#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "parsetools.h"
#include "boardvalidate.h"


int main(int argc, char *argv[]) {
	char* filename;
    if (argc != 2) {/* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename\n", argv[0] );
		return 1;
	} else {
		filename = argc[1];
	}
	
	int** sudokuBoard = ParseFile(filename);
	bool result = ValidateBoard(sudokuBoard);
	if (!result){
		printf( " The input is not a valid Sudoku");
	}
	else{
		printf(" You did it kiddo, you valid Sudoku");
	}
    return 0;
}
