#include "../include/game.h"
#include <conio.h>

int main() {
    setupWindowsConsole();
    int currentSize = showSplashScreen();
    
    Stone board[BOARD_SIZE][BOARD_SIZE];
    initBoard(board, currentSize);
    
    Stack history;
    initStack(&history);
    
    int moveCount = 0;
    int maxMoves = currentSize * currentSize;
    Stone currentPlayer = STONE_X;
    int cursorRow = currentSize / 2, cursorCol = currentSize / 2;
    bool gameRunning = true;

    while (gameRunning && moveCount < maxMoves) {
        printf("%s", ANSI_CLEAR);
        printf("=== CARO %dx%d ===\n", currentSize, currentSize);
        displayBoard(board, currentSize, cursorRow, cursorCol);
        drawStatusBar(cursorCol, cursorRow, 0);

        int ch = _getch();
        if (ch == 224) { // Di chuyen
            ch = _getch();
            if (ch == 72 && cursorRow > 0) cursorRow--;
            if (ch == 80 && cursorRow < currentSize - 1) cursorRow++;
            if (ch == 75 && cursorCol > 0) cursorCol--;
            if (ch == 77 && cursorCol < currentSize - 1) cursorCol++;
        } 
        else if (ch == 13 || ch == 32) { // Danh co
            if (board[cursorRow][cursorCol] == STONE_NA) {
                board[cursorRow][cursorCol] = currentPlayer;
                Move m = {cursorRow, cursorCol, currentPlayer};
                pushMove(&history, m);
                moveCount++;

                if (checkWinner(board, currentSize, cursorRow, cursorCol, currentPlayer)) {
                    printf("%s", ANSI_CLEAR);
                    displayBoard(board, currentSize, cursorRow, cursorCol);
                    printf("\nNGUOI CHOI %c THANG!\n", currentPlayer);
                    gameRunning = false;
                }
                currentPlayer = (currentPlayer == STONE_X) ? STONE_O : STONE_X;
            }
        }
    }
    return 0;
}
