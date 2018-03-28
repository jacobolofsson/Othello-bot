#ifndef IO_H
#define IO_H

enum IO_state {WAITING, AI_THINKING, MAKING_MOVE, READING_BOARD, ERROR};

void IO_init(void);

void IO_display(enum IO_state);

#endif // IO_H
