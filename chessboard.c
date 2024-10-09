#include "definitions.h"
#include "chessboard.h"
#include <stdio.h>
#include <stdbool.h>

void getBoard(p pieces[], int board[BOARD_SIZE][BOARD_SIZE])
{
    int x, y;
    for(y = 0; y < BOARD_SIZE; y++)
    {
        for(x = 0; x < BOARD_SIZE; x++)
        {
            board[x][y] = EMPTY_COORDINATE;
        }
    }

    int i;
    for(i = 0; i < NR_OF_PIECES; i++)
    {
        if(pieces[i].state != CAPTURED)
        {
            board[pieces[i].x][pieces[i].y] = i;
        }
    }
}

void new_board(p pieces[]) 
{
    p piece[NR_OF_PIECES] = 
    {
        [BPAWN1] = {0, 1, ACTIVE}, 
        [BPAWN2] = {1, 1, ACTIVE}, 
        [BPAWN3] = {2, 1, ACTIVE},
        [BPAWN4] = {3, 1, ACTIVE}, 
        [BPAWN5] = {4, 1, ACTIVE}, 
        [BPAWN6] = {5, 1, ACTIVE}, 
        [BPAWN7] = {6, 1, ACTIVE}, 
        [BPAWN8] = {7, 1, ACTIVE}, 
        [BROOK1] = {0, 0, ACTIVE}, 
        [BROOK2] = {7, 0, ACTIVE}, 
        [BBISHOP1] = {2, 0, ACTIVE}, 
        [BBISHOP2] = {5, 0, ACTIVE},
        [BKNIGHT1] = {1, 0, ACTIVE}, 
        [BKNIGHT2] = {6, 0, ACTIVE}, 
        [BKING] = {4, 0, ACTIVE}, 
        [BQUEEN] = {3, 0, ACTIVE}, 
        
        [WPAWN1] = {0, 6, ACTIVE}, 
        [WPAWN2] = {1, 6, ACTIVE},
        [WPAWN3] = {2, 6, ACTIVE}, 
        [WPAWN4] = {3, 6, ACTIVE},
        [WPAWN5] = {4, 6, ACTIVE}, 
        [WPAWN6] = {5, 6, ACTIVE}, 
        [WPAWN7] = {6, 6, ACTIVE},
        [WPAWN8] = {7, 6, ACTIVE}, 
        [WROOK1] = {0, 7, ACTIVE}, 
        [WROOK2] = {7, 7, ACTIVE},
        [WBISHOP1] = {2, 7, ACTIVE}, 
        [WBISHOP2] = {5, 7, ACTIVE}, 
        [WKNIGHT1] = {1, 7, ACTIVE}, 
        [WKNIGHT2] = {6, 7, ACTIVE}, 
        [WKING] = {4, 7, ACTIVE}, 
        [WQUEEN] = {3, 7, ACTIVE}  
    };
    int i;
    for(i = 0; i < NR_OF_PIECES; i++)
    {
        pieces[i].x = piece[i].x;
        pieces[i].y = piece[i].y;
        pieces[i].state = piece[i].state;
    }
}

void print_chessboard_v2(p pieces[], bool is_illegal_move, bool nextPlayer)
{ 
    int x, y, i = 0, board[BOARD_SIZE][BOARD_SIZE];
    getBoard(pieces, board);

    printf("\n");
    printf("\n");
    printf("   a  b  c  d  e  f  g  h  * * * * * * * * * * * * * * * *\n");
    for(y = 0; y < BOARD_SIZE; y++)
    {   
        
        printf("%d ", BOARD_SIZE - y);
        for(x = 0; x < BOARD_SIZE; x++)
        {
            if((i % 2 == 0) && (board[x][y] < 16)) 
                printf(COLOR_WHITE_BG_WHITE" "COLOR_BLUE_BG_WHITE"%c"COLOR_RESET""COLOR_WHITE_BG_WHITE" "COLOR_RESET, getPieceChar(board[x][y], pieces));
            else if((i % 2 != 0) && (board[x][y] < 16))
                printf(COLOR_WHITE_BG_TRANSPARENT" "COLOR_BLUE_BG_TRANSPARENT"%c"COLOR_RESET""COLOR_WHITE_BG_TRANSPARENT" "COLOR_RESET, getPieceChar(board[x][y], pieces));
            if((i % 2 == 0) && (board[x][y] >= 16)) 
                printf(COLOR_WHITE_BG_WHITE" %c "COLOR_RESET, getPieceChar(board[x][y], pieces));
            else if((i % 2 != 0) && (board[x][y] >= 16))
                printf(COLOR_WHITE_BG_TRANSPARENT" %c "COLOR_RESET, getPieceChar(board[x][y], pieces));
            i++;
        }
        printf(" *");
        if(y == 0)
        {
            printf("   ");
            for(i = 0; i < NR_OF_PIECES; i++)
            {
                if(i < 16 && pieces[i].state == CAPTURED)
                    printf(COLOR_BLUE_BG_TRANSPARENT"%c "COLOR_RESET, getPieceChar(i, pieces));
                else if(i >= 16 && pieces[i].state == CAPTURED)
                    printf(COLOR_WHITE_BG_TRANSPARENT"%c "COLOR_RESET, getPieceChar(i, pieces));
            }
            int balance = calculatePiecePoints(pieces);
            if(balance != 0) printf("  %d", balance);
        }
        
        if(y == 6) printf("   ___________________________");
        if(y == 7 && is_illegal_move) printf("   "COLOR_RED"Illegal move! Try again: "COLOR_RESET);
        else if(y == 7) printf("   %s's turn! Enter move: ", nextPlayer ? "White" : "Black");
        printf("\n");
        i++;
    }
    
}

char getPieceChar(int i, p pieces[])
{
    if(pieces[i].state == PROMOTED)
        return 'Q';
    else
    {
        switch(i)
        {
            case BPAWN1: case BPAWN2: case BPAWN3: case BPAWN4: case BPAWN5: case BPAWN6: case BPAWN7: case BPAWN8: 
                return 'o';
            case BROOK1: case BROOK2:
                return 'R';
            case BBISHOP1: case BBISHOP2:
                return 'B';
            case BKNIGHT1: case BKNIGHT2:
                return 'N';
            case BKING:
                return 'K';
            case BQUEEN:
                return 'Q';
            case WPAWN1: case WPAWN2: case WPAWN3: case WPAWN4: case WPAWN5: case WPAWN6: case WPAWN7: case WPAWN8: 
                return 'o';
            case WROOK1: case WROOK2:
                return 'R';
            case WBISHOP1: case WBISHOP2:
                return 'B';
            case WKNIGHT1: case WKNIGHT2:
                return 'N';
            case WKING:
                return 'K';
            case WQUEEN:
                return 'Q';
            case EMPTY_COORDINATE:
                return ' ';
            default:
                return ' ';
        }
    }
    
}

int calculatePiecePoints(p pieces[])
{
    int i, balance = 0;
    for(i = 0; i < NR_OF_PIECES; i++)
    {
        if(pieces[i].state == CAPTURED)
        {
            switch(i)
            {
                case BPAWN1: case BPAWN2: case BPAWN3: case BPAWN4: case BPAWN5: case BPAWN6: case BPAWN7: case BPAWN8: 
                    balance -= 1;
                    break;
                case BROOK1: case BROOK2:
                    balance -= 5;
                    break;
                case BBISHOP1: case BBISHOP2:
                    balance -= 3;
                    break;
                case BKNIGHT1: case BKNIGHT2:
                    balance -= 3;
                    break;
                case BQUEEN:
                    balance -= 9;
                    break;
                case WPAWN1: case WPAWN2: case WPAWN3: case WPAWN4: case WPAWN5: case WPAWN6: case WPAWN7: case WPAWN8: 
                    balance += 1;
                    break;
                case WROOK1: case WROOK2:
                    balance += 5;
                    break;
                case WBISHOP1: case WBISHOP2:
                    balance += 3;
                    break;
                case WKNIGHT1: case WKNIGHT2:
                    balance += 3;
                    break;
                case WQUEEN:
                    balance += 9;
                    break;
            }
        }
    }
    return balance;
}



