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
    int firstMove;
    int level;
    int score;
    Cell **cells;
} Board;

void initializeBoard(Board *board, int rows, int cols, int level);

void freeBoard(Board *);

void placeMines(Board *board, int excludeRow, int excludeCol, int mineCount);

void calculateNeighboringMines(Board *board);

void flagCell(Board *board, int row, int col);

void revealCell(Board *board, int row, int col, int * gameOver, int mineCount);

void displayBoard(Board* board, int gameOver);

void clearScreen();

#endif