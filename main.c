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
		filename = argv[1];
	}
	
	int sudokuBoard[9][9];
	ParseFile(filename, sudokuBoard); // Parsefile stores result in sudokuboard
	bool result = ValidateBoard(sudokuBoard);
	if (!result){
		printf( " The input is not a valid Sudoku\n");
	}
	else{
		printf(" You did it kiddo, you valid Sudoku\n");
	}
    return 0;
}
