#ifndef SENSOR_H
#define SENSOR_H

#include "config.hpp"
#include "game.hpp"
class Sensor {
    public:
        void setup(void);
        void read(void);
        Board<4,4> getBoard(void) const;

    private:
        static constexpr int UPPER_LIM = CONF_UPPER_SENS_LIM;
        static constexpr int LOWER_LIM = CONF_LOWER_SENS_LIM;
        static constexpr int N_SENSORS = CONF_N_SENSORS;
        static constexpr int pins[N_SENSORS] = CONF_SENSOR_PINS_V;

        int sensorVals[N_SENSORS];
        int sensorId = 0;

        static Coordinate pinToCoord(const int pin);
};
#endif // SENSOR_H
