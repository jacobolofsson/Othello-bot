#ifndef IO_H
#define IO_H

#include "game.hpp"
#include "config.hpp"

// IO class that controls the input and output for the application.
// setup() must be called before any other method calls.
class IO {
    public:
        IO(Board<4,4> *b, Coordinate *c);

        void setup(void);
        void write(const int state);
        bool isNewTurn(void);

    private:
       Board<4,4> *board;
       Coordinate *AImove;

       static const int BUTTON_PIN = CONF_IO_BUTTON_PIN;
       static constexpr int LED_PINS[] = {
           CONF_IDLE_LED_PIN,
           CONF_READING_LED_PIN,
           CONF_THINKING_LED_PIN,
           CONF_MOVING_LED_PIN,
           CONF_GAMEOVER_LED_PIN,
           CONF_ERROR_LED_PIN
       };
       static constexpr int N_LEDS = sizeof(LED_PINS)/sizeof(LED_PINS[0]);
};

#endif // IO_H
