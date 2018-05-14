#ifndef MOVE_PLANNER_H
#define MOVE_PLANNER_H

#include "config.hpp"
#include "game.hpp"

#include <AFMotor.h>
#include <Servo.h>

class MovePlanner {
    public:
        MovePlanner();

        void setup(void);
        void write(void);
        void addMove(Coordinate c, Player p); 
        bool isDone(void);

    private:
        AF_Stepper xMotor = Stepper(CONF_STEPPER_STEPS, 1);
        AF_Stepper yMotor = Stepper(CONF_STEPPER_STEPS, 2);
        Servo zMotor = Servo();

        enum Action {MOVE_TO_TARGET, LOWER_ARM, RAISE_ARM, PICK_PIECE, DROP_PIECE};
        enum Action actQueue[CONF_PLANNER_QUEUE_SZ];
        int actQueueSize = 0;
        int currentActionId;
        enum Magnet {NEGATIVE, POSITIVE};
        int targetX;
        int targetY;
        enum Magnet targetPolarity;
        enum Magnet currentPolarity = NEGATIVE;
        int currentX = CONF_STEPPER_START_X;
        int currentY = CONF_STEPPER_START_Y;

        void reset(void);
};

#endif // MOVE_PLANNER_H
