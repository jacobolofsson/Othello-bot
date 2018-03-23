#include "game.h"
#include "sensor.h"
#include "AI.h"
#include "move_planner.h"

const int WAITING_LED = 1;
const int AI_THINKING_LED = 2;
const int MAKING_MOVE_LED = 3;
const int READING_BOARD_LED = 4;

const int START_BUTTON = 10;
int start_button_state = 0;

enum state {WAITING, AI_THINKING, MAKING_MOVE, READING_BOARD, ERROR} current_state;

void setup() {

    pinMode(WAITING_LED, OUTPUT);
    pinMode(AI_THINKING_LED, OUTPUT);
    pinMode(MAKING_MOVE_LED, OUTPUT);
    pinMode(READING_BOARD_LED, OUTPUT);

    pinMode(START_BUTTON, INPUT);
    
    current_state = WAITING;
    game_state = init_game();
}

void loop() {
    digitalWrite(WAITING_LED, LOW);
    digitalWrite(AI_THINKING_LED, LOW);
    digitalWrite(MAKING_MOVE_LED, LOW);
    digitalWrite(READING_BOARD_LED, LOW);

    switch(current_state) {
        case WAITING:
            digitalWrite(WAITING_LED, HIGH);
            start_button_state = digitalRead(START_BUTTON);
            current_state = (start_button_state == HIGH) ? READING_BOARD : WAITING;
            break;
        case READING_BOARD:
            digitalWrite(MAKING_MOVE_LED, HIGH);
            game_state = read_board();
            current_state = AI_THINKING;
            break;
        case AI_THINKING:
            digitalWrite(AI_THINKING_LED, HIGH);
            next_move = think(game_state); 
            current_state = MAKING_MOVE;
            break;
        case MAKING_MOVE:
            digitalWrite(MAKING_MOVE_LED, HIGH);
            execute_move(next_move);
            current_state = WAITING;
            break;
        case ERROR:
            // ERROR handling?
            break;
    }

}
