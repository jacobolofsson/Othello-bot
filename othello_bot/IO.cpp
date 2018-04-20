#include "IO.hpp"
#include "config.hpp"

#include "game.hpp"
#include "Arduino.h"

constexpr int IO::LED_PINS[];

IO::IO(Board<4,4> *b, Coordinate *c) : board(b), AImove(c) {};

// Set up the instance for usage
void IO::setup(void) {
    pinMode(BUTTON_PIN, INPUT);
    for (int i = 0; i < N_LEDS; ++i) {
        pinMode(LED_PINS[i], OUTPUT);
    };
    DEBUG_SETUP;
};
// Outputs the current state by lighting corresponding LEDS
void IO::write(const int state) {
    DEBUG_STATE(state);
    for (int i = 0; i < N_LEDS; ++i) {
        digitalWrite(LED_PINS[i], LOW);
    };
    if (state < N_LEDS) {
        digitalWrite(LED_PINS[state], HIGH); 
    };
};
bool IO::isNewTurn(void) {
    return digitalRead(BUTTON_PIN) == LOW;
};
