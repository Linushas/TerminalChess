#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <stdbool.h>

#define COLOR_BLUE_BG_TRANSPARENT "\033[36;1;1m"
//#define COLOR_BLUE_BG_WHITE "\033[34;1;47m"
#define COLOR_BLUE_BG_WHITE "\033[36;1;100m"
#define COLOR_WHITE_BG_TRANSPARENT "\033[0;1;1m"
//#define COLOR_WHITE_BG_WHITE "\033[0;1;47m"
#define COLOR_WHITE_BG_WHITE "\033[0;1;100m"
#define COLOR_RED "\033[0;31m"
#define COLOR_RESET "\033[m"

void getBoard(p pieces[], int board[BOARD_SIZE][BOARD_SIZE]);

void new_board(p pieces[]);

void print_chessboard(p pieces[]);
void print_chessboard_v2(p pieces[], bool is_illegal_move, bool nextPlayer);

char getPieceChar(int i, p pieces[]);

int calculatePiecePoints(p pieces[]);

#endif