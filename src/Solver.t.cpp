#include "Solver.h"

#include <gtest/gtest.h>

TEST(SolverTests, EmptyWordlist)
{
    std::stringstream ss{};
    Solver solver{ss};

    EXPECT_FALSE(solver.finished());
    EXPECT_EQ(solver.getBestGuess().toString(), "~~~~~");
}

TEST(SolverTests, SingleWordWordlist)
{
    std::stringstream ss{"bbbbb"};
    Solver solver{ss};

    EXPECT_FALSE(solver.finished());
    EXPECT_EQ(solver.getBestGuess().toString(), "bbbbb");
    EXPECT_TRUE(solver.makeGuess(Word{"bbbbb"},
                                 Hint{"#####"}));  // Good guess, good hint
    EXPECT_TRUE(solver.finished());
}

TEST(SolverTests, SmallWordlist)
{
    std::stringstream ss{"aaaaa\nbbbbb"};
    Solver solver{ss};

    EXPECT_FALSE(solver.finished());
    auto first_guess     = solver.getBestGuess();
    auto first_guess_str = first_guess.toString();
    // Should only ever guess words in wordlist
    EXPECT_TRUE(first_guess_str == "aaaaa" || first_guess_str == "bbbbb");
    // Tell it that its guess is all wrong
    EXPECT_TRUE(solver.makeGuess(first_guess, Hint{"..."}));

    EXPECT_FALSE(solver.finished());
    auto second_guess     = solver.getBestGuess();
    auto second_guess_str = second_guess.toString();
    // Should only ever guess words in wordlist
    EXPECT_TRUE(second_guess_str == "aaaaa" || second_guess_str == "bbbbb");
    EXPECT_NE(first_guess, second_guess);
    // Now tell it that it found the solution
    EXPECT_TRUE(solver.makeGuess(second_guess, Hint{"#####"}));

    EXPECT_TRUE(solver.finished());
}

TEST(SolverTests, BadWordlist)
{
    std::stringstream ss{
        "aaaa\nbbbb\ncccc"};  // Words are not length 5, which is not allowed
    EXPECT_EXIT(Solver{ss}, testing::ExitedWithCode(1), "ERROR");
}

TEST(SolverTests, EasyMode)
{
    // In this wordlist, starting with the guess "afjxx" guarantees a solution
    // on the second guess. Any other starting guess may require three total
    // guesses
    std::stringstream ss{"abcdz\nafjxx\nefghz\nijklz\nxxxxx"};

    Solver solver{ss, false /* easy mode */};
    EXPECT_TRUE(solver.makeGuess(
        Word{"xxxxx"},
        Hint{"....."}));  // Eliminate "afjxx" from the solution set
    // "afjxx" is still the optimal pick despite not being a valid solution.

    EXPECT_EQ(solver.getBestGuess().toString(), "afjxx");
}

TEST(SolverTests, HardMode)
{
    // In this wordlist, starting with the guess "afjxx" guarantees a solution
    // on the second guess. Any other starting guess may require three total
    // guesses
    std::stringstream ss{"abcdz\nafjxx\nefghz\nijklz\nxxxxx"};

    Solver solver{ss, true /* hard mode */};
    EXPECT_TRUE(solver.makeGuess(
        Word{"xxxxx"},
        Hint{"....."}));  // Eliminate "afjxx" from the solution set
    // "afjxx" is still the optimal pick, but it's not a valid solution so the
    // solver can't pick it

    auto guess = solver.getBestGuess().toString();
    EXPECT_NE(guess, "afjxx");
    EXPECT_TRUE(guess == "abcdz" || guess == "efghz" || guess == "ijklz");
}
