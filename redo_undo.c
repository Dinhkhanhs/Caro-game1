#include <stdbool.h>

// ===== KIEU DU LIEU =====
typedef enum {
    NA = 0,
    BLACK = 1,
    WHITE = 2
} Stone;

typedef struct {
    int row;
    int col;
    Stone player;
} Move;

#define MAX_MOVES 100

typedef struct {
    Move data[MAX_MOVES];
    int top;
} Stack;

// ===== STACK CO BAN =====
void initStack(Stack *s) {
    s->top = -1;
}

bool isEmpty(Stack *s) {
    return s->top == -1;
}

bool isFull(Stack *s) {
    return s->top == MAX_MOVES - 1;
}

// pushMove
bool pushMove(Stack *s, Move m) {
    if (isFull(s)) return false;
    s->data[++s->top] = m;
    return true;
}

// popMove
bool popMove(Stack *s, Move *m) {
    if (isEmpty(s)) return false;
    *m = s->data[s->top--];
    return true;
}

// ===== UNDO =====
// xoa nuoc cuoi tren board va dua sang redo
bool undo(Stack *history, Stack *redoStack,
          Stone board[][50], Stone *currentPlayer, int *moves) {
    
    Move m;
    if (!popMove(history, &m)) return false;

    board[m.row][m.col] = NA;

    pushMove(redoStack, m);

    *currentPlayer = m.player;
    (*moves)--;

    return true;
}

// ===== REDO =====
// dat lai nuoc vua undo
bool redo(Stack *history, Stack *redoStack,
          Stone board[][50], Stone *currentPlayer, int *moves) {
    
    Move m;
    if (!popMove(redoStack, &m)) return false;

    board[m.row][m.col] = m.player;

    pushMove(history, m);

    *currentPlayer = (m.player == BLACK) ? WHITE : BLACK;
    (*moves)++;

    return true;
}
