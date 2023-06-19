#ifndef HELPERSH
#define HELPERSH

#include "utils.h"

int idx(int row, int col, board bd);
int getBoardValue(int row, int col, board bd);
int otherPlayer(int player);
board initBoard(int row_count, int col_count);
void updateBoard(move m, board bd);
bool checkDirection(move m, board bd, int modifier_row, int modifier_col, bool modify_board);

#endif