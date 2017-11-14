#include "boardvalidate.h"

bool ValidateBoard(int** sudokuBoard) {
//This is the mother function board
    chan_t* valid;
    valid = chan_init(27);
    pthread_t th[27];
    //TODO threads are probabbly not declared right
    struct readThreadParams readParams;
    readParams.sudokuBoard = sudokuBoard;
    readParams.validChan = valid;
    for (int i = 0; i++; i <9) {
        readParams.num = i;

        char strR[100];
        char strC[100];
        char strB[100];
        sprintf(strR,"Row ",i);
        readParams.error = strR;
        //validateRow
        pthread_create(&th[i],NULL,validateRow,&readParams);

        sprintf(strR,"Col ",i);
        readParams.error = strC;
        //validateCol
        pthread_create(&th[i+9],NULL,validateRow,&readParams);
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

        readParams.error = strB;
        //validateBox
        pthread_create(&th[i+18],NULL,validateRow,&readParams);

    }
    int i = 0;
    bool work = true;
    void* error_string;
    while ( chan_recv(readParams.validChan, &error_string) == 0)
    {
        printf("%s doesn't have the requred values.\n", error_string);
        i++;
        if (i >= 27){
            work = false;
            break;
        }
    }
    //TODO join threads, check for errors
    return work;

}

void* validateRow(void* params) {
	struct readThreadParams *params1 = params;
    //create a bool array for comparison
    bool test[9] = { false };

    for (int i = 0; i < 9; i++){
        //check board[i][num]
        test[params1->sudokuBoard[i][params1->num]] = true;
    }

    //check for valid
    bool isValid = testArray(test);
    //if not valid tell the main the error, otherwise tell it null.
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
        test[params1->sudokuBoard[params1->num][j]] = true;
    }

    //check for valid
    bool isValid = testArray(test);
    //if not valid tell the main the error, otherwise tell it null.
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
    int base_row = params1->num / 3;
    int base_col = params1->num % 3;
    for ( int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            test[params1->sudokuBoard[base_col+i][base_row+j]] = true;
        }
    }

    //check for valid
    bool isValid = testArray(test);
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
