#ifndef MOVES_H
#define MOVES_H

#include "pieces.h"

int isValidKingMove(Position from, Position to);
int isValidRookMove(Position from, Position to);
int isMoveValid(const Board* board, Position from, Position to);
int movePiece(Board* board, Position from, Position to);

#endif