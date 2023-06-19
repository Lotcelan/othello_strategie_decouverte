#include "main.h"

int main(int argc, char* argv[]) {

    /*
        First argument : {0, 1}
            - 0 : Player vs AI
            - 1 : AI vs AI

    */
   
    int row_count = 8;
    int col_count = 8;

    bool onlyAI = 0;

    if (argc > 1) {
        onlyAI = (bool)atoi(argv[1]);
    }

    runGame(onlyAI, row_count, col_count);

    return 0;
}