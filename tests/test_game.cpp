#include "catch.hpp"

#include "game.hpp"

TEST_CASE("Test empty board", "[board]") {
    Board board;
    Game game(board);

    REQUIRE(game.getLegalMoves(WHITE) == NULL);
    REQUIRE(game.getLegalMoves(BLACK) == NULL);
    REQUIRE(game.isOver() == false); 
}

TEST_CASE("Test board with a few pieces", "[board]") {
    Board board;
    Game game(board);

    board.put(BLACK, {2, 2});
    board.put(BLACK, {3, 3});
    board.put(WHITE, {3, 2});
    board.put(WHITE, {2, 3});

}

TEST_CASE("Test board with only one avaliabel slot", "[board]") {

}
