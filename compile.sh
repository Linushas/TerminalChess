#!/bin/bash
gcc main.c -Wall chessboard.c moves.c ./pieces/bishop.c ./pieces/king.c ./pieces/knight.c ./pieces/pawn.c ./pieces/queen.c ./pieces/rook.c -o chess -I /VSCode/Terminal_Chess