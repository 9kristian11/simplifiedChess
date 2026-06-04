#include <stdio.h>
#include "board.h"

void initBoard(Board* board, int size) {
    if (size < 1) {
        size = 1;
    }

    if (size > MAX_BOARD_SIZE) {
        size = MAX_BOARD_SIZE;
    }

    board->size = size;
    clearBoard(board);
}

void clearBoard(Board* board) {
    int row;
    int col;

    for (row = 0; row < board->size; row++) {
        for (col = 0; col < board->size; col++) {
            board->board[row][col] = '.';
        }
    }
}

void printBoard(const Board* board) {
    int row;
    int col;

    for (row = 0; row < board->size; row++) {
        for (col = 0; col < board->size; col++) {
            printf("%c ", board->board[row][col]);
        }
        printf("\n");
    }
}
