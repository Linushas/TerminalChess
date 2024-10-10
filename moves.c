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

        p temp_pieces[NR_OF_PIECES];
        int i;
        for(i = 0; i < NR_OF_PIECES; i++)
        {
            temp_pieces[i] = pieces[i];
        }

        switch(m.piece)
        {
            case BPAWN1: case BPAWN2: case BPAWN3: case BPAWN4: case BPAWN5: case BPAWN6: case BPAWN7: case BPAWN8:
            case WPAWN1: case WPAWN2: case WPAWN3: case WPAWN4: case WPAWN5: case WPAWN6: case WPAWN7: case WPAWN8:
                if(temp_pieces[m.piece].state == PROMOTED)
                {
                    if(queen_rules(m, temp_pieces) == 1)
                    {
                        temp_pieces[m.piece].x = m.dest_x;
                        temp_pieces[m.piece].y = m.dest_y;
                    }
                    else return 0;
                }
                else
                {
                    if(pawn_rules(m, temp_pieces) == 1)
                    {
                        temp_pieces[m.piece].x = m.dest_x;
                        temp_pieces[m.piece].y = m.dest_y;
                    }
                    else return 0;
                }
                break;
            case BROOK1: case BROOK2: case WROOK1: case WROOK2:
                if(rook_rules(m, temp_pieces) == 1)
                {
                    temp_pieces[m.piece].x = m.dest_x;
                    temp_pieces[m.piece].y = m.dest_y;
                }
                else return 0;
                break;
            case BBISHOP1: case BBISHOP2: case WBISHOP1: case WBISHOP2:
                if(bishop_rules(m, temp_pieces) == 1)
                {
                    temp_pieces[m.piece].x = m.dest_x;
                    temp_pieces[m.piece].y = m.dest_y;
                }
                else return 0;
                break;
            case BKNIGHT1: case BKNIGHT2: case WKNIGHT1: case WKNIGHT2:
                if(knight_rules(m) == 1)
                {
                    temp_pieces[m.piece].x = m.dest_x;
                    temp_pieces[m.piece].y = m.dest_y;
                }
                else return 0;
                break;
            case BKING: case WKING:
                if(king_rules(m, temp_pieces) == 1)
                {
                    temp_pieces[m.piece].x = m.dest_x;
                    temp_pieces[m.piece].y = m.dest_y;
                }
                else return 0;
                break;
            case BQUEEN: case WQUEEN:
                if(queen_rules(m, temp_pieces) == 1)
                {
                    temp_pieces[m.piece].x = m.dest_x;
                    temp_pieces[m.piece].y = m.dest_y;
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
            temp_pieces[captured_coordinate].state = CAPTURED;
        }

        if(in_check(temp_pieces) == BLACK_IN_CHECK && m.piece < 16)
        {
            return 0;
        }
        else if(in_check(temp_pieces) == WHITE_IN_CHECK && m.piece >= 16)
        {
            return 0;
        }
        else
        {
            for(i = 0; i < NR_OF_PIECES; i++)
            {
                pieces[i] = temp_pieces[i];
            }
        }
    }
    else if(m.move_type == KINGCASTLE || m.move_type == QUEENCASTLE)
    {
        if(castle(pieces, nextPlayer, m.move_type) == 0)
            return 0;
    }
        
    return 1;
}

int in_check(p pieces[])
{
    int i;
    for(i = 0; i < NR_OF_PIECES; i++)
    {
        if(pieces[i].state == PROMOTED)
        {
            if(visible_to_queen(pieces, pieces[i], pieces[BKING].x, pieces[BKING].y) == 1 && pieces[i].state != CAPTURED && i >= 16)
                return BLACK_IN_CHECK;
            if(visible_to_queen(pieces, pieces[i], pieces[WKING].x, pieces[WKING].y) == 1 && pieces[i].state != CAPTURED && i < 16)
                return WHITE_IN_CHECK;
        }
    }

    //Black king
    if(visible_to_bishop(pieces, pieces[WBISHOP1], pieces[BKING].x, pieces[BKING].y) == 1 && pieces[WBISHOP1].state != CAPTURED)
        return BLACK_IN_CHECK;
    else if(visible_to_bishop(pieces, pieces[WBISHOP2], pieces[BKING].x, pieces[BKING].y) == 1 && pieces[WBISHOP2].state != CAPTURED)
        return BLACK_IN_CHECK;
    
    else if(visible_to_rook(pieces, pieces[WROOK1], pieces[BKING].x, pieces[BKING].y) == 1 && pieces[WROOK2].state != CAPTURED)
        return BLACK_IN_CHECK;
    else if(visible_to_rook(pieces, pieces[WROOK2], pieces[BKING].x, pieces[BKING].y) == 1 && pieces[WROOK2].state != CAPTURED)
        return BLACK_IN_CHECK;

    else if(visible_to_knight(pieces, pieces[WKNIGHT1], pieces[BKING].x, pieces[BKING].y) == 1 && pieces[WKNIGHT2].state != CAPTURED)
        return BLACK_IN_CHECK;
    else if(visible_to_knight(pieces, pieces[WKNIGHT2], pieces[BKING].x, pieces[BKING].y) == 1 && pieces[WKNIGHT2].state != CAPTURED)
        return BLACK_IN_CHECK;
    
    else if(visible_to_queen(pieces, pieces[WQUEEN], pieces[BKING].x, pieces[BKING].y) == 1 && pieces[WQUEEN].state != CAPTURED)
        return BLACK_IN_CHECK;
    
    else if(visible_to_pawn(pieces, pieces[WPAWN1], pieces[BKING].x, pieces[BKING].y) == 1 && pieces[WPAWN1].state != CAPTURED)
        return BLACK_IN_CHECK;
    else if(visible_to_pawn(pieces, pieces[WPAWN2], pieces[BKING].x, pieces[BKING].y) == 1 && pieces[WPAWN2].state != CAPTURED)
        return BLACK_IN_CHECK;
    else if(visible_to_pawn(pieces, pieces[WPAWN3], pieces[BKING].x, pieces[BKING].y) == 1 && pieces[WPAWN3].state != CAPTURED) 
        return BLACK_IN_CHECK;
    else if(visible_to_pawn(pieces, pieces[WPAWN4], pieces[BKING].x, pieces[BKING].y) == 1 && pieces[WPAWN4].state != CAPTURED)
        return BLACK_IN_CHECK;
    else if(visible_to_pawn(pieces, pieces[WPAWN5], pieces[BKING].x, pieces[BKING].y) == 1 && pieces[WPAWN5].state != CAPTURED)
        return BLACK_IN_CHECK;
    else if(visible_to_pawn(pieces, pieces[WPAWN6], pieces[BKING].x, pieces[BKING].y) == 1 && pieces[WPAWN6].state != CAPTURED)
        return BLACK_IN_CHECK;
    else if(visible_to_pawn(pieces, pieces[WPAWN7], pieces[BKING].x, pieces[BKING].y) == 1 && pieces[WPAWN7].state != CAPTURED)
        return BLACK_IN_CHECK;
    else if(visible_to_pawn(pieces, pieces[WPAWN8], pieces[BKING].x, pieces[BKING].y) == 1 && pieces[WPAWN8].state != CAPTURED)
        return BLACK_IN_CHECK;

    //White king
    if(visible_to_bishop(pieces, pieces[BBISHOP1], pieces[WKING].x, pieces[WKING].y) == 1 && pieces[BBISHOP1].state != CAPTURED)
        return WHITE_IN_CHECK;
    else if(visible_to_bishop(pieces, pieces[BBISHOP2], pieces[WKING].x, pieces[WKING].y) == 1 && pieces[BBISHOP2].state != CAPTURED)
        return WHITE_IN_CHECK;
    
    else if(visible_to_rook(pieces, pieces[BROOK1], pieces[WKING].x, pieces[WKING].y) == 1 && pieces[BROOK1].state != CAPTURED)
        return WHITE_IN_CHECK;
    else if(visible_to_rook(pieces, pieces[BROOK2], pieces[WKING].x, pieces[WKING].y) == 1 && pieces[BROOK2].state != CAPTURED)
        return WHITE_IN_CHECK;

    else if(visible_to_knight(pieces, pieces[BKNIGHT1], pieces[WKING].x, pieces[WKING].y) == 1 && pieces[BKNIGHT1].state != CAPTURED)
        return WHITE_IN_CHECK;
    else if(visible_to_knight(pieces, pieces[BKNIGHT2], pieces[WKING].x, pieces[WKING].y) == 1 && pieces[BKNIGHT2].state != CAPTURED)
        return WHITE_IN_CHECK;
    
    else if(visible_to_queen(pieces, pieces[BQUEEN], pieces[WKING].x, pieces[WKING].y) == 1 && pieces[BQUEEN].state != CAPTURED)
        return WHITE_IN_CHECK;
    
    else if(visible_to_pawn(pieces, pieces[BPAWN1], pieces[WKING].x, pieces[WKING].y) == 1 && pieces[BPAWN1].state != CAPTURED)
        return WHITE_IN_CHECK;
    else if(visible_to_pawn(pieces, pieces[BPAWN2], pieces[WKING].x, pieces[WKING].y) == 1 && pieces[BPAWN2].state != CAPTURED)
        return BLACK_IN_CHECK;
    else if(visible_to_pawn(pieces, pieces[BPAWN3], pieces[WKING].x, pieces[WKING].y) == 1 && pieces[BPAWN3].state != CAPTURED)
        return WHITE_IN_CHECK;
    else if(visible_to_pawn(pieces, pieces[BPAWN4], pieces[WKING].x, pieces[WKING].y) == 1 && pieces[BPAWN4].state != CAPTURED)
        return WHITE_IN_CHECK;
    else if(visible_to_pawn(pieces, pieces[BPAWN5], pieces[WKING].x, pieces[WKING].y) == 1 && pieces[BPAWN5].state != CAPTURED)
        return WHITE_IN_CHECK;
    else if(visible_to_pawn(pieces, pieces[BPAWN6], pieces[WKING].x, pieces[WKING].y) == 1 && pieces[BPAWN6].state != CAPTURED)
        return WHITE_IN_CHECK;
    else if(visible_to_pawn(pieces, pieces[BPAWN7], pieces[WKING].x, pieces[WKING].y) == 1 && pieces[BPAWN7].state != CAPTURED)
        return WHITE_IN_CHECK;
    else if(visible_to_pawn(pieces, pieces[BPAWN8], pieces[WKING].x, pieces[WKING].y) == 1 && pieces[BPAWN8].state != CAPTURED)
        return WHITE_IN_CHECK;
    
    else return NOT_IN_CHECK;
}

int castle(p pieces[], bool nextPlayer, int move_type)
{
    int board[BOARD_SIZE][BOARD_SIZE];
    getBoard(pieces, board);
    if(nextPlayer)
    {
        if(move_type == KINGCASTLE)
        {
            if(board[5][7] != EMPTY_COORDINATE || board[6][7] != EMPTY_COORDINATE) return 0;
            else
            {
                if(pieces[WROOK2].x == 7 && pieces[WROOK2].y == 7 && pieces[WKING].x == 4 && pieces[WKING].y == 7)
                {
                    pieces[WROOK2].x = 5;
                    pieces[WKING].x = 6;
                }
            }
        }
        else if(move_type == QUEENCASTLE)
        {
            if(board[3][7] != EMPTY_COORDINATE || board[2][7] != EMPTY_COORDINATE || board[1][7] != EMPTY_COORDINATE) return 0;
            else
            {
                if(pieces[WROOK1].x == 0 && pieces[WROOK1].y == 7 && pieces[WKING].x == 4 && pieces[WKING].y == 7)
                {
                    pieces[WROOK1].x = 3;
                    pieces[WKING].x = 2;
                }
            }
        }
    }
    else
    {
        if(move_type == KINGCASTLE)
        {
            if(board[5][0] != EMPTY_COORDINATE || board[6][0] != EMPTY_COORDINATE) return 0;
            else
            {
                if(pieces[BROOK2].x == 7 && pieces[BROOK2].y == 0 && pieces[BKING].x == 4 && pieces[BKING].y == 0)
                {
                    pieces[BROOK2].x = 5;
                    pieces[BKING].x = 6;
                }
            }
        }
        else if(move_type == QUEENCASTLE)
        {
            if(board[3][0] != EMPTY_COORDINATE || board[2][0] != EMPTY_COORDINATE || board[1][0] != EMPTY_COORDINATE) return 0;
            else
            {
                if(pieces[BROOK1].x == 0 && pieces[BROOK1].y == 0 && pieces[BKING].x == 4 && pieces[BKING].y == 0)
                {
                    pieces[BROOK1].x = 3;
                    pieces[BKING].x = 2;
                }
            }
        }
    }
    return 1;
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

move getMove(p pieces[], bool nextPlayer)
{
    move m;
    char inputDest[6];
    char inputPiece[6];

    while(1)
    {
        scanf("%6s", inputPiece);
        m.start_x = charInputToIndex(inputPiece[0]);
        m.start_y = BOARD_SIZE - atoi(&inputPiece[1]);
        m.piece = getPiece(pieces, m.start_x, m.start_y);
        print_available_moves(pieces, false, nextPlayer, m.piece);
        printf("                           *   > ");

        scanf("%6s", inputDest);

        if(strcmp(inputDest, "0-0") == 0)
            m.move_type = KINGCASTLE;
        else if(strcmp(inputDest, "0-0-0") == 0)
            m.move_type = QUEENCASTLE;
        else
        {
            m.move_type = DEFAULT;
            m.dest_x = charInputToIndex(inputDest[0]);
            m.dest_y = BOARD_SIZE - atoi(&inputDest[1]);
            if(m.piece == 404)
            {
                //printf("No piece located at %c%c! Try again: ", input[0], input[1]); 
                print_chessboard_v2(pieces, true, nextPlayer);
                printf("                           *   > ");
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
                {
                    print_chessboard_v2(pieces, true, nextPlayer);
                    printf("                           *   > ");
                }
            }
            else if( (abs(m.start_x - m.dest_x) == 1 && abs(m.start_y - m.dest_y) == 2) ||
                     (abs(m.start_x - m.dest_x) == 2 && abs(m.start_y - m.dest_y) == 1))
                m.direction = KNIGHT;
            else
            {
                print_chessboard_v2(pieces, true, nextPlayer);
                printf("                           *   > ");
            }
        }
        break;
    }
    //printf("piece: %d, x1:%d, y1:%d, x2:%d, y2:%d, move type:%d, direction:%d\n", m.piece, m.start_x, m.start_y, m.dest_x, m.dest_y, m.move_type, m.direction);
    return m;
}
