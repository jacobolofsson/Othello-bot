#ifndef AI_H
#define AI_H

#include "game.h"

struct game_move AI_think(struct game_state gs, enum game_color AI_color, int time_limit_ms);

#endif // AI_H
