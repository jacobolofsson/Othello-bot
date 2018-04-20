#include "sensor.hpp"
#include "game.hpp"

#include "Arduino.h"

constexpr int Sensor::pins[];

// Initializes the input pins for the sensors. Must be called
// before any calls to read().
void Sensor::setup(void) {
    for (int i = 0; i <N_SENSORS; ++i) {
        pinMode(pins[i], INPUT);
    };
};
// Reads the data from one sensor position and advances the
// position to be read next time one step.
// Because only one position is read at a time this function
// should be called contiously and getBoard() only when the
// data is needed to ensure updated position data.
void Sensor::read(void) {
    sensorVals[sensorId] = analogRead(pins[sensorId]);
    sensorId = (sensorId + 1)%N_SENSORS;
};
// Gets the latest data from the sensors in the form of a
// populated Board<> class
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
// Helper function to translate pin position to a board
// coordinate. This assumes that the pins are ordered
// from left to right, starting in the top left corner.
Coordinate Sensor::pinToCoord(const int pin) {
    Coordinate c;
    c.rowPos = pin % 4;
    c.colPos = (pin - (pin%4))/4;
    return c;
};
