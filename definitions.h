#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define BOARD_SIZE 8
#define NR_OF_PIECES 32
#define EMPTY_COORDINATE (NR_OF_PIECES + 2)

enum piece{BPAWN1, BPAWN2, BPAWN3, BPAWN4, BPAWN5, BPAWN6, BPAWN7, BPAWN8, 
           BROOK1, BROOK2, BBISHOP1, BBISHOP2, BKNIGHT1, BKNIGHT2, BKING, BQUEEN,
           WPAWN1, WPAWN2, WPAWN3, WPAWN4, WPAWN5, WPAWN6, WPAWN7, WPAWN8, 
           WROOK1, WROOK2, WBISHOP1, WBISHOP2, WKNIGHT1, WKNIGHT2, WKING, WQUEEN};

enum piece_state{CAPTURED, PROMOTED, ACTIVE};

enum movetype{DEFAULT, KINGCASTLE, QUEENCASTLE};

enum check{NOT_IN_CHECK, BLACK_IN_CHECK, WHITE_IN_CHECK};

enum gameover{NOT_GAMEOVER, BLACK_CHECKMATE, WHITE_CHECKMATE, STALEMATE};

enum directions{NONE, UP, DOWN, LEFT, RIGHT, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT, KNIGHT};

typedef struct{
    int x;
    int y;
    int state;
}p;

typedef struct moveSpecs
{
    int piece;
    int start_x;
    int start_y;
    int dest_x;
    int dest_y;
    int move_type;
    int direction;
}move;

#endif