#include "game.h"

void initStack(Stack *s) { s->top = -1; }
bool isEmpty(Stack *s) { return s->top == -1; }
bool isFull(Stack *s) { return s->top == BOARD_SIZE * BOARD_SIZE - 1; }

bool pushMove(Stack *s, Move m) {
    if (isFull(s)) return false;
    s->data[++s->top] = m;
    return true;
}

bool popMove(Stack *s, Move *m) {
    if (isEmpty(s)) return false;
    *m = s->data[s->top--];
    return true;
}
