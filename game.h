#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

// --- CAU HINH GAME MAC DINH ---
#define BOARD_SIZE 15

// --- CHUOI THOAT ANSI ---
#define ANSI_RESET   "\x1B[0m"
#define ANSI_CLEAR   "\x1B[2J\x1B[H"
#define ANSI_RED     "\x1B[91m"
#define ANSI_CYAN    "\x1B[96m"
#define ANSI_GRAY    "\x1B[90m"
#define ANSI_YELLOW  "\x1B[93m" 
#define ANSI_BG_DARK "\x1B[100m"

// --- KY TU VE HOP ---
#define H_LINE "\xE2\x94\x80"
#define V_LINE "\xE2\x94\x82"
#define CROSS  "\xE2\x94\xBC"

// --- CAU TRUC DU LIEU ---
typedef enum { NA = 0, BLACK = 1, WHITE = 2 } Stone;

typedef struct {
    int row;
    int col;
    Stone player;
} Move;

typedef struct {
    int blackWins;
    int whiteWins;
    int draws;
} ScoreBoard;

// Thêm vào sau struct
extern Stone board[BOARD_SIZE][BOARD_SIZE];
extern ScoreBoard gameScore;

// --- KHAI BAO NGUYEN MAU HAM (API) ---

// Console
void setupWindowsConsole();
int showSplashScreen(); 

// Ban co (Da them tham so int size)
void initBoard(Stone board[BOARD_SIZE][BOARD_SIZE], int size);
void displayBoard(Stone board[BOARD_SIZE][BOARD_SIZE], int size, int cursorRow, int cursorCol);

// Logic (Da them tham so int size)
int countDirection(Stone board[BOARD_SIZE][BOARD_SIZE], int size, int r, int c, int dr, int dc, Stone player);
bool checkWinner(Stone board[BOARD_SIZE][BOARD_SIZE], int size, int lastRow, int lastCol, Stone player);

// Diem so
void loadScore(ScoreBoard *sb);
void saveScore(ScoreBoard sb);
void updateScore(ScoreBoard *sb, Stone winner);

#endif // GAME_H
