#ifndef MOVE_PLANNER_H
#define MOVE_PLANNER_H

#include "game.h"
void planner_init(void);

void planner_execute(struct game_move m);

#endif // MOVE_PLANNER_H
