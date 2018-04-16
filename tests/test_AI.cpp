#include "AI.hpp"

#include "catch.hpp"

// Provide override for insert to display coordinates for testing
namespace Catch {
    template<>
        struct StringMaker<Coordinate> {
            static std::string convert( Coordinate const& value ) {
                return "{" + std::to_string(value.rowPos) + ", " + std::to_string(value.colPos) + "}";

            }
        };
}

SCENARIO("Game with one avaliable slot") {
    // BBBB
    // BW_B
    // WWBW
    // WWWW
    Board<4,4> b;
    b.put(BLACK, {0,0});
    b.put(BLACK, {1,0});
    b.put(BLACK, {2,0});
    b.put(BLACK, {3,0});
    b.put(BLACK, {0,1});
    b.put(WHITE, {1,1});

    b.put(BLACK, {3,1});
    b.put(WHITE, {0,2});
    b.put(WHITE, {1,2});
    b.put(BLACK, {2,2});
    b.put(WHITE, {3,2});
    b.put(WHITE, {0,3});
    b.put(WHITE, {1,3});
    b.put(WHITE, {2,3});
    b.put(WHITE, {3,3});

    Game g = Game(b);
    GIVEN("White player AI") {
        AI ai = AI(g, WHITE);
        THEN("AI returns the slot without thinking") {
            CHECK( ai.getNumMoves() == 1 );
            CHECK( ai.getBestMove() == Coordinate {2,1} );
        }
    }
    GIVEN("Black player AI") {
        AI ai = AI(g, BLACK);
        THEN("AI returns same slot without thinking") {
            CHECK( ai.getNumMoves() == 1 );
            CHECK( ai.getBestMove() == Coordinate {2,1} );
        }
    }
}
SCENARIO("Game with two avaliable slots which guarantee lose and win", "[AI_2_slots]") {
    // _BBW
    // BWW_
    // BBBB
    // WBBW
    Board<4,4> b;

    b.put(BLACK, {1,0});
    b.put(BLACK, {2,0});
    b.put(WHITE, {3,0});
    b.put(BLACK, {0,1});
    b.put(WHITE, {1,1});
    b.put(WHITE, {2,1});

    b.put(BLACK, {0,2});
    b.put(BLACK, {1,2});
    b.put(BLACK, {2,2});
    b.put(BLACK, {3,2});
    b.put(WHITE, {0,3});
    b.put(BLACK, {1,3});
    b.put(BLACK, {2,3});
    b.put(WHITE, {3,3});

    Game g = Game(b);

    const static int nThinkCycles = 800;
    GIVEN("White player AI") {
        AI ai = AI(g, WHITE);
        THEN("AI returns the slot after thinking") {
            CHECK( ai.getNumMoves() == 2 );
            for (int i=0; i < nThinkCycles; i++) {
                ai.think();
            };
            CHECK( ai.getBestMove() == Coordinate {0,0} );
        }
    }
    GIVEN("Black player AI") {
        AI ai = AI(g, BLACK);
        THEN("AI returns same slot after thinking") {
            CHECK( ai.getNumMoves() == 2 );
            for (int i=0; i < nThinkCycles; i++) {
                ai.think();
            };
            CHECK( ai.getBestMove() == Coordinate {0,0} );
        }
    }
}
SCENARIO("Game with several valid slots for WHITE but none for BLACK") {
    // WWWW
    // BBBB
    // _B__
    // ____
    Board<4,4> b;
    b.put(WHITE, {0,0});
    b.put(WHITE, {1,0});
    b.put(WHITE, {2,0});
    b.put(WHITE, {3,0});
    b.put(BLACK, {0,1});
    b.put(BLACK, {1,1});
    b.put(BLACK, {2,1});
    b.put(BLACK, {3,1});

    b.put(BLACK, {1,2});

    Game g = Game(b);

    GIVEN("White player AI") {
        AI ai = AI(g, WHITE);
        CHECK( ai.getNumMoves() == 5);
        THEN("AI returns a valid slot without thinking") {
            CHECK( (
                (ai.getBestMove() == Coordinate {0,2}) || 
                (ai.getBestMove() == Coordinate {2,2}) || 
                (ai.getBestMove() == Coordinate {3,2}) || 
                (ai.getBestMove() == Coordinate {0,3}) || 
                (ai.getBestMove() == Coordinate {1,3})
                ) ); 
        }
        THEN("AI returns a valid slot after thinking") {
            int nThinkCycles = 300;
            for (int i=0; i < nThinkCycles; i++) {
                ai.think();
            };
            CHECK( ( 
                (ai.getBestMove() == Coordinate {0,2}) || 
                (ai.getBestMove() == Coordinate {2,2}) || 
                (ai.getBestMove() == Coordinate {3,2}) || 
                (ai.getBestMove() == Coordinate {0,3}) || 
                (ai.getBestMove() == Coordinate {1,3})
                ) ); 
        }
    }
    GIVEN("Black player AI") {
        AI ai = AI(g, BLACK);
        THEN("AI returns a 0 avaliable moves") {
            CHECK( ai.getNumMoves() == 0);
        }
    }
}
