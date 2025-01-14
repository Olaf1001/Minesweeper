#include <stdio.h>
#include <unistd.h>
#include "include/board.h"
#include "include/game.h"
#include "include/score.h"

int main(int argc, char *argv[])
{
    int opt;

    while ((opt = getopt(argc, argv, "f:s")) != -1) {
        switch (opt) {
            case 'f':
                return 0;
            case 's':
                displayScoreboard();
                return 0;
            default:
                fprintf(stderr, "Usage: %s [-f <file>] [-s]\n", argv[0]);
                return 1;
        }
    }

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


    displayScoreboard();

    freeBoard(&gameBoard);

    startGame();

    return 0;
}