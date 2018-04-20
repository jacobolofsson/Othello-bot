#include "sensor.hpp"
#include "game.hpp"

#include "Arduino.h"

constexpr int Sensor::pins[];

void Sensor::setup(void) {
    for (int i = 0; i <N_SENSORS; ++i) {
        pinMode(pins[i], INPUT);
    };
};
void Sensor::read(void) {
    sensorVals[sensorId] = analogRead(pins[sensorId]);
    sensorId = (sensorId + 1)%N_SENSORS;
};
Board<4,4> Sensor::getBoard(void) const {
    Board<4,4> board;
    for (int i = 0; i < N_SENSORS; ++i) {
        if (sensorVals[i] > UPPER_LIM) {
            board.put(BLACK, pinToCoord(i));
        } else if (sensorVals[i] < LOWER_LIM) {
            board.put(WHITE, pinToCoord(i));
        };
    };
    return board;
};
Coordinate Sensor::pinToCoord(const int pin) {
    Coordinate c;
    c.rowPos = pin % 4;
    c.colPos = (pin - (pin%4))/4;
    return c;
};
