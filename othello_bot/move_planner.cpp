#include "move_planner.hpp"

MovePlanner::MovePlanner(Stepper x, Stepper y, Servo z) : xMotor(x), yMotor(y), zMotor(z) {};
void MovePlanner::setup(void) {};
void MovePlanner::write(void) {};
void MovePlanner::addMove(Coordinate c, Player p) {};
