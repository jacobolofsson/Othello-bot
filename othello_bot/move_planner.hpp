#ifndef MOVE_PLANNER_H
#define MOVE_PLANNER_H

#include "game.hpp"

#define N_STEPPER_STEPS 100 
#include <Stepper.h>
#include <Servo.h>

class MovePlanner {
    public:
        MovePlanner(Stepper x, Stepper y, Servo z);

        void setup(void);
        void write(void);
        void addMove(Coordinate c, Player p); 

    private:
        const Stepper xMotor;
        const Stepper yMotor;
        const Servo zMotor;

        enum action {X_STEP_FORWARD, X_STEP_BACKWARD, Y_STEP_FORWARD, Y_STEP_BACKWARD, PICK_PIECE, DROP_PIECE};

        void reset(void);
};

#endif // MOVE_PLANNER_H
