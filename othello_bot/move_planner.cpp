#include "move_planner.hpp"

#include "config.hpp"

MovePlanner::MovePlanner() {};
void MovePlanner::setup(void) {
    xMotor.setSpeed(CONF_STEPPER_RPM);
    yMotor.setSpeed(CONF_STEPPER_RPM);
    zMotor.attach(CONF_Z_SERVO_PIN);
    reset();
};
void MovePlanner::write(void) {
    int xSteps;
    int ySteps;
    if (!isDone()) {
        switch(actQueue[currentActionId]) {
            case MOVE_TO_TARGET:
                // To get better control keep steps per call to a maximum
                xSteps = constrain(targetX-currentX, -CONF_MAX_STEPS, CONF_MAX_STEPS);
                ySteps = constrain(targetY-currentY, -CONF_MAX_STEPS, CONF_MAX_STEPS);
                xMotor.step(xSteps, DOUBLE, FORWARD);
                yMotor.step(ySteps, DOUBLE, FORWARD);
                currentX += xSteps;
                currentY += ySteps;
                if ( (xSteps == 0) && (ySteps == 0) ) {
                    currentActionId++;
                };
                break;
            case LOWER_ARM:
                zMotor.write(CONF_SERVO_MAX);
                //TODO Do we ned a delay here?
                currentActionId++;
                break;
            case RAISE_ARM:
                zMotor.write(0);
                currentActionId++;
                break;
            case PICK_PIECE:
                currentPolarity = targetPolarity;
                // TODO delay here?
                currentActionId++;
                break;
            case DROP_PIECE:
                currentPolarity = (targetPolarity == NEGATIVE) ? POSITIVE : NEGATIVE;
                // TODO delay here?
                currentActionId++;
                break;
        };
    };
    writeMagnet(currentPolarity);
};        
void MovePlanner::addMove(Coordinate c, Player p) {
    targetX = c.rowPos*CONF_STEPS_PER_COORD_X;
    targetY = c.colPos*CONF_STEPS_PER_COORD_Y;
    targetPolarity = (p == WHITE) ? POSITIVE : NEGATIVE;
    currentActionId = 0;
    enum Action newActions[] = {MOVE_TO_TARGET, LOWER_ARM, DROP_PIECE, RAISE_ARM};
    actQueueSize = sizeof(newActions)/sizeof(newActions[0]);
    for (int i = 0; i < actQueueSize; ++i) {
        actQueue[i] = newActions[i];
    };

};
bool MovePlanner::isDone(void) {
    return currentActionId >= actQueueSize;
};
void MovePlanner::reset(void) {};
void MovePlanner::writeMagnet(Magnet polarity) {
    if(polarity == NEGATIVE) {
        digitalWrite(CONF_MAGNET_PIN_NEG, HIGH);
	digitalWrite(CONF_MAGNET_PIN_POS, LOW);
    } else if(polarity == POSITIVE) {
        digitalWrite(CONF_MAGNET_PIN_NEG, LOW);
	digitalWrite(CONF_MAGNET_PIN_POS, HIGH);
    } else {
        digitalWrite(CONF_MAGNET_PIN_NEG, LOW);
	digitalWrite(CONF_MAGNET_PIN_POS, LOW);
    };
};
