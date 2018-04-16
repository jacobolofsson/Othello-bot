#ifndef GAME_H
#define GAME_H

// This file contains the declaration of the game class that contains the rules
// for playing reversi (othello), a board class that represents the playing board
// and a coordinate and player data structures.

#define N_ROWS 4
#define N_COLUMNS 4

enum Player {
    WHITE, 
    BLACK 
};

// Data structure that holds a coordinate. There are
// also directions associated with the coordinates.
struct Coordinate {
    int rowPos;
    int colPos;
    enum Direction {S, SW, W, NW, N, NE, E, Se,
    firstDir = S, lastDir = Se};
    bool operator==(const Coordinate &rhs) const;
    bool operator< (const Coordinate &rhs) const;
    bool operator<=(const Coordinate &rhs) const;
    Coordinate step(const Coordinate::Direction d);
};

// The board class represents the playing board of the game. The first coordinate is 0
// and the last is Size-1. 
// Example (initialize an 8x8 reversi board):
//  Board<8,8> b;
//  b.put(BLACK, {2,2};
//  b.put(WHITE, {2,3};
//  b.put(WHITE, {3,2};
//  b.put(BLACK, {3,3};
template<int rowSize, int colSize>
class Board {
    public:
        // Returns the first Coordinate on the board. This is mainly
        // for use with iterate function.
        Coordinate getFirst(void) const {
            Coordinate temp = first;
            return temp;
        }
        // Returns the last Coordinate on the board. This is mainly
        // for use with iterate function.
        Coordinate getLast(void) const {
            Coordinate temp = last;
            return temp;
        }
        // Takes a coordinate and returns the next in the board. This can be
        // used to iterate over the whole board together with getFirst() and
        // getLast().
        // Example:
        //  for (Coordinate c = board.getFirst(); c <= board.getLast(); c = b.iterate(c)) {
        //      /* Do stuff at each coordinate */
        //  };
        Coordinate iterate(const Coordinate c) const {
            Coordinate new_c = c;
            if (c.rowPos < last.rowPos) {
                new_c.rowPos++;
            } else {
                new_c.rowPos = first.rowPos;
                new_c.colPos++;
            }
            return new_c;
        };
        // Puts a player piece at a coordinate
        void put(const Player p, const Coordinate c) {
            this->positions[c.rowPos][c.colPos].isEmpty = false;
            this->positions[c.rowPos][c.colPos].player = p;
        };
        // Flips the player piece at the given coordinate
        void flip(const Coordinate c) {
            Player *p = &(this->positions[c.rowPos][c.colPos].player);
            if (*p == WHITE) {
                *p = BLACK;
            } else {
                *p = WHITE;
            };
        };
        bool isEmpty(const Coordinate c) const {
            return this->positions[c.rowPos][c.colPos].isEmpty;
        };
        Player getPlayer(const Coordinate c) const {
            return this->positions[c.rowPos][c.colPos].player;
        };
        static bool isInBounds(const Coordinate c) {
            return c.colPos < colSize &&
                   c.colPos >= 0      &&
                   c.rowPos < rowSize &&
                   c.rowPos >= 0;
        };
                                                                            
    private:
        // Internal data structure of the board is an array of positions.
        // A position can be empty or hold a player.
        struct Position {
                bool isEmpty{true};
                Player player{WHITE};
        };

        static const constexpr Coordinate first = {0,0};
        static const constexpr Coordinate last = {rowSize-1, colSize-1};
        Position positions[rowSize][colSize];
};

// The game class keeps the score and applies the rules of the game.
class Game {
    public:
        Game(Board<4,4> board);
        int getLegalMoves(const Player p, Coordinate buffer[]) const;
        static Player nextPlayer(const Player p);
        bool isOver(void) const;
        bool isWinner(const Player p) const;
        int getPoints(const Player p) const;

        void applyMove(const Player p, const Coordinate c);

    private:
        Board<4,4> board;
        static const int BUFFER_SIZE = 16;

        int getLegalMoves(const Player p) const;
        int getsFlippedByMove(const Player p, const Coordinate c, Coordinate buffer[]) const;
};

#endif // GAME_H
