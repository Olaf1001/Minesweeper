#include <stdio.h>
#include <stdlib.h>

#include "../include/board.h"
#include "../include/game.h"
#include "../include/score.h"


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
        char userName[256];
        if(command == 'f') {
                flagCell(board, row, col);
        } else if (command == 'r') {
                revealCell(board, row, col, gameOver, mineCount);
                if (*gameOver) {
                        displayBoard(board, *gameOver);
                        if(mineCount != 0) {
                                printf("Please write your nickname for the scoreboard: ");
                                scanf("%s", userName);
                                fillScoreboard(userName, board->score);    
                        }
                } else if(checkIfWin(board)) {
                        printf("Congratulations! You won the game! \n");
                        *gameOver = 1;
                        displayBoard(board, *gameOver);
                        if(mineCount != 0) {
                                printf("Please write your nickname for the scoreboard: ");
                                scanf("%s", userName);
                                fillScoreboard(userName, board->score);    
                        }
                }
        } else {
                printf("[!] Unknown command, Try again. \n");
        }
}

void selectLevel(int * boardLevel, int * boardRows, int * boardCols, int * boardMines) {
    int userLevel;

    printf("Welcome to Minesweeper game!\n");
    printf("Select game difficulty (1 - easy, 2 - medium, 3 - hard, 4 - custom): ");

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
            break;
        }
    }

    if(userLevel == 4) {
            *boardLevel = 1;
            printf("x = ");
            scanf("%d", boardRows);

            printf("y = ");
            scanf("%d", boardCols);

            printf("mines = ");
            scanf("%d", boardMines);

            if((*boardRows * *boardCols) < *boardMines) {
                printf("[!] Numer of mines is greater than cells.\nEnter new mine amount: ");
                scanf("%d", boardMines);
            }

            printf("Level: CUSTOM, Rows: %d, Cols: %d, Mines: %d\n", *boardRows, *boardCols, *boardMines);
    }
}