#include <stdlib.h>
#include "moves.h"

static int isInsideBoard(const Board* board, Position position) {
    return position.row >= 0 &&
           position.row < board->size &&
           position.col >= 0 &&
           position.col < board->size;
}

static int isFriendlyPiece(char piece, char destination) {
    if ((piece == 'K' || piece == 'R') &&
        (destination == 'K' || destination == 'R')) {
        return 1;
    }

    if (piece == 'C' && destination == 'C') {
        return 1;
    }

    return 0;
}

static int isRookPathClear(const Board* board, Position from, Position to) {
    int rowStep = 0;
    int colStep = 0;
    int row;
    int col;

    if (to.row > from.row) {
        rowStep = 1;
    } else if (to.row < from.row) {
        rowStep = -1;
    }

    if (to.col > from.col) {
        colStep = 1;
    } else if (to.col < from.col) {
        colStep = -1;
    }

    row = from.row + rowStep;
    col = from.col + colStep;

    while (row != to.row || col != to.col) {
        if (board->board[row][col] != '.') {
            return 0;
        }

        row += rowStep;
        col += colStep;
    }

    return 1;
}

int isValidKingMove(Position from, Position to) {
    int rowDifference = abs(to.row - from.row);
    int colDifference = abs(to.col - from.col);

    return rowDifference <= 1 &&
           colDifference <= 1 &&
           (rowDifference != 0 || colDifference != 0);
}

int isValidRookMove(Position from, Position to) {
    int sameRow = from.row == to.row && from.col != to.col;
    int sameColumn = from.col == to.col && from.row != to.row;

    return sameRow || sameColumn;
}

int isMoveValid(const Board* board, Position from, Position to) {
    char piece;
    char destination;

    if (!isInsideBoard(board, from) || !isInsideBoard(board, to)) {
        return 0;
    }

    piece = board->board[from.row][from.col];
    destination = board->board[to.row][to.col];

    if (piece == '.' || isFriendlyPiece(piece, destination)) {
        return 0;
    }

    if (piece == 'K' || piece == 'C') {
        return isValidKingMove(from, to);
    }

    if (piece == 'R') {
        return isValidRookMove(from, to) &&
               isRookPathClear(board, from, to);
    }

    return 0;
}

int movePiece(Board* board, Position from, Position to) {
    if (!isMoveValid(board, from, to)) {
        return 0;
    }

    board->board[to.row][to.col] = board->board[from.row][from.col];
    board->board[from.row][from.col] = '.';

    return 1;
}