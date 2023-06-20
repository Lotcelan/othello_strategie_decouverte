#include "helpers.h"

int idx(int row, int col, board bd) {
    assert(row * bd.col_count + col < bd.col_count * bd.row_count);
    return row * bd.col_count + col;
}

int getBoardValue(int row, int col, board bd) {
    assert(row < bd.row_count);
    assert(col < bd.col_count);
    return bd.bd[idx(row, col, bd)];
}

int otherPlayer(int player) {
    switch (player)
    {
    case 1:
        return 2;
        break;
    case 2:
        return 1;
    default:
        break;
    }
}

board initBoard(int row_count, int col_count) {
    assert(row_count >= 2 && col_count >= 2 && row_count % 2 == 0 && col_count % 2 == 0);
    
    int* tab = (int*)malloc(sizeof(int) * row_count * col_count);
    assert(tab);


    board bd = { .bd = tab, .row_count = row_count, .col_count = col_count };

    bd.bd[idx(row_count / 2 - 1, col_count / 2 - 1, bd)] = 1;
    bd.bd[idx(row_count / 2, col_count / 2 - 1, bd)] = 2;
    bd.bd[idx(row_count / 2 - 1, col_count / 2, bd)] = 2;
    bd.bd[idx(row_count / 2, col_count / 2, bd)] = 1;



    return bd;
}

bool checkDirection(move m, board bd, int modifier_row, int modifier_col, bool modify_board) {

    // Returns wether or not the player doing the move m is going to "eat" its ennemies

    int row = m.row;
    int col = m.col;
    int iterations = 0;

    bool self_at_end = false;

    while ( (
                ( modifier_row > 0 && row < bd.row_count - 1) || (modifier_row < 0 && row > 0) || (modifier_row == 0)
            )
            && 
            (
                ( modifier_col > 0 && col < bd.col_count - 1) || (modifier_col <= 0 && col > 0) || (modifier_col == 0) 
            ) ) {
                
        row = row + modifier_row;
        col = col + modifier_col;

        if (getBoardValue(row, col, bd) == otherPlayer(m.player)) {
            iterations++;
        } else if (getBoardValue(row, col, bd) == m.player) {
            self_at_end = true;
            break;
        } else {
            break;
        }
    }

    bool result = iterations > 0 && self_at_end;
    if (result && modify_board) {
        int row = m.row;
        int col = m.col;
        
        bd.bd[idx(row,col,bd)] = m.player;

        while ( (
                ( modifier_row > 0 && row < bd.row_count - 1) || (modifier_row <= 0 && row > 0) || (modifier_row == 0)
            )
            && 
            (
                ( modifier_col > 0 && col < bd.col_count - 1) || (modifier_col <= 0 && col > 0) || (modifier_col == 0)
            ) ) {
            row = row + modifier_row;
            col = col + modifier_col;

            if (getBoardValue(row, col, bd) == otherPlayer(m.player)) {
                bd.bd[idx(row,col,bd)] = m.player;
            } else if (getBoardValue(row, col, bd) == m.player) {
                break;
            } else {
                break;
            }
        }
    }

    return result;
}



void updateBoard(move m, board bd) {
    // I suppose that m is a VALID MOVE for bd
    
    checkDirection(m, bd, 0, 1, true);
    checkDirection(m, bd, 1, 0, true);
    checkDirection(m, bd, 1, 1, true);
    checkDirection(m, bd, 0, -1, true);
    checkDirection(m, bd, -1, 0, true);
    checkDirection(m, bd, -1, -1, true);
    checkDirection(m, bd, 1, -1, true);
    checkDirection(m, bd, -1, 1, true);
    checkDirection(m, bd, -1, 1, true);
}
