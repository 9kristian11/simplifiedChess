#ifndef BOARD_H
#define BOARD_H

#define MAX_BOARD_SIZE 20

typedef struct {
    int size;
    char board[20][20];
} Board;

void initBoard(Board* board, int size);
void clearBoard(Board* board);
void printBoard(const Board* board);

#endif