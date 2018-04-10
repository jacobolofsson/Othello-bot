#include "catch.hpp"

#include <vector>

#include "game.hpp"

TEST_CASE("Test step", "[coordinate][board]") {
    SECTION("Test inBounds") {
        CHECK(Board<4,4>::isInBounds({-1, 1}) == false);
        CHECK(Board<4,4>::isInBounds({1, -5}) == false);
        CHECK(Board<4,4>::isInBounds({15, 1}) == false);
        CHECK(Board<4,4>::isInBounds({2, 20}) == false);
        CHECK(Board<4,4>::isInBounds({1, 2}) == true);
        CHECK(Board<4,4>::isInBounds({-1, 25}) == false);
    }
    SECTION("Valid steps") {
        CHECK((Coordinate {0,0}).step(Coordinate::S)  == Coordinate {0,1});
        CHECK((Coordinate {1,1}).step(Coordinate::SW) == Coordinate {0,2});
        CHECK((Coordinate {2,2}).step(Coordinate::W)  == Coordinate {1,2});
        CHECK((Coordinate {2,2}).step(Coordinate::NW) == Coordinate {1,1});
        CHECK((Coordinate {0,2}).step(Coordinate::N)  == Coordinate {0,1});
        CHECK((Coordinate {2,1}).step(Coordinate::NE) == Coordinate {3,0});
        CHECK((Coordinate {0,0}).step(Coordinate::E)  == Coordinate {1,0});
        CHECK((Coordinate {0,0}).step(Coordinate::Se) == Coordinate {1,1});
    }
    SECTION("Test iteration") {
        Board<4,4> b;
        CHECK(b.getFirst() == Coordinate {0,0});
        CHECK(b.getLast() == Coordinate {3,3});

        CHECK(b.iterate({0,0}) == Coordinate {1,0});
        CHECK(b.iterate({3,1}) == Coordinate {0,2});
    }
}
TEST_CASE("Test game functions", "[game]") {
    CHECK(Game::nextPlayer(BLACK) == WHITE);
    CHECK(Game::nextPlayer(WHITE) == BLACK);
}

TEST_CASE("Test empty board", "[board][game]") {
    Board<4,4> board;
    Game game(board);
    Coordinate buffer[100];

    CHECK(game.getLegalMoves(BLACK, buffer) == 0);
    CHECK(game.getLegalMoves(WHITE, buffer) == 0);
    CHECK(game.isWinner(WHITE) == false);
    CHECK(game.isWinner(BLACK) == false);
    CHECK(game.isOver() == true); 
}

TEST_CASE("Test board with a few pieces", "[board][game]") {
    //____
    //_BW_
    //_WB_
    //____
    Board<4,4> board;

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

    SECTION("Flip pieces") {
        board.flip({1, 1});
        board.flip({1, 2});

        CHECK(board.getPlayer({1, 1}) == WHITE);
        CHECK(board.getPlayer({1, 2}) == BLACK);
    }
    SECTION("Test game") {
        Game game = Game(board);

        CHECK(game.isOver() == false);
        CHECK(game.isWinner(WHITE) == false);
        CHECK(game.isWinner(BLACK) == false);

        CHECK(game.getPoints(BLACK) == 2);
        CHECK(game.getPoints(WHITE) == 2);
        
        SECTION("Test getLegalMoves") {
            Coordinate buffer[100];
            int nBlackMoves = game.getLegalMoves(BLACK, buffer);
            std::vector<Coordinate> blackMoves(buffer, buffer + nBlackMoves);

            CHECK(nBlackMoves == 4);
            CHECK_THAT(blackMoves,
                    Catch::VectorContains( Coordinate {2,0} ) &&
                    Catch::VectorContains( Coordinate {3,1} ) &&
                    Catch::VectorContains( Coordinate {0,2} ) &&
                    Catch::VectorContains( Coordinate {1,3} ) );

            int nWhiteMoves = game.getLegalMoves(WHITE, buffer);
            std::vector<Coordinate> whiteMoves(buffer, buffer + nWhiteMoves);

            CHECK(nWhiteMoves == 4);
            CHECK_THAT(whiteMoves,
                    Catch::VectorContains( Coordinate {1,0} ) &&
                    Catch::VectorContains( Coordinate {0,1} ) &&
                    Catch::VectorContains( Coordinate {3,2} ) &&
                    Catch::VectorContains( Coordinate {2,3} ) );
        }
        SECTION("Test getLegalMoves with too small buffer") {
            Coordinate buffer[2];
            CHECK(game.getLegalMoves(BLACK, buffer) == -1);
            CHECK(game.getLegalMoves(WHITE, buffer) == -1);
        }
        SECTION("Test legal move") {
            game.applyMove(BLACK, {0, 2});
            
            CHECK(game.isOver() == false);
            CHECK(game.isWinner(WHITE) == false);
            CHECK(game.isWinner(BLACK) == false);

            CHECK(game.getPoints(BLACK) == 4);
            CHECK(game.getPoints(WHITE) == 1);
            
            Coordinate buffer[100];
            int nBlackMoves = game.getLegalMoves(BLACK, buffer);
            std::vector<Coordinate> blackMoves(buffer, buffer + nBlackMoves);

            CHECK(nBlackMoves == 3);
            CHECK_THAT(blackMoves,
                    Catch::VectorContains( Coordinate {2,0} ) &&
                    Catch::VectorContains( Coordinate {3,0} ) &&
                    Catch::VectorContains( Coordinate {3,1} ) );

            int nWhiteMoves = game.getLegalMoves(WHITE, buffer);
            std::vector<Coordinate> whiteMoves(buffer, buffer + nWhiteMoves);

            CHECK(nWhiteMoves == 3);
            CHECK_THAT(whiteMoves,
                    Catch::VectorContains( Coordinate {0,1} ) &&
                    Catch::VectorContains( Coordinate {0,3} ) &&
                    Catch::VectorContains( Coordinate {2,3} ) );
        }
    }

}

TEST_CASE("Test board with only one avaliable slot", "[game]") {
    //WB_W
    //WWWW
    //WWWW
    //WWBW
    Board<4,4> board;

    board.put(WHITE, {0, 0});
    board.put(BLACK, {1, 0});
    board.put(WHITE, {3, 0});
    board.put(WHITE, {0, 1});
    board.put(WHITE, {1, 1});
    board.put(WHITE, {2, 1});
    board.put(WHITE, {3, 1});
    board.put(WHITE, {0, 2});
    board.put(WHITE, {1, 2});
    board.put(WHITE, {2, 2});
    board.put(WHITE, {3, 2});
    board.put(WHITE, {0, 3});
    board.put(WHITE, {1, 3});
    board.put(BLACK, {2, 3});
    board.put(WHITE, {3, 3});

    Game game = Game(board);

    CHECK(game.isOver() == false);
    CHECK(game.isWinner(WHITE) == false);
    CHECK(game.isWinner(BLACK) == false);

    CHECK(game.getPoints(BLACK) == 2);
    CHECK(game.getPoints(WHITE) == 13);
    
    SECTION("Apply black move") {
        game.applyMove(BLACK, {2, 0});

        CHECK(game.isOver() == true);
        CHECK(game.isWinner(WHITE) == true);
        CHECK(game.isWinner(BLACK) == false);

        CHECK(game.getPoints(BLACK) == 5);
        CHECK(game.getPoints(WHITE) == 11);
    }
    SECTION("Apply white move") {
        game.applyMove(WHITE, {2, 0});

        CHECK(game.isOver() == true);
        CHECK(game.isWinner(WHITE) == true);
        CHECK(game.isWinner(BLACK) == false);

        CHECK(game.getPoints(BLACK) == 1);
        CHECK(game.getPoints(WHITE) == 15);
    }

}
TEST_CASE("Test board where game over for BLACK", "[game]") {
    //WWWW
    //W_WW
    //WWBW
    //WWWW
    Board<4,4> board;

    board.put(WHITE, {0, 0});
    board.put(WHITE, {1, 0});
    board.put(WHITE, {2, 0});
    board.put(WHITE, {3, 0});
    board.put(WHITE, {0, 1});
    board.put(WHITE, {2, 1});
    board.put(WHITE, {3, 1});
    board.put(WHITE, {0, 2});
    board.put(WHITE, {1, 2});
    board.put(BLACK, {2, 2});
    board.put(WHITE, {3, 2});
    board.put(WHITE, {0, 3});
    board.put(WHITE, {1, 3});
    board.put(WHITE, {2, 3});
    board.put(WHITE, {3, 3});

    Game game = Game(board);

    CHECK(game.isOver() == false);
    CHECK(game.isWinner(WHITE) == false);
    CHECK(game.isWinner(BLACK) == false);

    CHECK(game.getPoints(BLACK) == 1);
    CHECK(game.getPoints(WHITE) == 14);

    Coordinate buffer[100];
    CHECK(game.getLegalMoves(BLACK, buffer) == 0);
    CHECK(game.getLegalMoves(WHITE, buffer) == 1);
    
    game.applyMove(WHITE, {1, 1});

    CHECK(game.isOver() == true);
    CHECK(game.isWinner(WHITE) == true);
    CHECK(game.isWinner(BLACK) == false);

    CHECK(game.getPoints(BLACK) == 0);
    CHECK(game.getPoints(WHITE) == 16);

}
TEST_CASE("Test board where game over for WHITE", "[game]") {
    // BB__
    // BBW_
    // BBB_
    // BBB_
    Board<4,4> board;

    board.put(BLACK, {0, 0});
    board.put(BLACK, {1, 0});
    board.put(BLACK, {0, 1});
    board.put(BLACK, {1, 1});
    board.put(WHITE, {2, 1});
    board.put(BLACK, {0, 2});
    board.put(BLACK, {1, 2});
    board.put(BLACK, {2, 2});
    board.put(BLACK, {0, 3});
    board.put(BLACK, {1, 3});
    board.put(BLACK, {2, 3});

    Game game = Game(board);

    CHECK(game.isOver() == false);
    CHECK(game.isWinner(WHITE) == false);
    CHECK(game.isWinner(BLACK) == false);

    CHECK(game.getPoints(BLACK) == 10);
    CHECK(game.getPoints(WHITE) == 1);

    Coordinate buffer[100];
    CHECK(game.getLegalMoves(BLACK, buffer) == 4);
    CHECK(game.getLegalMoves(WHITE, buffer) == 0);
    
    game.applyMove(BLACK, {2, 0});

    CHECK(game.isOver() == true);
    CHECK(game.isWinner(WHITE) == false);
    CHECK(game.isWinner(BLACK) == true);

    CHECK(game.getPoints(BLACK) == 12);
    CHECK(game.getPoints(WHITE) == 0);

}
TEST_CASE("Test draw", "[game]") {
    //BBBB
    //BBBB
    //WWWW
    //WWWW
    Board<4,4> board;

    board.put(BLACK, {0, 0});
    board.put(BLACK, {1, 0});
    board.put(BLACK, {2, 0});
    board.put(BLACK, {3, 0});
    board.put(BLACK, {0, 1});
    board.put(BLACK, {1, 1});
    board.put(BLACK, {2, 1});
    board.put(BLACK, {3, 1});
    board.put(WHITE, {0, 2});
    board.put(WHITE, {1, 2});
    board.put(WHITE, {2, 2});
    board.put(WHITE, {3, 2});
    board.put(WHITE, {0, 3});
    board.put(WHITE, {1, 3});
    board.put(WHITE, {2, 3});
    board.put(WHITE, {3, 3});

    Game game = Game(board);

    CHECK(game.isOver() == true);
    CHECK(game.isWinner(WHITE) == false);
    CHECK(game.isWinner(BLACK) == false);

    CHECK(game.getPoints(BLACK) == 8);
    CHECK(game.getPoints(WHITE) == 8);

    Coordinate buffer[100];
    CHECK(game.getLegalMoves(BLACK, buffer) == 0);
    CHECK(game.getLegalMoves(WHITE, buffer) == 0);
    
}
