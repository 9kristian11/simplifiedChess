#include <stdlib.h>
#include "pieces.h"

static int samePosition(Position first, Position second) {
    return first.row == second.row && first.col == second.col;
}
static int areKingsAdjacent(Position firstKing, Position secondKing) {
    int rowDifference = abs(firstKing.row - secondKing.row);
    int colDifference = abs(firstKing.col - secondKing.col);

    return rowDifference <= 1 && colDifference <= 1;
}
static Position randomPosition(const Board* board) {
    Position position;

    position.row = rand() % board->size;
    position.col = rand() % board->size;

    return position;
}
void generateRandomPieces(Board* board, Pieces* pieces) {
    do {
        pieces->king = randomPosition(board);
        pieces->rook1 = randomPosition(board);
        pieces->rook2 = randomPosition(board);
        pieces->enemyKing = randomPosition(board);
    } while (
        samePosition(pieces->king, pieces->rook1) ||
        samePosition(pieces->king, pieces->rook2) ||
        samePosition(pieces->king, pieces->enemyKing) ||
        samePosition(pieces->rook1, pieces->rook2) ||
        samePosition(pieces->rook1, pieces->enemyKing) ||
        samePosition(pieces->rook2, pieces->enemyKing) ||
        areKingsAdjacent(pieces->king, pieces->enemyKing)
    );
}
void placePieces(Board* board, const Pieces* pieces) {
    clearBoard(board);

    board->board[pieces->king.row][pieces->king.col] = 'K';
    board->board[pieces->rook1.row][pieces->rook1.col] = 'R';
    board->board[pieces->rook2.row][pieces->rook2.col] = 'R';
    board->board[pieces->enemyKing.row][pieces->enemyKing.col] = 'C';
}