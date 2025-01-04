#include <stdio.h>
#include <stdlib.h>
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

    printf("[^] board.c/board.h files works fine\n");
    printf("[^] Generated board with %d rows and %d columns\n", board->rows, board->cols);
}

void freeBoard(Board *board)
{
    free(board->cells);

    for (int i = 0; i < board->rows; i++)
    {
        free(board->cells[i]);
    }
}