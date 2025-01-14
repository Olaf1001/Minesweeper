
#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"
#include "../include/game.h"

void runFromFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("[!] Error: Can't open file %s\n", filename);
        return;
    }

    int rows, cols;
    fscanf(file, "%d %d", &rows, &cols);

    Board gameBoard;
    initializeBoard(&gameBoard, rows, cols, 1);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char cell;
            fscanf(file, " %c", &cell);

            if (cell == '*') {
                gameBoard.cells[i][j].isMine = 1; 
            } else {
                gameBoard.cells[i][j].isMine = 0;
            }
        }
    }

    int gameOver = 0;
    int moveCounter = 0;
    int rowR, colR; // r x y (next steps from file)
    while(fscanf(file, "%d %d", &rowR, &colR) == 2 && gameOver != 1) {
        printf("Next step: x = %d   y = %d\n", rowR, colR);
        processUserInput(&gameBoard, 'r', rowR, colR, &gameOver, 0);
        displayBoard(&gameBoard, gameOver);
        moveCounter++;
    }   
    fclose(file);
    printf("Correct moves: %d\n", moveCounter);
    if(checkIfWin(&gameBoard)) {
        printf("Success!\n");
    } else {
        printf("Failure!\n");
    }
    freeBoard(&gameBoard);
}
