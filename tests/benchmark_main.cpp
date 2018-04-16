#include <iostream>
#include <time.h>

#include "AI.hpp"
#include "game.hpp"

int main(int argc, char* argv[]) {
    const int NUM_ITERATIONS = 50000;
    int start;
    double secs;

    Board<4,4> board;
    board.put(BLACK, {1, 1});
    board.put(BLACK, {2, 2});
    board.put(WHITE, {2, 1});
    board.put(WHITE, {1, 2});

    Game game(board);
    AI ai(game, BLACK);

    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        ai.think();
    };
    secs = (clock() - start)/ (double) CLOCKS_PER_SEC;

    std::cout << NUM_ITERATIONS << " iterations took " << secs << " seconds (" << secs/NUM_ITERATIONS << " secs per iteration).\n";
    return 0;
}
