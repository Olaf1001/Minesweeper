#ifndef BOARD_H
#define BOARD_H

typedef struct
{
    int isMine;
    int isRevealed;
    int isFlagged;
    int neighboringMines;
} Cell;

typedef struct
{
    int rows;
    int cols;
    Cell **cells;
} Board;

void initializeBoard(Board *, int rows, int cols);

void freeBoard(Board *);

void placeMines(Board *board, int mineCount);

void calculateNeighboringMines(Board *board);

#endif