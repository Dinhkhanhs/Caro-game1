#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- CAU HINH ---
#define BOARD_SIZE 15
#define WIN_COUNT 5

// Thong nhat dung char de de hien thi
typedef char Stone;
#define STONE_X 'X'
#define STONE_O 'O'
#define STONE_NA ' '

// --- CAU TRUC DU LIEU ---
typedef struct {
    int row;
    int col;
    Stone player;
} Move;

typedef struct {
    Move data[BOARD_SIZE * BOARD_SIZE];
    int top;
} Stack;

typedef struct {
    int blackWins;
    int whiteWins;
    int draws;
} ScoreBoard;

// --- MA MAU ANSI ---
#define ANSI_RESET   "\x1B[0m"
#define ANSI_CLEAR   "\x1B[2J\x1B[H"
#define ANSI_RED     "\x1B[91m"
#define ANSI_CYAN    "\x1B[96m"
#define ANSI_YELLOW  "\x1B[93m"
#define ANSI_GRAY    "\x1B[90m"

// --- KY TU VE HOP ---
#define H_LINE "\xE2\x94\x80"
#define V_LINE "\xE2\x94\x82"
#define CROSS  "\xE2\x94\xBC"

// --- KHAI BAO HAM ---
void setupWindowsConsole();
int showSplashScreen();
void initBoard(Stone board[BOARD_SIZE][BOARD_SIZE], int size);
void displayBoard(Stone board[BOARD_SIZE][BOARD_SIZE], int size, int cursorRow, int cursorCol);
bool checkWinner(Stone board[BOARD_SIZE][BOARD_SIZE], int size, int r, int c, Stone player);
void drawStatusBar(int cursorX, int cursorY, int timeRemaining);

// Stack functions
void initStack(Stack *s);
bool pushMove(Stack *s, Move m);
bool popMove(Stack *s, Move *m);

#endif
