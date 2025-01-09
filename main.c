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
        displayBoard(&gameBoard, gameOver);

        printf("Enter your command (f x y to flag Cell, r x y, to reveal Cell): ");
        char command;
        int row, col;

        scanf(" %c %d %d", &command, &row, &col);

        processUserInput(&gameBoard, command, row, col, &gameOver);
        
    }
    
    displayBoard(&gameBoard, gameOver);
    
    freeBoard(&gameBoard);

    startGame();

    return 0;
}