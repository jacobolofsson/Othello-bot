#ifndef AI_H
#define AI_H

#include "game.h"

struct move think(board_t game_state, player_t AI_color, time_t time_limit);

#endif // AI_H
