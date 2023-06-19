#include "game.h"


move choseMove(int player, board bd) {
    return minMaxHeuristic(player, bd, 1);
}

void runGame(bool onlyAI, int row_count, int col_count) {
    bool should_close = false;
    bool move_chosen = false;

    move player_one_move = { .col = 0, .row = 0, .player = 1 };
    move player_two_move = { .col = 0, .row = 0, .player = 2 };

    board bd = initBoard(row_count, col_count);

    showBoard(bd);

    while (!should_close) {
        
        /* PLAYER ONE PLAYING */

        // Make the player chose his next move, if player there is
        if (!onlyAI) {
            move_chosen = false;

            while (!move_chosen) {
                int user_row, user_col;

                printf("Provide a row : ");
                scanf("%i"   , &user_row);
                printf(", and a column : ");
                scanf("%i", &user_col);
                printf("\n");

                player_one_move.row = user_row;
                player_one_move.col = user_col;

                if (!moveIsPossible(player_one_move, bd)) {
                    printf("Invalid move\n");
                } else {
                    move_chosen = true;
                }
            }
        }
        // Or else let the AI decide
        else {
            player_one_move = choseMove(1, bd);
        }

        // Update the board accordingly
        updateBoard(player_one_move, bd);

        /* PLAYER TWO PLAYING */

        player_two_move = choseMove(2, bd);
        updateBoard(player_two_move, bd);

        /* DISPLAYING */

        showBoard(bd);

        /* ENDING TURN */

        if (isEndingState(bd)) {
            should_close = true;
        }

    }
}