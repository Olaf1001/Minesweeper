#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/board.h"

void initializeBoard(Board *board, int rows, int cols)
{
    board->rows = rows;
    board->cols = cols;

    board->cells = malloc(rows * sizeof(Cell *));

    for (int i = 0; i < rows; i++)
    {
        board->cells[i] = malloc(cols * sizeof(Cell));
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            board->cells[i][j].isMine = 0;
            board->cells[i][j].isRevealed = 0;
            board->cells[i][j].isFlagged = 0;
            board->cells[i][j].neighboringMines = 0;
        }
    }

    printf("[^] Generated board with %d rows and %d columns\n", board->rows, board->cols);
}

void freeBoard(Board *board)
{
    for (int i = 0; i < board->rows; i++)
    {
        free(board->cells[i]);
    }
    free(board->cells);
}

void placeMines(Board *board, int mineCount) {
    srand(time(NULL));

    int placedMines = 0;

    while (placedMines < mineCount) {
        int row = rand() % board->rows;
        int col = rand() % board->cols;

        if(!board->cells[row][col].isMine) {
            board->cells[row][col].isMine = 1;
            placedMines++;
        }
    }
}

void calculateNeighboringMines(Board *board) {
    for(int i = 0; i < board->rows; i++){
        for(int j = 0; j < board->cols; j++) {
            if(board->cells[i][j].isMine) {
                board->cells[i][j].neighboringMines = -1; // MINE!!
                continue;
            }

            int mineCount = 0;
            for(int dr = -1; dr <= 1; dr++) {
                for(int dc = -1; dc <= 1; dc++) {
                    if(dr == 0 && dc == 0) {
                        continue;
                    }

                    int neighborRow = i + dr;
                    int neighborCol = j + dc;

                    if(neighborRow >= 0 && neighborRow < board->rows && neighborCol >= 0 && neighborCol < board->cols) {
                        if(board->cells[neighborRow][neighborCol].isMine) {
                            mineCount++;
                        }
                    }
                }
            }
            board->cells[i][j].neighboringMines = mineCount;
        }
    }
}

void flagCell(Board *board, int row, int col) {
    if (row < 0 && col < 0 && row >= board->rows && col >= board->cols) {
        printf("[!] Wrong coordinates!\n");
        return;
    }

    if(!board->cells[row][col].isRevealed) {
        board->cells[row][col].isFlagged = !board->cells[row][col].isFlagged;

        if(!board->cells[row][col].isFlagged) {
            printf("Cell [%d][%d] is now unflagged.\n", row, col);
        } else {
            printf("Cell [%d][%d] is now flagged.\n", row, col);
        }
    } else {
        printf("Cell[%d][%d] is already revealed.\n", row, col);
    }
}

void revealCell(Board *board, int row, int col, int * gameOver) {
    if (row < 0 && col < 0 && row >= board->rows && col >= board->cols) {
        printf("[!] Wrong coordinates!\n");
        return;
    }

    if(board->cells[row][col].isFlagged) {
        printf("Cell[%d][%d] is flagged.\n", row, col);
        return;
    }

    if(board->cells[row][col].isRevealed) {
        printf("Cell [%d][%d] is already revealed.\n", row, col);
        return;
    }

    board->cells[row][col].isRevealed = 1;

    if(board->cells[row][col].isMine) {
        printf("BOOM!!! You hit a mine at [%d][%d].\n", row, col);
        *gameOver = 1;
        return;
    }

    if (board->cells[row][col].neighboringMines == 0) {
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue;
                
                int neighborRow = row + dr;
                int neighborCol = col + dc;

                if (neighborRow >= 0 && neighborRow < board->rows &&
                    neighborCol >= 0 && neighborCol < board->cols) {
                    revealCell(board, neighborRow, neighborCol, gameOver);
                }
            }
        }
    }
}


