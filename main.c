#include <stdio.h>
#include "include/board.h"
#include "include/game.h"

int main()
{

    printf("Welcome to Minesweeper game!\n");

    Board gameBoard;

    initializeBoard(&gameBoard, 10, 6);

    placeMines(&gameBoard, 5);

    calculateNeighboringMines(&gameBoard);

    // Display Test Board

    for(int i = 0; i < gameBoard.rows; i++) {
        for(int j = 0; j < gameBoard.cols; j++) {
            if(gameBoard.cells[i][j].isMine) {
                printf("* ");
            } else {
                printf("%d ", gameBoard.cells[i][j].neighboringMines);
            }
        }
        printf("\n");
    }

    freeBoard(&gameBoard);

    startGame();

    return 0;
}