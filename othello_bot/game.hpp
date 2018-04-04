#ifndef GAME_H
#define GAME_H

#define N_ROWS 4
#define N_COLUMNS 4

enum Player {
    WHITE, 
    BLACK 
};

struct Coordinate {
    int colPos;
    int rowPos;
    enum Direction{S, SW, W, NW, N, NE, E, SE};
    bool operator==(const Coordinate &rhs) const;
};

//template<int rowSize, int colSize>
class Board {
    public:
        //Board(int _rowSize, int colSize);

        void put(const Player p, const Coordinate c);
        void flip(const Coordinate c);

        int getPoints(const Player p) const;
        bool isEmpty(const Coordinate c) const;
        static bool isInBounds(const Coordinate c);
        Player getPlayer(const Coordinate c) const;
        static Coordinate step(const Coordinate c, const Coordinate::Direction d);
                                                                            
    private:
        //const int rowSize = N_ROWS;
        //const int colSize = N_COLUMNS;
        struct Position {
                bool isEmpty{true};
                Player player{WHITE};
        };
        Position positions[N_ROWS][N_COLUMNS];
};

class Game {
    public:
        //Game(Board<4,4> board);
        Game(Board b);

        Coordinate* getLegalMoves(const Player p) const;
        bool isOver(void) const;
        bool isWinner(const Player p) const;

        void applyMove(const Player p, const Coordinate c);

    private:
        //Board<4,4> board;
        Board board;

        Coordinate* getFlippedByMove(const Player p, const Coordinate c) const;
};

#endif // GAME_H
