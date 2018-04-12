#ifndef MOVE_PLANNER_H
#define MOVE_PLANNER_H

#include <Stepper.h>
#define N_STEPPER_STEPS 100 
#include <Servo.h>

//Stepper xMotor;
//Stepper yMotor;
//Servo zMotor;

enum move {X_STEP_FORWARD, X_STEP_BACKWARD, PICK_PIECE, DROP_PIECE};

#endif // MOVE_PLANNER_H
