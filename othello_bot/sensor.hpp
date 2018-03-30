#ifndef SENSOR_H
#define SENSOR_H

#include "game.hpp"

class Sensor {
    public:
        Sensor(int analoguePins[16]);

        void read(void);
        
        Board getBoard(void) const;
};
#endif // SENSOR_H
