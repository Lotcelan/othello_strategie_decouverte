#include "game.h"


move choseMove(int player, board bd) {
    return minMaxHeuristic(player, bd, 6);
}

void runGame(bool onlyAI, int row_count, int col_count) {
    bool should_close = false;
    bool move_chosen = false;

    move player_one_move = { .col = 0, .row = 0, .player = 1 };
    move player_two_move = { .col = 0, .row = 0, .player = 2 };

    board bd = initBoard(row_count, col_count);

    showBoard(bd, true);

    while (!should_close) {
        
        /* PLAYER ONE PLAYING */

        if (canPlayerMove(1, bd)) {

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
        } else {
            continue;
        }
        showBoard(bd, false);


        /* PLAYER TWO PLAYING */


        if (canPlayerMove(2, bd)) {
            player_two_move = choseMove(2, bd);
            updateBoard(player_two_move, bd);
        }
        showBoard(bd, false);

        /* ENDING TURN */
        if (isEndingState(bd)) {
            if (isPlayerWinning(1, bd)) {
                printf("Player 1 won !\n");
            } else if (isPlayerWinning(2, bd)) {
                printf("Player 2 won !\n");
            }
            should_close = true;
        }
    }
}