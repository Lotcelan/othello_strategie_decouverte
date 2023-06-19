#include "display.h"

void showBoard(board bd, bool first_iteration) {
    if (!first_iteration) {
        printf("\033[%iA\r", bd.row_count * 2 + 2);

    }
    
    for (int i = 0; i < bd.col_count; i++) {
            printf("----");
        }
        printf("\n");
    for (int row = 0; row < bd.row_count; row++) {
        printf("|");
        for (int col = 0; col < bd.col_count; col++) {
            int value = getBoardValue(row, col, bd);

            if (value != 0) {
                printf(" \033[%i;%im \033[0m |", (value == 1) ? 47 : ((value == 2) ? 41 : 40), (value == 1) ? 47 : ((value == 2) ? 41 : 40) );
            } else {
                printf("   |");
            }

        }
        printf("\033[0m\n");
        for (int i = 0; i < bd.col_count; i++) {
            printf("----");
        }
        printf("\n");
    }
    printf("\n");

}