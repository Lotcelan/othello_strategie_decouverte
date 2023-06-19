#include "display.h"

void showBoard(board bd) {
    for (int i = 0; i < bd.col_count; i++) {
            printf("----");
        }
        printf("\n");
    for (int row = 0; row < bd.row_count; row++) {
        printf("|");
        for (int col = 0; col < bd.col_count; col++) {
            int value = getBoardValue(row, col, bd);

            if (value != 0) {
                printf(" %i |", value);
            } else {
                printf("   |");
            }

        }
        printf("\n");
        for (int i = 0; i < bd.col_count; i++) {
            printf("----");
        }
        printf("\n");
    }

    printf("\n");
}