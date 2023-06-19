#include "strategy.h"

bool moveIsPossible(move m, board bd) {
    if (m.col >= bd.col_count || m.col < 0) { return false; }
    if (m.row >= bd.row_count || m.row < 0) { return false; }

    if (getBoardValue(m.row, m.col, bd) != 0) { return false; };

    bool result =  checkDirection(m, bd, 0, 1, false)
                || checkDirection(m, bd, 1, 0, false)
                || checkDirection(m, bd, 1, 1, false)
                || checkDirection(m, bd, 0, -1, false)
                || checkDirection(m, bd, -1, 0, false)
                || checkDirection(m, bd, -1, -1, false)
                || checkDirection(m, bd, 1, -1, false)
                || checkDirection(m, bd, -1, 1, false);


    return result;
}

move_size getPossibleMoves(int turn, board bd) {
    // Returns an array of possible moves and its length
    int size = 0;
    for (int row = 0; row < bd.row_count; row++) {
        for (int col = 0;  col < bd.col_count; col++) {
            move temp_move = { .col = col, .row = row, .player = turn };
            if (moveIsPossible(temp_move, bd)) {
                size++;
            }
        }
    }

    int tracker = 0;
    move* tab = (move*)malloc(sizeof(move) * size);
    assert(tab);

    for (int row = 0; row < bd.row_count; row++) {
        for (int col = 0;  col < bd.col_count; col++) {
            move temp_move = { .col = col, .row = row, .player = turn };
            if (moveIsPossible(temp_move, bd)) {
                tab[tracker] = temp_move;
                tracker++;
            }
        }
    }
    
    move_size result = { .size = size, .tab = tab };
    return result;

}

bool isEndingState(board bd) {
    return ((getPossibleMoves(1, bd).size == 0) && (getPossibleMoves(2, bd).size == 0));
}

int getScore(board bd) {
    int player_one_count = 0;
    int player_two_count = 0;

    for (int row = 0; row < bd.row_count; row++) {
        for (int col = 0;  col < bd.col_count; col++) {
            if (getBoardValue(row, col, bd) == 1) {
                player_one_count++;
            } else if (getBoardValue(row, col, bd) == 2) {
                player_two_count++;
            }
        }
    }

    if (isEndingState(bd)) {
        if (player_one_count > player_two_count) {
            return 1000;
        } else if (player_one_count < player_two_count) {
            return -1000;
        } else {
            return 0;
        }
    } else {
        if (player_one_count > player_two_count) {
            return 10;
        } else if (player_one_count < player_two_count) {
            return -10;
        } else {
            return 0;
        }
    }
}

int getScoreFromHeuristic(board bd) {
    return getScore(bd);
}

int _exploreMinMaxH(int current_depth, int turn, int player, board bd, int max_depth) {
    /*
        turn : player to play during this round of recursive call
        player : player I am trying to find the best score for
    */

    board temp = initBoard(bd.row_count,  bd.col_count);
    for (int i = 0; i < bd.row_count; i++) {
        for (int j = 0; j < bd.col_count; j++) {
            temp.bd[idx(i,j,bd)] = getBoardValue(i,j,bd);
        }
    }


    if (isEndingState(bd)) {

        return getScore(bd);
    } else if (current_depth >= max_depth) {

        return getScoreFromHeuristic(bd);
    } else {
        
        move_size possible_moves = getPossibleMoves(turn, bd);

        if (possible_moves.size == 0) {
            return 0;
        } else {
            int* scores = (int*)malloc(sizeof(int) * possible_moves.size);
            assert(scores);

            for (int i = 0; i < possible_moves.size; i++) {
                updateBoard(possible_moves.tab[i], temp);
                
                scores[i] = _exploreMinMaxH(current_depth + 1, otherPlayer(turn), player, temp, max_depth);

                move reset_move = { .col = possible_moves.tab[i].col, .row = possible_moves.tab[i].row, .player = 0 };
                updateBoard(reset_move, temp);

            }

            free(temp.bd);

            if (turn == player) {
                // We look for the best move, so the max of the scores
                int max_idx = 0;
                int max_score = scores[0];

                for (int i = 1; i < possible_moves.size; i++) {
                    if (scores[i] > max_score) {
                        max_idx = i;
                        max_score = scores[i];
                    }
                }

                return max_score;

            } else {
                // The other player is playing and we want assume that he's choosing the best score for him, so we look for the min
                int min_idx = 0;
                int min_score = scores[0];

                for (int i = 1; i < possible_moves.size; i++) {
                    if (scores[i] > min_score) {
                        min_idx = i;
                        min_score = scores[i];
                    }
                }

                return min_score;
            }
        }
    }
}

move minMaxHeuristic(int player, board bd, int max_depth) {

    board temp = initBoard(bd.row_count,  bd.col_count);
    for (int i = 0; i < bd.row_count; i++) {
        for (int j = 0; j < bd.col_count; j++) {
            temp.bd[idx(i,j,bd)] = getBoardValue(i,j,bd);
        }
    }


    move_size possible_moves = getPossibleMoves(player, bd);

    if (possible_moves.size == 0) {
        printf("Pas possible");
        exit(-1);
    } else {
        int* scores = (int*)malloc(sizeof(int) * possible_moves.size);
        assert(scores);


        for (int i = 0; i < possible_moves.size; i++) {
            updateBoard(possible_moves.tab[i], temp);
            
            scores[i] = _exploreMinMaxH(1, otherPlayer(player), player, temp, max_depth);

            move reset_move = { .col = possible_moves.tab[i].col, .row = possible_moves.tab[i].row, .player = 0 };
            updateBoard(reset_move, temp);

        }

        free(temp.bd);

        int max_idx = 0;
        int max_score = scores[0];

        for (int i = 1; i < possible_moves.size; i++) {
            if (scores[i] > max_score) {
                max_idx = i;
                max_score = scores[i];
            }
        }

        return possible_moves.tab[max_idx];

        
    }

}
