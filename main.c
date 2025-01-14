#include <stdio.h>
#include "include/board.h"
#include "include/game.h"
#include "include/score.h"

int main()
{
    Board gameBoard;

    int boardLevel, boardRows, boardCols, boardMines;

    selectLevel(&boardLevel, &boardRows, &boardCols, &boardMines);

    initializeBoard(&gameBoard, boardRows, boardCols, boardLevel);

    calculateNeighboringMines(&gameBoard);

    int gameOver = 0;
    // clearScreen();
    
    while(!gameOver) {

        displayBoard(&gameBoard, gameOver);

        printf("SCORE: %d\n", gameBoard.score);
        printf("Enter your command (f x y to flag Cell, r x y to reveal Cell): ");
        char command;
        int row, col;

        scanf(" %c %d %d", &command, &row, &col);

        processUserInput(&gameBoard, command, row, col, &gameOver, boardMines);
    }
    
    displayBoard(&gameBoard, gameOver);

    displayScoreboard();

    freeBoard(&gameBoard);

    startGame();

    return 0;
}