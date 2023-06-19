#ifndef UTILSH
#define UTILSH

#include <stdlib.h>
#include <stdio.h>
#include "assert.h"

typedef int bool;
#define true 1
#define false 0

typedef struct move {
    int row;
    int col;
    int player;
} move;

typedef struct board {
    int row_count;
    int col_count;
    int* bd; // Tab of row_count * col_count elements, 0 means no player, then i means that the cell belongs to the ith player
} board;

#include "helpers.h"

#endif