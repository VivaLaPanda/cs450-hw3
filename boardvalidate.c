#include "boardvalidate.h"

bool ValidateBoard(int sudokuBoard[9][9]) {
//This is the mother function board
    chan_t* valid;
    valid = chan_init(27);
    pthread_t th[27];
    //TODO threads are probabbly not declared right
	printf("Summoning workers\n");
    for (int i=0; i<9; i++) {
        char* strR = malloc(100);
        char* strC = malloc(100);
        char* strB = malloc(100);
        sprintf(strR,"Row %d",i);
		
		struct readThreadParams* readParams = malloc(sizeof(struct readThreadParams));
		(*readParams).sudokuBoard = sudokuBoard;
		(*readParams).validChan = valid;
        (*readParams).num = i;
        (*readParams).error = strR;
        //validateRow
        pthread_create(&th[i],NULL,validateRow,readParams);

        sprintf(strC,"Col %d",i);
		readParams = malloc(sizeof(struct readThreadParams));
		(*readParams).sudokuBoard = sudokuBoard;
		(*readParams).validChan = valid;
        (*readParams).num = i;
        (*readParams).error = strC;
        //validateCol
        pthread_create(&th[i+9],NULL,validateCol,readParams);
		char *tmp;
        switch(i+1) {
            case 1:
				tmp = "The left top";
                strcpy(strB, tmp);
                break;
            case 2:
                tmp = "The middle top";
                strcpy(strB, tmp);
                break;
            case 3:
                tmp = "The right top";
                strcpy(strB, tmp);
                break;
            case 4:
                tmp = "The left middle";
                strcpy(strB, tmp);
                break;
            case 5:
                tmp = "The middle middle";
                strcpy(strB, tmp);
                break;
            case 6:
                tmp = "The right middle";
                strcpy(strB, tmp);
                break;
            case 7:
                tmp = "The left bottom";
                strcpy(strB, tmp);
                break;
            case 8:
                tmp = "The middle bottom";
                strcpy(strB, tmp);
                break;
            case 9:
                tmp = "The right bottom";
                strcpy(strB, tmp);
                break;
            default:
                tmp = "invalid bounds";
                strcpy(strB, tmp);
        }

		readParams = malloc(sizeof(struct readThreadParams));
		(*readParams).sudokuBoard = sudokuBoard;
		(*readParams).validChan = valid;
        (*readParams).num = i;
        (*readParams).error = strB;
        //validateBox
        pthread_create(&th[i+18],NULL,validateBox,readParams);

    }
    int i = 0;
    bool work = true;
    void* error_string;
    while ( chan_recv(valid, &error_string) == 0)
    {
        if (error_string != NULL) {
            printf("%s doesn't have the requred values.\n", error_string);
            work = false;
        }
        i++;
        if (i >= 27){
            break;
        }
    }
    return work;

}

void* validateRow(void* params) {
	struct readThreadParams *params1 = params;
    //create a bool array for comparison
    bool test[9] = { false };

    for (int i = 0; i < 9; i++){
        //check board[i][num]
        test[params1->sudokuBoard[i][params1->num]-1] = true;
    }

    //check for valid
    bool isValid = testArray(test);
    //if not valid tell the main the error, otherwise tell it null.
	//printf("Checked row %d\n", params1->num);
    if (!isValid) {
        chan_send(params1->validChan, params1->error);
    }
    else {
        chan_send(params1->validChan, NULL);
    }
}



void* validateCol(void* params) {
    struct readThreadParams *params1 = params;
    //create a bool array for comparison
    bool test[9] = { false };

    for (int j = 0; j < 9; j++){
        //check board[n][i]
        test[params1->sudokuBoard[params1->num][j]-1] = true;
    }

    //check for valid
    bool isValid = testArray(test);
    //if not valid tell the main the error, otherwise tell it null.
	//printf("Checked col %d\n", params1->num);
    if (!isValid) {
        chan_send(params1->validChan, params1->error);
    }
    else {
        chan_send(params1->validChan, NULL);
    }

}


void* validateBox(void* params) {
    struct readThreadParams *params1 = params;
    //create a bool array for comparison
    bool test[9] = {false};
    int base_row = 3*(params1->num / 3);
    int base_col = 3*(params1->num % 3);
    for ( int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            //printf("%d %d \n",base_col,base_row);
            test[(params1->sudokuBoard[base_col+i][base_row+j])-1] = true;
        }
    }

    //check for valid
    bool isValid = testArray(test);
	//printf("Checked box %d,%d\n", base_row, base_col);
    //if not valid tell the main the error, otherwise tell it null.
    if (!isValid) {
        chan_send(params1->validChan, params1->error);
    }
    else {
        chan_send(params1->validChan, NULL);
    }
}

bool testArray(bool* test) {

    //look for any cases where a number isn't present
    for (int k = 0; k < 9; k++) {
        if (!test[k])
            return false;
    }
    return true;
}
