#include "definitions.h"
#include "moves.h"
#include "chessboard.h"
#include "./pieces/pieces.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int executeMove(move m, p pieces[], bool nextPlayer)
{
    if(m.move_type == DEFAULT)
    {
        int board[BOARD_SIZE][BOARD_SIZE];
        getBoard(pieces, board);

        if(m.piece < 16 && nextPlayer != 0)
            return 0;
        else if(m.piece >= 16 && nextPlayer != 1)
            return 0;

        int captured_coordinate = EMPTY_COORDINATE;
        if(board[m.dest_x][m.dest_y] != EMPTY_COORDINATE)
        {
            captured_coordinate = board[m.dest_x][m.dest_y];
        }

        switch(m.piece)
        {
            case BPAWN1: case BPAWN2: case BPAWN3: case BPAWN4: case BPAWN5: case BPAWN6: case BPAWN7: case BPAWN8:
            case WPAWN1: case WPAWN2: case WPAWN3: case WPAWN4: case WPAWN5: case WPAWN6: case WPAWN7: case WPAWN8:
                if(pieces[m.piece].state == PROMOTED)
                {
                    if(queen_rules(m, pieces) == 1)
                    {
                        pieces[m.piece].x = m.dest_x;
                        pieces[m.piece].y = m.dest_y;
                    }
                    else return 0;
                }
                else
                {
                    if(pawn_rules(m, pieces) == 1)
                    {
                        pieces[m.piece].x = m.dest_x;
                        pieces[m.piece].y = m.dest_y;
                    }
                    else return 0;
                }
                break;
            case BROOK1: case BROOK2: case WROOK1: case WROOK2:
                if(rook_rules(m, pieces) == 1)
                {
                    pieces[m.piece].x = m.dest_x;
                    pieces[m.piece].y = m.dest_y;
                }
                else return 0;
                break;
            case BBISHOP1: case BBISHOP2: case WBISHOP1: case WBISHOP2:
                if(bishop_rules(m, pieces) == 1)
                {
                    pieces[m.piece].x = m.dest_x;
                    pieces[m.piece].y = m.dest_y;
                }
                else return 0;
                break;
            case BKNIGHT1: case BKNIGHT2: case WKNIGHT1: case WKNIGHT2:
                if(knight_rules(m) == 1)
                {
                    pieces[m.piece].x = m.dest_x;
                    pieces[m.piece].y = m.dest_y;
                }
                else return 0;
                break;
            case BKING: case WKING:
                if(king_rules(m, pieces) == 1)
                {
                    pieces[m.piece].x = m.dest_x;
                    pieces[m.piece].y = m.dest_y;
                }
                else return 0;
                break;
            case BQUEEN: case WQUEEN:
                if(queen_rules(m, pieces) == 1)
                {
                    pieces[m.piece].x = m.dest_x;
                    pieces[m.piece].y = m.dest_y;
                }
                else return 0;
                break;
        }

        if(16 <= captured_coordinate && captured_coordinate < 32 && m.piece >= 16)
            return 0;
        else if(16 > captured_coordinate && m.piece < 16)
            return 0;

        if(captured_coordinate != EMPTY_COORDINATE)
        {
            pieces[captured_coordinate].state = CAPTURED;
        }
    }
    else if(m.move_type == KINGCASTLE || m.move_type == QUEENCASTLE)
        castle();
        
    return 1;
}

int in_check(bool nextPlayer, p pieces[])
{

}

void castle()
{

}

int charInputToIndex(char ch)
{
    switch(ch)
    {
        case 'a': return 0;
        case 'b': return 1;
        case 'c': return 2;
        case 'd': return 3;
        case 'e': return 4;
        case 'f': return 5;
        case 'g': return 6;
        case 'h': return 7;
        default: return 10;
    }
}

int getPiece(p pieces[], int x_pos, int y_pos)
{
    int board[BOARD_SIZE][BOARD_SIZE];
    getBoard(pieces, board);
    
    if(board[x_pos][y_pos] != EMPTY_COORDINATE)
    {
        return board[x_pos][y_pos];
    }
    return 404;
}

move getMove(p pieces[])
{
    move m;
    char input[6];

    while(1)
    {
        scanf("%6s", input);

        if(strcmp(input, "0-0") == 0)
            m.move_type = KINGCASTLE;
        else if(strcmp(input, "0-0-0") == 0)
            m.move_type = QUEENCASTLE;
        else
        {
            m.move_type = DEFAULT;
            m.start_x = charInputToIndex(input[0]);
            m.start_y = BOARD_SIZE - atoi(&input[1]);
            m.dest_x = charInputToIndex(input[2]);
            m.dest_y = BOARD_SIZE - atoi(&input[3]);

            m.piece = getPiece(pieces, m.start_x, m.start_y);
            if(m.piece == 404)
            {
                printf("No piece located at %c%c! Try again: ", input[0], input[1]); 
                continue;
            }

            if(m.start_x == m.dest_x && m.start_y == m.dest_y)
                m.direction = NONE;
            else if(m.start_x == m.dest_x && m.start_y < m.dest_y)
                m.direction = DOWN;
            else if(m.start_x == m.dest_x && m.start_y > m.dest_y)
                m.direction = UP;
            else if(m.start_x < m.dest_x && m.start_y == m.dest_y)
                m.direction = RIGHT;
            else if(m.start_x > m.dest_x && m.start_y == m.dest_y)
                m.direction = LEFT;
            else if(abs(m.start_x - m.dest_x) == abs(m.start_y - m.dest_y))
            {
                if((m.start_x - m.dest_x) < 0 && (m.start_y - m.dest_y) < 0)
                    m.direction = DOWNRIGHT;
                else if((m.start_x - m.dest_x) > 0 && (m.start_y - m.dest_y) < 0)
                    m.direction = DOWNLEFT;
                else if((m.start_x - m.dest_x) < 0 && (m.start_y - m.dest_y) > 0)
                    m.direction = UPRIGHT;
                else if((m.start_x - m.dest_x) > 0 && (m.start_y - m.dest_y) > 0)
                    m.direction = UPLEFT;
                else
                    {printf("Illegal move!"); continue;}
            }
            else if( (abs(m.start_x - m.dest_x) == 1 && abs(m.start_y - m.dest_y) == 2) ||
                     (abs(m.start_x - m.dest_x) == 2 && abs(m.start_y - m.dest_y) == 1))
                m.direction = KNIGHT;
            else
                {printf("Illegal move! Try again: "); continue;}
        }
        break;
    }
    //printf("piece: %d, x1:%d, y1:%d, x2:%d, y2:%d, move type:%d, direction:%d\n", m.piece, m.start_x, m.start_y, m.dest_x, m.dest_y, m.move_type, m.direction);
    return m;
}
