#include "game.hpp"

// This file contains the implementation of a Game-class used to implement
// the rules of the game reversi (othello).

// Overload comparison operators to compare different coordinates
bool Coordinate::operator==(const Coordinate &rhs) const {
    return (this->colPos == rhs.colPos) && (this->rowPos == rhs.rowPos);
}
bool Coordinate::operator<(const Coordinate &rhs) const {
    return (this->colPos < rhs.colPos) || ( (this->colPos == rhs.colPos) && (this->rowPos < rhs.rowPos) );
}
bool Coordinate::operator<=(const Coordinate &rhs) const {
    return (*this == rhs) || (*this < rhs);
}
// This function returns the coordinate which is one steo in direction
// d from the coordinate it is applied to
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
// This function takes a player and a buffer. The buffer is filled with all
// the positions the player can place a move on and the return value is
// the number of elements in the buffer.
int Game::getLegalMoves(const Player p, Coordinate buffer[]) const {
    Coordinate dummy_buffer[BUFFER_SIZE];
    int numLegalMoves = 0;
    // Traverse board and add coordinates to buffer if it is legal move
    Coordinate c = this->board.getFirst();
    while (c <= this->board.getLast()) {
        // A move is legal if it flips 1 or more opponent pieces
        if( this->board.isEmpty(c) && (this->getsFlippedByMove(p, c, dummy_buffer) > 0) ) {
            buffer[numLegalMoves] = c;  
            ++numLegalMoves;
        };
        c = this->board.iterate(c);
    }; 
    return numLegalMoves;
}
// This function returns the next player in turn
Player Game::nextPlayer(const Player p) {
    return p == BLACK ? WHITE : BLACK;
}
// This function returns true if there are no legal moves for both players
bool Game::isOver() const {
    Coordinate dummy_buffer[BUFFER_SIZE];
    return (0 == this->getLegalMoves(BLACK, dummy_buffer)) && (0 == this->getLegalMoves(WHITE, dummy_buffer));
}
bool Game::isWinner(const Player p) const {
    return this->isOver() && ( this->getPoints(p) > this->getPoints(nextPlayer(p)) );
}
// The points in othello is just the number of pieces of the players color on the board
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
// This function applies a move to the game. It places a piece on the board and flips
// the opponent pieces that is effected by the move
void Game::applyMove(const Player p, const Coordinate c) {
    this->board.put(p, c);
    Coordinate coordBuffer[BUFFER_SIZE];
    int nToFlip = getsFlippedByMove(p, c, coordBuffer);
    for (int i = 0; i < nToFlip; i++) {
        this->board.flip(coordBuffer[i]);
    };
}
// Returns a string representation of the game in the buffer given
void Game::toString(char *s) const {
    for(Coordinate c = board.getFirst(); c <= board.getLast(); c = board.iterate(c)) { 
        if(board.isEmpty(c)) {
            *s = '_';
        } else if (board.getPlayer(c) == WHITE) {
            *s = 'O';
        } else {
            *s = 'X';
        };
        s++;
        if (c.rowPos % 4 == 3) {
            *s = '\n';
            s++;
        };
    };
    *s = '\0';
    return;
};
// Takes a move (player + coordinate) and a buffer which is filled with the positions of
// opponent pieces that is flipped by the move. The return value is the amount of opponent
// pieces that gets flipped.
//
// In othello a piece is flipped when a new opponent piece is placed so it has opponent
// pieces on both sides.
int Game::getsFlippedByMove(const Player p, const Coordinate c, Coordinate buffer[]) const {
    int count = 0;
    // Because we cant know if the positions should be added to output
    // we need to use temporary variables until we have traversed the path
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
