//
// Created by Jeffrey  Booher-Kaeding on 11/12/17.
//

#ifndef CS450_HW3_BOARDVALIDATE_H
#define CS450_HW3_BOARDVALIDATE_H

// Struct for thread params
// https://stackoverflow.com/a/16230944/4730779
struct readThreadParams {
    int** sudokuBoard;
    int num;
    chan_t* validChan
    ;
    char* error;
};
bool ValidateBoard(int** sudokuBoard);

void* validateRow(void* params);

void* validateCol(void* params);

void* validateBox(void* params);

bool testArray(bool* test);

#endif //CS450_HW3_BOARDVALIDATE_H
