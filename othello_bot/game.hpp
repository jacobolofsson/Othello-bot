#ifndef GAME_H
#define GAME_H

#define N_ROWS 8
#define N_COLUMNS 8

enum Player {
    WHITE, 
    BLACK 
};

struct Coordinate {
    int colPos;
    int rowPos;
};

class Board {
    public:
        //Board(void);

        void put(const Player p, const Coordinate c);
        void flip(const Coordinate c);

        int getPoints(const Player p) const;
        bool isEmpty(const Coordinate c) const;
        bool isOccupiedBy(const Player p, const Coordinate c) const;
                                                                            
    private:
        struct Position {
                bool isEmpty{true};
                Player player{WHITE};
        };

        bool isInBounds(const Coordinate c) const;

        Position positions[N_ROWS][N_COLUMNS];
};

class Game {
    public:
        Game(Board board);

        Coordinate* getLegalMoves(const Player p) const;
        bool isOver(void) const;
        bool isPlayerWinner(const Player p) const;

        void applyMove(const Player p, const Coordinate c);

    private:
        Board board;
};

#endif // GAME_H
