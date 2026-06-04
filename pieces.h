#ifndef PIECES_H
#define PIECES_H

#include "board.h"

typedef struct {
    int row;
    int col;
} Position;

typedef struct {
    Position king;
    Position rook1;
    Position rook2;
    Position enemyKing;
} Pieces;

void generateRandomPieces(Board* board, Pieces* pieces);
void placePieces(Board* board, const Pieces* pieces);

#endif