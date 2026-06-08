#include <stdlib.h>
#include "game.h"
#include "moves.h"

static int samePosition(Position first, Position second) {
    return first.row == second.row && first.col == second.col;
}
int isCheck(const Board* board, const Pieces* pieces) {
    if (isMoveValid(board, pieces->rook1, pieces->enemyKing)) {
        return 1;
    }

    if (isMoveValid(board, pieces->rook2, pieces->enemyKing)) {
        return 1;
    }

    return 0;
}

int areKingsAdjacent(Position king1, Position king2) {
    int rowDifference = abs(king1.row - king2.row);
    int colDifference = abs(king1.col - king2.col);

    return rowDifference <= 1 &&
           colDifference <= 1 &&
           !samePosition(king1, king2);
}

int hasLegalKingMove(const Board* board, const Pieces* pieces) {
    int rowChange;
    int colChange;

    for (rowChange = -1; rowChange <= 1; rowChange++) {
        for (colChange = -1; colChange <= 1; colChange++) {
            Board boardCopy;
            Pieces piecesCopy;
            Position newPosition;

            if (rowChange == 0 && colChange == 0) {
                continue;
            }

            newPosition.row = pieces->enemyKing.row + rowChange;
            newPosition.col = pieces->enemyKing.col + colChange;

            if (samePosition(newPosition, pieces->king) ||
                areKingsAdjacent(newPosition, pieces->king)) {
                continue;
            }

            if (!isMoveValid(board, pieces->enemyKing, newPosition)) {
                continue;
            }

            boardCopy = *board;
            piecesCopy = *pieces;

            if (!movePiece(&boardCopy, piecesCopy.enemyKing, newPosition)) {
                continue;
            }

            piecesCopy.enemyKing = newPosition;

            if (!isCheck(&boardCopy, &piecesCopy)) {
                return 1;
            }
        }
    }

    return 0;
}

int isCheckmate(const Board* board, const Pieces* pieces) {
    return isCheck(board, pieces) &&
           !hasLegalKingMove(board, pieces);
}