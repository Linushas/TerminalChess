#include "definitions.h"
#include "moves.h"
#include "chessboard.h"
#include "./pieces/pieces.h"
#include <stdio.h>
#include <stdbool.h>

int main()
{
    enum{BLACK, WHITE};
    bool nextPlayer = WHITE;
    p pieces[NR_OF_PIECES];
    new_board(pieces);

    bool game_over = false;
    while(!game_over)
    {
        //print_chessboard(pieces);
        print_chessboard_v2(pieces, false, nextPlayer);
        printf("                           *   > ");
        while(1)
        {
            move m = getMove(pieces, nextPlayer);
            int n = executeMove(m, pieces, nextPlayer);
            if(n == 1)
                break;
            else if(n == 2){
                game_over = true;
                break;
            }
            else 
            {
                print_chessboard_v2(pieces, true, nextPlayer);
                printf("                           *   > ");
            }
        }
        nextPlayer = nextPlayer ? BLACK : WHITE;
    }

    return 0;
}