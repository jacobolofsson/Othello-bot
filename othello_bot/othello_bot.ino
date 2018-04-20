#include "config.hpp"
#include "game.hpp"
#include "sensor.hpp"
#include "AI.hpp"
#include "move_planner.hpp"
#include "IO.hpp"


const unsigned long AI_TIME_LIMIT_MS = 5000;
unsigned long startTime;

Sensor sensor;
MovePlanner planner;
IO io;

Player AIplayer = BLACK;
Coordinate AImove;
Board<4,4> board;
AI ai(Game(board), AIplayer);

enum state {IDLE, RESET_AI, THINK, MOVING} state = IDLE;

void setup() {
    sensor.setup();
    planner.setup();
    io.setup();
}

void loop() {
    switch(state) {
        case RESET_AI:
            board = sensor.getBoard(); 
            ai = AI(Game(board), AIplayer);
            startTime = millis();
            state = THINK;
            break;
        case THINK:
            if ( millis()-startTime < AI_TIME_LIMIT_MS ) {
                ai.think();
            } else {
                AImove = ai.getBestMove();
                planner.addMove(AImove, AIplayer);
                state = MOVING;
            };
            break;
        case MOVING:
            if (planner.isDone()) {
                state = IDLE;
            };
            break;
        case IDLE: // Intentional fall through to default:
        default:
            if (io.isNewTurn()) {
                state = RESET_AI;
            } else {
                state = IDLE;
            };
        break;
    };
    sensor.read();
    planner.write();
    io.write();
}
