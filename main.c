#include "definitions.h"
#include "moves.h"
#include "chessboard.h"
#include "pvc.h"
#include "./pieces/pieces.h"
#include <stdio.h>
#include <stdbool.h>

int main()
{
    printf(
    "   _______                  _             _    _____ _          \n"       
    "  |__   __|                (_)           | |  / ____| |         \n"
    "     | | ___ _ __ _ __ ___  _ _ __   __ _| | | |    | |__   ___  ___ ___ \n"
    "     | |/ _ \\ '__| '_ ` _ \\| | '_ \\ / _` | | | |    | '_ \\ / _ \\/ __/ __|\n"
    "     | |  __/ |  | | | | | | | | | | (_| | | | |____| | | |  __/\\__ \\__ \\ \n"
    "     |_|\\___|_|  |_| |_| |_|_|_| |_|\\__,_|_|  \\_____|_| |_|\\___||___/___/\n");
    printf("\n");
    printf("     https://github.com/Linusred/TerminalChess\n\n");

    printf("Select mode - 1: player vs player, 2: player vs computer: ");
    int mode;
    scanf("%d", &mode);
    if(mode == 2)
    {
        player_vs_computer();
        return 0;
    }
    printf("\n");

    enum{BLACK, WHITE};
    bool nextPlayer = WHITE;
    p pieces[NR_OF_PIECES];
    new_board(pieces);
    int winning_player;

    while(1)
    {
        nextPlayer = WHITE;
        new_board(pieces);
        bool game_over = false;
        while(!game_over)
        {
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
                    winning_player = BLACK;
                    break;
                }
                else if(n == 3){
                    game_over = true;
                    winning_player = WHITE;
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
        printf("\nCheckmate! %s wins!\n", winning_player ? "White" : "Black");

        printf("Play again? (Y/n): ");
        char playAgain;
        scanf(" %c", &playAgain);
        if(playAgain == 'Y')
            continue;
        else if(playAgain == 'n')
            break;
        else break;
    }

    return 0;
}