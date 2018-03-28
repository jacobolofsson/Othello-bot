#ifndef SENSOR_H
#define SENSOR_H

#include "game.h"

void sensor_init(void);

struct game_state sensor_read_board();

#endif // SENSOR_H
