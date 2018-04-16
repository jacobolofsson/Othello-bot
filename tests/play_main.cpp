#include <iostream>
#include <time.h>

#include "AI.hpp"
#include "game.hpp"

void printBoard(Game g) {
    char s[100];
    g.toString(s);
    std::cout << "----------------\n";
    std::cout << s;
    std::cout << "----------------\n";
};

int main(int argc, char* argv[]) {
    int iteration_limit = 50000;
    if (argc > 1) {
        iteration_limit = atoi(argv[1]);
    };
    std::cout << "Number of AI iterations limited to: " << iteration_limit << "\n";

    Board<4,4> board;
    board.put(BLACK, {1, 1});
    board.put(BLACK, {2, 2});
    board.put(WHITE, {2, 1});
    board.put(WHITE, {1, 2});

    Player aiColor = BLACK;
    Player humanColor = WHITE;
    Coordinate aiMove;
    Coordinate humanMove;

    Game game(board);

    std::cout << "AI: X, You: O\n";

    while(!game.isOver()) {
        printBoard(game);
        std::cout << "Enter Y-coord:";
        std::cin >> humanMove.colPos;
        std::cout << "Enter X-coord:";
        std::cin >> humanMove.rowPos;
        std::cout << "Applying human move:\n";
        game.applyMove(humanColor, humanMove);

        AI ai(game, aiColor);
        printBoard(game);
        std::cout << "AI thinking...\n";
        if (ai.getNumMoves() > 0) {
            for (int i = 0; i < iteration_limit; ++i) {
                ai.think();
            };
            aiMove = ai.getBestMove();
            game.applyMove(aiColor, aiMove);
        } else {
            std::cout << "AI: pass\n";
        };
    };
    printBoard(game);
    std::cout << "Game over!!\n";
    if (game.isWinner(aiColor)) {
        std::cout << "Winner: AI\n";
    } else if (game.isWinner(humanColor)) {
        std::cout << "Winner: You\n";
    } else {
        std::cout << "Its a draw!\n";
    };
    return 0;
};
