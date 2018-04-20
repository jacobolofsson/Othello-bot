#include "AI.hpp"

#include "random.hpp"

// The AI is implemented by using a Monte-Carlo strategy. Random moves
// are applied until the game ends and the AI records if it was a win
// or lose. The best move is calculated by simply assigning each legal
// move with a score, which is the number of simulations starting with
// this move divided with the number that resulted in a win.

// WHen an AI object is constructed it adds all the legal moves from the
// current game supplied to the simulations vector
AI::AI(Game g, Player p) : currentGame(g), AIplayer(p) {
    Coordinate tempBuffer[BUFFER_SIZE];
    nAvaliableMoves = currentGame.getLegalMoves(AIplayer, tempBuffer);
    for (int i = 0; i<nAvaliableMoves; ++i) {
        simulations[i].startCoord = tempBuffer[i];
        reset(simulations[i]);
    };
};
// This function initializes the RNG that drives the monte carlo simulations
void AI::setup(void) {
    initRandom();
};
// This function steps the AIs current simulation one step.
// If the simulation is over the AI adds the score to the simulation
// vector, resets the game and then switches the current simulation
// to the next in turn (circularly).
void AI::think(void) {
    if( nAvaliableMoves > 0) {
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
};
// This function iterates through the simulation vector that contains the
// the coordinates for all the legal moves and the scores associated with
// them. It picks the one with best score.
Coordinate AI::getBestMove(void) const {
    float bestScore = -1000.0;
    int bestIndex = -1;
    float score = 0.0;
    for (int i = 0; i<nAvaliableMoves; ++i) {
        score = simulations[i].getScore();
        if ( score > bestScore) {
            bestScore = score;
            bestIndex = i;
        };
    };
    return simulations[bestIndex].startCoord;
};
// This steps the simulation forward one step by applying one legal move and
// then switching player.
void AI::step(Simulation s) {
    Coordinate tempBuffer[BUFFER_SIZE];
    int tempAvaliableMoves = s.game.getLegalMoves(s.turn, tempBuffer);
    // If no avaliable moves: pass
    if (tempAvaliableMoves > 0) {
        s.game.applyMove( s.turn, tempBuffer[getRandom(tempAvaliableMoves)] );
    }
    s.turn = Game::nextPlayer(s.turn);
};
// This function resets a simulation by setting the game to the input game
// of the AI and applying the starting move of the simulation.
void AI::reset(Simulation s) {
    s.game = this->currentGame;
    s.game.applyMove(this->AIplayer, s.startCoord);
    s.turn = Game::nextPlayer(this->AIplayer);
};
