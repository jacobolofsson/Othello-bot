#include "game.h"
#include "sensor.h"
#include "AI.h"
#include "move_planner.h"
#include "IO.h"

enum IO_state current_state;
enum IO_state next_state;

struct game_state game_state;

struct game_move next_move;

void setup() {
    IO_init();
    sensor_init();
    planner_init();

    current_state = WAITING;
}

void loop() {
    IO_display(current_state);

    switch(current_state) {
        case WAITING:
            break;
        case READING_BOARD:
            game_state = sensor_read_board();
            next_state = AI_THINKING;
            break;
        case AI_THINKING:
            next_move = AI_think(game_state, BLACK, 1000); 
            next_state = MAKING_MOVE;
            break;
        case MAKING_MOVE:
            planner_execute(next_move);
            next_state = WAITING;
            break;
        case ERROR:
            // ERROR handling?
            break;
    }
    current_state = next_state;

}
