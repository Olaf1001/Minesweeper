#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"
#include "../include/game.h"

int checkIfWin(Board* board) {
        for(int i = 0; i < board->rows; i++) {
                for(int j = 0; j < board->cols; j++) {
                        if(!board->cells[i][j].isMine && !board->cells[i][j].isRevealed) {
                                return 0;
                        }
                }
        }
        return 1;
}

void processUserInput(Board *board, char command, int row, int col, int *gameOver, int mineCount) {
        row--;
        col--;
        if(command == 'f') {
                flagCell(board, row, col);
        } else if (command == 'r') {
                revealCell(board, row, col, gameOver, mineCount);
                if (*gameOver) {
                        printf("GAME OVER. You hit a mine. \n");
                } else if(checkIfWin(board)) {
                        printf("Congratulations! You won the game! \n");
                        *gameOver = 1;
                }
        } else {
                printf("[!] Unknown command, Try again. \n");
        }
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void selectLevel(int * boardLevel, int * boardRows, int * boardCols, int *boardMines) {
    int userLevel;

    printf("Welcome to Minesweeper game!\n");
    printf("Select game difficulty (1 - easy, 2 - medium, 3 - hard): ");
    scanf("%d", &userLevel);

    FILE* boards;

    boards = fopen("src/boards.txt", "r");

    if(boards == NULL) {
        printf("[!] Can't read from file! \n");
        return;
    }

    while (fscanf(boards, "%d", boardLevel) == 1) {
        if (*boardLevel == userLevel) {
            fscanf(boards, "%d %d %d", boardRows, boardCols, boardMines);
            printf("Level: %d, Rows: %d, Cols: %d, Mines: %d\n", *boardLevel, *boardRows, *boardCols, *boardMines);

        }
    }
}

void startGame(int rows, int cols) {

}