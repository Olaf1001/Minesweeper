#include <stdio.h>
#include "include/board.h"
#include "include/game.h"

int main()
{

    printf("Welcome to Minesweeper game!\n");

    Board gameBoard;

    initializeBoard(&gameBoard, 6, 6);

    placeMines(&gameBoard, 5);

    calculateNeighboringMines(&gameBoard);

    int gameOver = 0;
    
    while(!gameOver) {
        for (int i = 0; i < gameBoard.rows; i++) {
            for (int j = 0; j < gameBoard.cols; j++) {
                if (gameBoard.cells[i][j].isFlagged) {
                    printf("F ");
                } else if (!gameBoard.cells[i][j].isRevealed) {
                    printf(". ");
                } else if (gameBoard.cells[i][j].isMine) {
                    printf("* ");
                } else {
                    printf("%d ", gameBoard.cells[i][j].neighboringMines);
                }
            }
        printf("\n");
        }

        printf("Enter your command (f x y to flag Cell, r x y, to reveal Cell): ");
        char command;
        int row, col;

        scanf(" %c %d %d", &command, &row, &col);
        row--;
        col--;
        
    }

    freeBoard(&gameBoard);

    startGame();

    return 0;
}