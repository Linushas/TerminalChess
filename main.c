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
        print_chessboard(pieces);
        if(visible_to_pawn(pieces, pieces[WPAWN4], pieces[BKING].x, pieces[BKING].y) == 1)
            printf("visible!\n");
        printf("%s's turn! Enter move: ", nextPlayer ? "White" : "Black");
        while(1)
        {
            move m = getMove(pieces);
            int n = executeMove(m, pieces, nextPlayer);
            if(n == 1)
                break;
            else if(n == 2){
                game_over = true;
                break;
            }
            else printf("Illegal move! Try again: ");
        }
        nextPlayer = nextPlayer ? BLACK : WHITE;
    }

    return 0;
}