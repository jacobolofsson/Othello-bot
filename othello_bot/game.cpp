#include "game.hpp"
//template class Board<>;

bool Coordinate::operator==(const Coordinate &rhs) const {
    return (this->colPos == rhs.colPos) && (this->rowPos == rhs.rowPos);
}

void Board::put(const Player p, const Coordinate c) {
}
void Board::flip(const Coordinate c) {
}
int Board::getPoints(const Player p) const {
    return 0;
}
bool Board::isEmpty(const Coordinate c) const {
    return 0;
}
bool Board::isInBounds(const Coordinate c) {
    return false;
}
Player Board::getPlayer(const Coordinate c) const {
    return WHITE;
}
Coordinate Board::step(const Coordinate c, const Coordinate::Direction d) {
    return {0,0};
}


Game::Game(Board b) {
}
Coordinate* Game::getLegalMoves(const Player p) const {
    return 0;
}
bool Game::isOver() const {
    return 0;
}
bool Game::isWinner(const Player p) const {
    return false;
}
void Game::applyMove(const Player p, const Coordinate c) {

}
