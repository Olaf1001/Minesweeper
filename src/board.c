#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/board.h"

void initializeBoard(Board *board, int rows, int cols, int level)
{
    board->rows = rows;
    board->cols = cols;
    board->firstMove = 0;
    board->level = level;
    board->score = 0;

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
}

void freeBoard(Board *board)
{
    for (int i = 0; i < board->rows; i++)
    {
        free(board->cells[i]);
    }
    free(board->cells);
}

void placeMines(Board *board, int excludeRow, int excludeCol, int mineCount) {
    srand(time(NULL));

    int placedMines = 0;

    while (placedMines < mineCount) {
        int row = rand() % board->rows;
        int col = rand() % board->cols;

        if ((row >= excludeRow - 1 && row <= excludeRow + 1) &&
            (col >= excludeCol - 1 && col <= excludeCol + 1)) {
            continue;
        }

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
    if (row < 0 || col < 0 || row >= board->rows || col >= board->cols) {
        printf("[!] Wrong coordinates!\n");
        return;
    }

    if(!board->cells[row][col].isRevealed) {
        board->cells[row][col].isFlagged = !board->cells[row][col].isFlagged;
    } 
}

void revealCell(Board *board, int row, int col, int * gameOver, int mineCount) {
    if (row < 0 || col < 0 || row >= board->rows || col >= board->cols) {
        printf("[!] Wrong coordinates!\n");
        return;
    }

    if (board->firstMove == 0) {
        if(mineCount != 0) {
            placeMines(board, row, col, mineCount);
        }
        calculateNeighboringMines(board);
        board->firstMove = 1;
    }

    if(board->cells[row][col].isFlagged) {
        printf("Cell[%d][%d] is flagged.\n", row, col);
        return;
    }

    if(board->cells[row][col].isRevealed) {
        return;
    }

    board->cells[row][col].isRevealed = 1;

    if(board->cells[row][col].isMine) {
        printf("BOOM!!! You hit a mine at [%d][%d].\n", row + 1, col + 1);
        *gameOver = 1;
        return;
    }

    board->score += 1 * board->level; // Score calculataion

    if (board->cells[row][col].neighboringMines == 0) {
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue;
                
                int neighborRow = row + dr;
                int neighborCol = col + dc;

                if (neighborRow >= 0 && neighborRow < board->rows &&
                    neighborCol >= 0 && neighborCol < board->cols) {
                    revealCell(board, neighborRow, neighborCol, gameOver, mineCount);
                }
            }
        }
    }
}

void displayBoard(Board* board, int gameOver) {
    printf("   ");
    for (int col = 0; col < board->cols; col++) {
        printf("\033[1m%2d \033[0m", col + 1);
    }

    printf("\n");

    for (int row = 0; row < board->rows; row++) {
        printf("\033[1m%2d \033[0m", row + 1);
        for (int col = 0; col < board->cols; col++) {
            Cell* cell = &board->cells[row][col];

            if (gameOver && cell->isMine) {
                printf(" * ");
            } else if (cell->isFlagged) {
                printf("\033[1;31m ⚑ \033[0m");
            } else if (!cell->isRevealed) {
                printf(" ■ ");
            } else if (cell->neighboringMines > 0) {
                switch (cell->neighboringMines) {
                    case 1:
                        printf("\033[0;34m %d \033[0m", cell->neighboringMines);
                        break;
                    case 2:
                        printf("\033[0;32m %d \033[0m", cell->neighboringMines);
                        break;
                    case 3:
                        printf("\033[0;31m %d \033[0m", cell->neighboringMines);
                        break;
                    case 4:
                        printf("\033[0;35m %d \033[0m", cell->neighboringMines);
                        break;
                    case 5:
                        printf("\033[0;33m %d \033[0m", cell->neighboringMines);
                        break;
                    default:
                        printf("\033[0;36m %d \033[0m", cell->neighboringMines);
                        break;
                }
            } else {
                printf("   ");
            }
        }
        printf("\n");
    }
    printf("\n");
}
