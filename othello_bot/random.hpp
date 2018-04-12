#ifndef RANDOM_H
#define RANDOM_H

#ifdef ARDUINO
    #include "Arduino.h"
    void initRandom(void) {
        randomSeed(analogRead(0));
    };
    int getRandom(int max) {
        return random(0, max);
    };
#else
    #include <cstdlib>
    void initRandom(void) {
        srand(0);
    };
    int getRandom(int max) {
        return rand()%max;
    };
#endif //NO_TEST



#endif //RANDOM_H
