#ifndef GAME_H
#define GAME_H

#define N_ROWS 4
#define N_COLUMNS 4

enum Player {
    WHITE, 
    BLACK 
};

struct Coordinate {
    int rowPos;
    int colPos;
    enum Direction {S, SW, W, NW, N, NE, E, Se};
    bool operator==(const Coordinate &rhs) const;
    Coordinate step(const Coordinate::Direction d);
};

template<int rowSize, int colSize>
class Board {
    public:
        void put(const Player p, const Coordinate c) {
            this->positions[c.rowPos][c.colPos].isEmpty = false;
            this->positions[c.rowPos][c.colPos].player = p;
        };
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
        struct Position {
                bool isEmpty{true};
                Player player{WHITE};
        };
        Position positions[rowSize][colSize];
};

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

        int getLegalMoves(const Player p) const;
        Coordinate* getFlippedByMove(const Player p, const Coordinate c) const;
};

#endif // GAME_H
