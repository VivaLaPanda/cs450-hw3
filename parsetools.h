#ifndef PARSE_H
#define PARSE_H

char** str_split(char* a_str, char a_delim);
void ParseFile(char* filename, int sudokuBoard[9][9]);

#endif