#ifndef GAME_H
#define GAME_H

#include "pieces.h"

int isCheck(const Board* board, const Pieces* pieces);
int areKingsAdjacent(Position king1, Position king2);
int hasLegalKingMove(const Board* board, const Pieces* pieces);
int isCheckmate(const Board* board, const Pieces* pieces);

#endif