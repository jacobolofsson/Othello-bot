#include "IO.hpp"
#include <Arduino.h>

const int WAITING_LED = 1;
const int AI_THINKING_LED = 2;
const int MAKING_MOVE_LED = 3;
const int READING_BOARD_LED = 4;

const int START_BUTTON = 10;
int start_button_state = 0;


void IO_init(void) {
    pinMode(WAITING_LED, OUTPUT);
    pinMode(AI_THINKING_LED, OUTPUT);
    pinMode(MAKING_MOVE_LED, OUTPUT);
    pinMode(READING_BOARD_LED, OUTPUT);

    pinMode(START_BUTTON, INPUT);
}

void display_state(enum IO_state s) {
    digitalWrite(WAITING_LED, LOW);
    digitalWrite(AI_THINKING_LED, LOW);
    digitalWrite(MAKING_MOVE_LED, LOW);
    digitalWrite(READING_BOARD_LED, LOW);

    switch(s) {
        case WAITING:
            digitalWrite(WAITING_LED, HIGH);
            break;
        case READING_BOARD:
            digitalWrite(MAKING_MOVE_LED, HIGH);
            break;
        case AI_THINKING:
            digitalWrite(AI_THINKING_LED, HIGH);
            break;
        case MAKING_MOVE:
            digitalWrite(MAKING_MOVE_LED, HIGH);
            break;
        case ERROR:
            // ERROR handling?
            break;
    }
}

int IO_is_next_move() {
    start_button_state = digitalRead(START_BUTTON);
    return (start_button_state == HIGH) ? READING_BOARD : WAITING;
}
