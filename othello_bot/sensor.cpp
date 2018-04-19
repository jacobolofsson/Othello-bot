#include "sensor.hpp"

#include "Arduino.h"

Sensor::Sensor(SensorArray arr) : sensors(arr) {};

void Sensor::setup(void) {
    for (int i = 0; i <16; ++i) {
        pinMode(sensors.pin[i], INPUT_PULLUP);
    };
};
void Sensor::read(void) {};
Board<4,4> Sensor::getBoard(void) const {};
