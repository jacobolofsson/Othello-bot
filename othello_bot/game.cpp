#include "game.hpp"

bool Coordinate::operator==(const Coordinate &rhs) const {
    return (this->colPos == rhs.colPos) && (this->rowPos == rhs.rowPos);
}
Coordinate Coordinate::step(const Coordinate::Direction d) {
    Coordinate temp = *this;
    switch (d) {
        case SW :
            return this->step(S).step(W);
        case Se :
            return this->step(S).step(E);
        case NW :
            return this->step(N).step(W);
        case NE :
            return this->step(N).step(E);
        case N :
            --temp.colPos;
            break;
        case S :
            ++temp.colPos;
            break;
        case W :
            --temp.rowPos;
            break;
        case E :
            ++temp.rowPos;
            break;
    }
    return temp;
}


Game::Game(Board<4,4> b) {
    this->board = b;
}
int Game::getLegalMoves(const Player p) const {
    return 0;
}
int Game::getLegalMoves(const Player p, Coordinate buffer[]) const {
    return 0;
}
Player Game::nextPlayer(const Player p) {
    return p == BLACK ? WHITE : BLACK;
}
bool Game::isOver() const {
    return 0 == this->getLegalMoves(BLACK) && 0 == this->getLegalMoves(WHITE);
}
bool Game::isWinner(const Player p) const {
    return this->isOver() && ( this->getPoints(p) > this->getPoints(nextPlayer(p)) );
}
int Game::getPoints(const Player p) const {
    return 0;
}
void Game::applyMove(const Player p, const Coordinate c) {

}
