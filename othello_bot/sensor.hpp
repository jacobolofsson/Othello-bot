#ifndef SENSOR_H
#define SENSOR_H

#include "game.hpp"
        struct SensorArray {
            const int pin[16];
        };

class Sensor {
    public:
        Sensor(SensorArray arr);

        void setup(void);
        void read(void);
        Board<4,4> getBoard(void) const;

    private:
        Board<4,4> board;
        const SensorArray sensors;
};
#endif // SENSOR_H
