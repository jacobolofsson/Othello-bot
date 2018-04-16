#ifndef AI_H
#define AI_H

#include "game.hpp"

// An AI that will provide the best move for a game of othello
// given enough time to think.
// Example:
//      AI ai = AI(game, player);
//      for (int i = 0; i<1000; ++i) {
//          ai.think();
//      };
//      bestMove = getBestMove();
class AI {
    public:
        AI(Game g, Player p);

        void think(void);
        int getNumMoves(void) const { return nAvaliableMoves; };
        Coordinate getBestMove(void) const;

    private:
        // Structure that holds data for the simulations the AI
        // uses to calculate the best move
        struct Simulation {
            Game game {Game(Board<4,4>())};
            Player turn;
            Coordinate startCoord;
            int nSimulations {0};
            int nWins {0};
            float getScore(void) const {
                return nSimulations == 0 ? 0 : nWins / (float) nSimulations;
            };
        };

        const Game currentGame;
        const Player AIplayer;
        static const int BUFFER_SIZE = 20;
        Simulation simulations[BUFFER_SIZE];
        int currentSim {0};
        int nAvaliableMoves {0};

        void step(Simulation s);
        void reset(Simulation s);
};

#endif // AI_H
