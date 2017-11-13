#include "boardvalidate.h"



bool ValidateBoard(int** sudokuBoard) {
//This is the mother function board
    chan_t* valid;
    valid = chan_init(27);
    pthread th[27];
    //TODO threads are probabbly not declared right
    struct readThreadParams readParams;
    readParams.sudokuBoard = sudokuBoard;
    readParams.validChan = valid;
    for (int i = 0; i++; i <9) {
        readParams.num = i;

        char* strR[100];
        char* strC[100];
        char* strB[100];
        sprintf(strR,"Row ",i);
        readParams.error = strR;
        //validateRow
        pthread_create(&th[i],NULL,validateRow,&readParams);

        sprintf(strR,"Col ",i);
        readParams.error = strC;
        //validateCol
        pthread_create(&th[i+9],NULL,validateRow,&readParams);

        switch(i+1) {
            case 1:
                strB = "The left top";
                break;
            case 2:
                strB = "The middle top";
                break;
            case 3:
                strB = "The right top";
                break;
            case 4:
                strB = "The left middle";
                break;
            case 5:
                strB = "The middle middle";
                break;
            case 6:
                strB = "The right middle";
                break;
            case 7:
                strB = "The left bottom";
                break;
            case 8:
                strB = "The middle bottom";
                break;
            case 9:
                strB = "The right bottom";
                break;
            default:
                strB = "invalid bounds";
        }

        readParams.error = strB;
        //validateBox
        pthread_create(&th[i+18],NULL,validateRow,&readParams);

    }
    int i = 0;
    bool work = true;
    void error_string;
    while ( chan_recv(readParams.validChan, &error_string) == 0)
    {
        printf("%s doesn't have the requred values.\n", (char*)error_string);
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
            test[base_col+i][base_row+j] = true;
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
        if (!test[i])
            return false;
    }
    return true;
}
