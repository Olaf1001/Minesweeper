#include <stdio.h>
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

void processUserInput(Board *board, char command, int row, int col, int *gameOver) {
        if(command == 'f') {
                flagCell(board, row, col);
        } else if (command == 'r') {
                revealCell(board, row, col, gameOver);
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

void startGame(int rows, int cols) {
        printf("[^] game.c/game.h files works fine\n");
}