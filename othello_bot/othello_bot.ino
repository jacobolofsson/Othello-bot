#include "game.hpp"
#include "sensor.hpp"
#include "AI.hpp"
#include "move_planner.hpp"
#include "IO.hpp"

#define X_STEPPER_PINS 22,24,26,28
#define Y_STEPPER_PINS 23,25,27,29
#define Z_SERVO_PIN 30
#define SENSOR_PINS A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15

const unsigned long AI_TIME_LIMIT_MS = 5000;
unsigned long startTime;
const int STEPPER_STEPS = 100;

Sensor sensor({SENSOR_PINS});
MovePlanner planner(Stepper(STEPPER_STEPS, X_STEPPER_PINS), Stepper(STEPPER_STEPS, Y_STEPPER_PINS), Servo());
IO io;

Player AIplayer = BLACK;
Coordinate AImove;
Board<4,4> board;
AI ai(Game(board), AIplayer);

enum state {IDLE, RESET_AI, THINK} state = IDLE;

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
