//
// Created by Jeffrey  Booher-Kaeding on 11/12/17.
//

#ifndef CS450_HW3_BOARDVALIDATE_H
#define CS450_HW3_BOARDVALIDATE_H

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "chan.h"
// Struct for thread params
// https://stackoverflow.com/a/16230944/4730779
struct readThreadParams {
    int (*sudokuBoard)[9];
    int num;
    chan_t* validChan
    ;
    char* error;
};
bool ValidateBoard(int sudokuBoard[9][9]);

void* validateRow(void* params);

void* validateCol(void* params);

void* validateBox(void* params);

bool testArray(bool* test);

#endif //CS450_HW3_BOARDVALIDATE_H
