#include "catch.hpp"

#include "game.hpp"

TEST_CASE("Test step", "[coordinate][board]") {
    SECTION("Test inBounds") {
        CHECK(Board::isInBounds({-1, 1}) == false);
        CHECK(Board::isInBounds({1, -5}) == false);
        CHECK(Board::isInBounds({15, 1}) == false);
        CHECK(Board::isInBounds({2, 20}) == false);
        CHECK(Board::isInBounds({1, 2}) == true);
        CHECK(Board::isInBounds({-1, 25}) == false);
    }
    SECTION("Valid steps") {
        CHECK(Board::step({0,0}, Coordinate::S)  == Coordinate {0,1});
        CHECK(Board::step({1,1}, Coordinate::SW) == Coordinate {0,2});
        CHECK(Board::step({2,2}, Coordinate::W)  == Coordinate {1,2});
        CHECK(Board::step({2,2}, Coordinate::NW) == Coordinate {1,1});
        CHECK(Board::step({0,2}, Coordinate::N)  == Coordinate {0,1});
        CHECK(Board::step({2,1}, Coordinate::NE) == Coordinate {3,0});
        CHECK(Board::step({0,0}, Coordinate::E)  == Coordinate {1,0});
        CHECK(Board::step({0,0}, Coordinate::SE) == Coordinate {1,1});
    }
    SECTION("Invalid steps") {

    }
}

TEST_CASE("Test empty board", "[board][game]") {
    Board board;
    Game game(board);

    CHECK(game.getLegalMoves(BLACK) == NULL);
    CHECK(game.getLegalMoves(WHITE) == NULL);
    CHECK(game.isWinner(WHITE) == false);
    CHECK(game.isWinner(BLACK) == false);
    CHECK(game.isOver() == true); 
}

TEST_CASE("Test board with a few pieces", "[board][game]") {
    Board board;

    board.put(BLACK, {1, 1});
    board.put(BLACK, {2, 2});
    board.put(WHITE, {2, 1});
    board.put(WHITE, {1, 2});

    CHECK(board.getPlayer({1, 1}) == BLACK);
    CHECK(board.getPlayer({2, 2}) == BLACK);
    CHECK(board.getPlayer({2, 1}) == WHITE);
    CHECK(board.getPlayer({1, 2}) == WHITE);

    CHECK(board.isEmpty({0,0}) == true);
    CHECK(board.isEmpty({1,1}) == false);
    CHECK(board.isEmpty({2,1}) == false);
    CHECK(board.isEmpty({3,2}) == true);

    CHECK(board.getPoints(BLACK) == 2);
    CHECK(board.getPoints(WHITE) == 2);

    SECTION("Flip pieces") {
        board.flip({1, 1});
        board.flip({1, 2});

        CHECK(board.getPlayer({1, 1}) == WHITE);
        CHECK(board.getPlayer({1, 2}) == BLACK);
    }
    SECTION("Test game") {
        Game game = Game(board);

        //CHECK(game.getLegalMoves(BLACK) == {{3,1}, {4,1}, {4,2}, {1,3}, {1,4}, {2,4}});
        //legal moves white
        CHECK(game.isOver() == false);
        CHECK(game.isWinner(WHITE) == false);
        CHECK(game.isWinner(BLACK) == false);

        SECTION("Test legal move") {
        }
        SECTION("Test illegal move") {
        }
    }

}

TEST_CASE("Test board with only one avaliabel slot", "[game]") {

}
TEST_CASE("Test board where game over for BLACK", "[game]") {

}
TEST_CASE("Test board where game over for WHITE", "[game]") {

}
