#include <stdio.h>
#include <pthread.h>
#include "chan.h"
#include "boardvalidate.h"



void ValidateBoard(int** sudokuBoard) {
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
        //TODO pass the error msgs, figure out how to pass box locations

        readParams.error = "";
        //validateRow
        pthread_create(&th[i],NULL,validateRow,&readParams);

        readParams.error = "";
        //validateCol
        pthread_create(&th[i+9],NULL,validateRow,&readParams);

        readParams.error = "";
        //validateBox
        pthread_create(&th[i+18],NULL,validateRow,&readParams);

    }
    //TODO join threads, check for errors
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
    if (!isValid)
            chan_send(params1->validChan, params1->error);
    else
        chan_send(params1->validChan, NULL);
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
    if (!isValid)
        chan_send(params1->validChan, params1->error);
    else
        chan_send(params1->validChan, NULL);

}


void* validateBox(void* params) {
    struct readThreadParams *params1 = params;
    //create a bool array for comparison
    bool test[9] = {false};

    for (int i = 0; i < 9; i++) {
    //TODO write logic to check the given box.
    }

    //check for valid
    bool isValid = testArray(test);
    //if not valid tell the main the error, otherwise tell it null.
    if (!isValid)
        chan_send(params1->validChan, params1->error);
    else
        chan_send(params1->validChan, NULL);

}

bool testArray(bool* test) {

    //look for any cases where a number isn't present
    for (int k = 0; k < 9; k++) {
        if (!test[i])
            return false;
    }
    return true;
}
