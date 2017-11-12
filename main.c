#include <stdio.h>
#include <stdlib.h>
#include "parsetools.h"
#include <string.h>
#include <sys/wait.h>

void arrcpy(char dest[][MAX_LINE_CHARS], char src[][MAX_LINE_CHARS], int length);

int main() {
    

    return 0;
}

void arrcpy(char dest[][MAX_LINE_CHARS], char src[][MAX_LINE_CHARS], int length) {
	for (int i = 0; i < length; i++) {
		strcpy(dest[i], src[i]);
	}
	
	return;
}
