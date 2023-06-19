#ifndef STRATEGYH
#define STRATEGYH

#include "utils.h"

move minMaxHeuristic(int player, board bd, int max_depth);
bool moveIsPossible(move m, board bd);
bool isEndingState(board bd);
bool isPlayerWinning(int player, board bd);
int getScore(board bd);

typedef struct move_size {
    move* tab;
    int size;
} move_size;

#endif