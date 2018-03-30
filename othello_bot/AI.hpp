#ifndef AI_H
#define AI_H

#include "game.hpp"

class AI {
    public:
        AI(Game newGame);

        void think();

        Coordinate getBestMove() const;
};

#endif // AI_H
