#include "game.hpp"

bool Coordinate::operator==(const Coordinate &rhs) const {
    return (this->colPos == rhs.colPos) && (this->rowPos == rhs.rowPos);
}
bool Coordinate::operator<(const Coordinate &rhs) const {
    return (this->colPos < rhs.colPos) || ( (this->colPos == rhs.colPos) && (this->rowPos < rhs.rowPos) );
}
bool Coordinate::operator<=(const Coordinate &rhs) const {
    return (*this == rhs) || (*this < rhs);
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
int Game::getLegalMoves(const Player p, Coordinate buffer[]) const {
    Coordinate dummy_buffer[BUFFER_SIZE];
    int i = 0;
    Coordinate c = this->board.getFirst();
    while (c <= this->board.getLast()) {
        if( this->board.isEmpty(c) && (this->getsFlippedByMove(p, c, dummy_buffer) > 0) ) {
            buffer[i] = c;  
            ++i;
        };
        c = this->board.iterate(c);
    }; 
    return i;
}
Player Game::nextPlayer(const Player p) {
    return p == BLACK ? WHITE : BLACK;
}
bool Game::isOver() const {
    Coordinate dummy_buffer[BUFFER_SIZE];
    return (0 == this->getLegalMoves(BLACK, dummy_buffer)) && (0 == this->getLegalMoves(WHITE, dummy_buffer));
}
bool Game::isWinner(const Player p) const {
    return this->isOver() && ( this->getPoints(p) > this->getPoints(nextPlayer(p)) );
}
int Game::getPoints(const Player p) const {
    int points = 0;
    Coordinate c = this->board.getFirst();
    while (c <= this->board.getLast()) {
        if( !this->board.isEmpty(c) && this->board.getPlayer(c) == p ) {
            points++;
        };
        c = this->board.iterate(c);
    }; 
    return points;
}
void Game::applyMove(const Player p, const Coordinate c) {
    this->board.put(p, c);
    Coordinate coordBuffer[BUFFER_SIZE];
    int nToFlip = getsFlippedByMove(p, c, coordBuffer);
    for (int i = 0; i < nToFlip; i++) {
        this->board.flip(coordBuffer[i]);
    };
}
int Game::getsFlippedByMove(const Player p, const Coordinate c, Coordinate buffer[]) const {
    int count = 0;
    // Because we cant know if the positions should be added we need to use
    // temporary variables
    Coordinate c_temp; 
    Coordinate buffer_temp[BUFFER_SIZE];
    int count_temp;
    // Traverse the board in all directions from the given coordinate c.
    for (int dir = Coordinate::firstDir; dir <= Coordinate::lastDir; dir++) {
        c_temp = c;
        c_temp = c_temp.step(Coordinate::Direction(dir));
        count_temp = 1;
        // Keep stepping until edge or empty position is detected
        while( board.isInBounds(c_temp) && !board.isEmpty(c_temp) ) {
            // If the current coordinate is held by the player add all
            // traversed positions to the buffer and stop stepping in
            // this direction, else keep stepping.
            if (board.getPlayer(c_temp) == p) {
                for (int i = 0; i < count_temp; i++) {
                    buffer[count+i] = buffer_temp[i];
                };
                count += (count_temp - 1);
                break;
            };
            buffer_temp[(count_temp - 1)] = c_temp;
            count_temp++;
            c_temp = c_temp.step(Coordinate::Direction(dir));
        };
    };

    return count;
}
