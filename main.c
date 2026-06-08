#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "board.h"
#include "game.h"
#include "moves.h"
#include "pieces.h"

static int convertCoordinates(const Board* board, const char* text,Position* position) {
    int rank;
    char extra;
    char file = text[0];
    if (file >= 'A' && file <= 'Z') {
        file = (char)(file - 'A' + 'a');
    }
    if (sscanf(text + 1, "%d%c", &rank, &extra) != 1) {
        return 0;
    }
    position->col = file - 'a';
    position->row = board->size - rank;

    return position->row >= 0 && position->row < board->size && position->col >= 0 && position->col < board->size;
}
static int getPiecePosition(const Pieces* pieces, const char* pieceName,Position* position) {
    if (strcmp(pieceName, "R1") == 0) {
        *position = pieces->rook1;
        return 1;
    }
    if (strcmp(pieceName, "R2") == 0) {
        *position = pieces->rook2;
        return 1;
    }
    if (strcmp(pieceName, "K") == 0) {
        *position = pieces->king;
        return 1;
    }
    return 0;
}
static void updatePiecePosition(Pieces* pieces, const char* pieceName,Position position) {
    if (strcmp(pieceName, "R1") == 0) {
        pieces->rook1 = position;
    } else if (strcmp(pieceName, "R2") == 0) {
        pieces->rook2 = position;
    } else {
        pieces->king = position;
    }
}
int main(void) {
    Board board;
    Pieces pieces;
    char input[100];
    srand((unsigned int)time(NULL));
    initBoard(&board, 8);
    generateRandomPieces(&board, &pieces);
    placePieces(&board, &pieces);
    printBoard(&board);
    while (1) {
        char pieceName[3];
        char coordinates[4];
        char extra;
        Position from;
        Position to;
        printBoard(&board);
        printf("Enter move (R1 f3, R2 a8, or K e4): ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            return 0;
        }

        if (sscanf(input, " %2s %3s %c", pieceName, coordinates, &extra) != 2) {
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (!getPiecePosition(&pieces, pieceName, &from) || !convertCoordinates(&board, coordinates, &to)) {
            printf("Invalid input. Try again.\n");
            continue;
        }

        if (to.row == pieces.enemyKing.row && to.col == pieces.enemyKing.col) {
            printf("Invalid move. The computer king must be checkmated.\n");
            continue;
        }

        if (strcmp(pieceName, "K") == 0 && areKingsAdjacent(to, pieces.enemyKing)) {
            printf("Invalid move. The kings cannot be adjacent.\n");
            continue;
        }

        if (!isMoveValid(&board, from, to) || !movePiece(&board, from, to)) {
            printf("Invalid move. Try again.\n");
            continue;
        }

        updatePiecePosition(&pieces, pieceName, to);

        if (isCheck(&board, &pieces)) {
            printf("The computer king is in check!\n");
        }

        if (isCheckmate(&board, &pieces)) {
            printBoard(&board);
            printf("Checkmate! You win.\n");
            break;
        }
    }
    return 0;
}