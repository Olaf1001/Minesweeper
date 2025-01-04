#include <stdio.h>
#include "include/board.h"
#include "include/game.h"

int main()
{

    printf("Welcome to Minesweeper game!\n");

    Board boardGame;

    initializeBoard(&boardGame, 10, 5);

    startGame();

    return 0;
}