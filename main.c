#include <stdio.h>
#include <stdlib.h>
#include "parsetools.h"
#include <string.h>
#include <sys/wait.h>


void arrcpy(char dest[][MAX_LINE_CHARS], char src[][MAX_LINE_CHARS], int length);

int main(int argc, char *argv[]) {
	char* filename;
    if (argc != 2) {/* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename\n", argv[0] );
		return 1;
	} else {
		filename = argc[1];
	}
	
	int** sudokuBoard = ParseFile(filename);

    return 0;
}
