#ifndef AI_H
#define AI_H

#include "game.hpp"

class AI {
    public:
        AI(Game g, Player p);

        void think(void);

        Coordinate getBestMove(void) const;
    private:
        const Game game;
        const Player AIplayer;
        struct Simulation {
            //Simulation(Game g, Player p, Coordinate c);
            Game game {Game(Board<4,4>())};
            Player turn;
            Coordinate startCoord;
            int nSimulations {0};
            int nWins {0};
        };
        void step(Simulation s);
        void reset(Simulation s);
        static const int BUFFER_SIZE = 20;
        Simulation simulations[BUFFER_SIZE];
        int currentSim;
        int nAvaliableMoves;
};

#endif // AI_H
