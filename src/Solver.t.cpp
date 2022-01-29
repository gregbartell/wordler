#include "Solver.h"

#include <gtest/gtest.h>

TEST(SolverTests, EmptyWordlist)
{
    std::stringstream ss{};
    Solver solver{ss};

    EXPECT_FALSE(solver.finished());
    EXPECT_EQ(solver.getBestGuess(), "");
}

TEST(SolverTests, SingleWordWordlist)
{
    std::stringstream ss{"aaa"};
    Solver solver{ss};

    EXPECT_FALSE(solver.finished());
    EXPECT_EQ(solver.getBestGuess(), "aaa");
    EXPECT_FALSE(solver.makeGuess("", "###"));    // Bad guess
    EXPECT_FALSE(solver.makeGuess("aaa", ""));    // Bad hint
    EXPECT_TRUE(solver.makeGuess("aaa", "###"));  // Good guess, good hint
    EXPECT_TRUE(solver.finished());
}

TEST(SolverTests, SmallWordlist)
{
    std::stringstream ss{"aaa\nbbb"};
    Solver solver{ss};

    EXPECT_FALSE(solver.finished());
    auto first_guess = solver.getBestGuess();
    // Should only ever guess words in wordlist
    EXPECT_TRUE(first_guess == "aaa" || first_guess == "bbb");
    // Tell it that its guess is all wrong
    EXPECT_TRUE(solver.makeGuess(first_guess, "..."));

    EXPECT_FALSE(solver.finished());
    auto second_guess = solver.getBestGuess();
    // Should only ever guess words in wordlist
    EXPECT_TRUE(second_guess == "aaa" || second_guess == "bbb");
    EXPECT_NE(first_guess, second_guess);
    // Now tell it that it found the solution
    EXPECT_TRUE(solver.makeGuess(second_guess, "###"));

    EXPECT_TRUE(solver.finished());
}

TEST(SolverTests, BadWordlist)
{
    std::stringstream ss{
        "aaa\nbb\nccc"};  // Words have different lengths, which is not allowed
    EXPECT_EXIT(Solver{ss}, testing::ExitedWithCode(1), "ERROR");
}

TEST(SolverTests, EasyMode)
{
    // In this wordlist, starting with the guess "aeix" guarantees a solution on
    // the second guess. Any other starting guess may require three total
    // guesses
    std::stringstream ss{"abcz\naeix\ndefz\nghiz\nxxxx"};

    Solver solver{ss, false /* easy mode */};
    EXPECT_TRUE(
        solver.makeGuess("xxxx",
                         "...."));  // Eliminate "aeix" from the solution set
    // "aeix" is still the optimal pick despite not being a valid solution.

    EXPECT_EQ(solver.getBestGuess(), "aeix");
}

TEST(SolverTests, HardMode)
{
    // In this wordlist, starting with the guess "aeix" guarantees a solution on
    // the second guess. Any other starting guess may require three total
    // guesses
    std::stringstream ss{"abcz\naeix\ndefz\nghiz\nxxxx"};

    Solver solver{ss, true /* hard mode */};
    EXPECT_TRUE(
        solver.makeGuess("xxxx",
                         "...."));  // Eliminate "aeix" from the solution set
    // "aeix" is still the optimal pick despite not being a valid solution.

    auto guess = solver.getBestGuess();
    EXPECT_NE(guess, "aeix");
    EXPECT_TRUE(guess == "abcz" || guess == "defz" || guess == "ghiz");
}
