#ifndef CHESSBOARD_H
#define CHESSBOARD_H

void getBoard(p pieces[], int board[BOARD_SIZE][BOARD_SIZE]);

void new_board(p pieces[]);

void print_chessboard(p pieces[]);

char getPieceChar(int i, p pieces[]);

int calculatePiecePoints(p pieces[]);

#endif