#include "AI.hpp"
#include "random.hpp"

AI::AI(Game g, Player p) : game(g), AIplayer(p) {
    Coordinate tempBuffer[BUFFER_SIZE];
    nAvaliableMoves = game.getLegalMoves(AIplayer, tempBuffer);
    for (int i = 0; i<nAvaliableMoves; i++) {
        //simulations[i](g, p, tempBuffer[i]);
        simulations[i].startCoord = tempBuffer[i];
        reset(simulations[i]);
    };
};
void AI::think(void) {
    if( simulations[currentSim].game.isOver() ) {
        if( simulations[currentSim].game.isWinner(AIplayer) ) {
            simulations[currentSim].nWins++;
        }
        simulations[currentSim].nSimulations++;
        reset(simulations[currentSim]);
        currentSim = (currentSim + 1)%nAvaliableMoves;
    };
    step(simulations[currentSim]);
};
void AI::step(Simulation s) {
    Coordinate tempBuffer[BUFFER_SIZE];
    int tempAvaliableMoves = s.game.getLegalMoves(s.turn, tempBuffer);
    if (tempAvaliableMoves > 0) {
        s.game.applyMove( s.turn, tempBuffer[getRandom(tempAvaliableMoves)] );
    }
    s.turn = Game::nextPlayer(s.turn);
};
void AI::reset(Simulation s) {
    s.game = this->game;
    s.game.applyMove(this->AIplayer, s.startCoord);
    s.turn = Game::nextPlayer(this->AIplayer);
};

//AI::Simulation::Simulation(const Game g, const Player p, const Coordinate c) : game(g), turn(p), startCoord(c) {};
