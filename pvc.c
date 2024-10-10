#include "pvc.h"
#include "definitions.h"
#include "moves.h"
#include "chessboard.h"
#include "./pieces/pieces.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void player_vs_computer(void)
{
    printf("\n");

    enum{BLACK, WHITE};
    bool nextPlayer = WHITE;
    p pieces[NR_OF_PIECES];
    new_board(pieces);
    int winning_player;
    srand(time(NULL));

    while(1)
    {
        nextPlayer = WHITE;
        new_board(pieces);
        bool game_over = false;
        while(!game_over)
        {
            if(nextPlayer)
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
            }
            else
                random_move(pieces);
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

    return;
}

void random_move(p pieces[])
{
    int board[BOARD_SIZE][BOARD_SIZE];
    getBoard(pieces, board);
    int piece;
    int x_arr[64], y_arr[64];
    int i = 0, x = 0, y = 0;

    while(i < 1)
    {
        move m;
        piece = rand()%16;
        m.piece = piece;
        m.start_x = pieces[piece].x;
        m.start_y = pieces[piece].y;
        m.move_type = DEFAULT;
        for(y = 0; y < BOARD_SIZE; y++)
        {
            for(x = 0; x < BOARD_SIZE; x++)
            {   
                m.dest_x = x;
                m.dest_y = y;
                if(validMove(m, pieces) && board[x][y] >= 16)
                {
                    x_arr[i] = x;
                    y_arr[i] = y;
                    i++;
                }
                /*
                switch(piece)
                {
                    case BPAWN1: case BPAWN2: case BPAWN3: case BPAWN4: case BPAWN5: case BPAWN6: case BPAWN7: case BPAWN8:
                        if(visible_to_pawn(pieces, pieces[piece], x, y) && board[x][y] >= 16)
                        {
                            x_arr[i] = x;
                            y_arr[i] = y;
                            i++;
                        }
                        break;
                    case BROOK1: case BROOK2:
                        if(visible_to_rook(pieces, pieces[piece], x, y) && board[x][y] >= 16)
                        {
                            x_arr[i] = x;
                            y_arr[i] = y;
                            i++;
                        }
                        break;
                    case BBISHOP1: case BBISHOP2:
                        if(visible_to_bishop(pieces, pieces[piece], x, y) && board[x][y] >= 16)
                        {
                            x_arr[i] = x;
                            y_arr[i] = y;
                            i++;
                        }
                        break;
                    case BKNIGHT1: case BKNIGHT2:
                        if(visible_to_knight(pieces, pieces[piece], x, y) && board[x][y] >= 16)
                        {
                            x_arr[i] = x;
                            y_arr[i] = y;
                            i++;
                        }
                        break;
                    case BKING:
                        if(visible_to_king(pieces, pieces[piece], x, y) && board[x][y] >= 16)
                        {
                            x_arr[i] = x;
                            y_arr[i] = y;
                            i++;
                        }
                        break;
                    case BQUEEN:
                        if(visible_to_queen(pieces, pieces[piece], x, y) && board[x][y] >= 16)
                        {
                            x_arr[i] = x;
                            y_arr[i] = y;
                            i++;
                        }
                        break;
                    
                }*/
            }
        }
    }
    x = x_arr[rand()%i];
    y = y_arr[rand()%i];
    if(board[x][y] != EMPTY_COORDINATE)
    {
        pieces[board[x][y]].state = CAPTURED;
    }
    pieces[piece].x = x;
    pieces[piece].y = y;

    return;
}