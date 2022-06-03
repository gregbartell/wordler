#include "Wordle.h"

#include <gtest/gtest.h>

TEST(WordleTests, HintTests)
{
    for (char a : {'.', '+', '#'})
    {
        for (char b : {'.', '+', '#'})
        {
            for (char c : {'.', '+', '#'})
            {
                for (char d : {'.', '+', '#'})
                {
                    for (char e : {'.', '+', '#'})
                    {
                        std::string hint_str{a};
                        hint_str += b;
                        hint_str += c;
                        hint_str += d;
                        hint_str += e;

                        EXPECT_EQ(Hint{hint_str}.toString(), hint_str);
                    }
                }
            }
        }
    }

    Hint hint{"....."};
    hint.set(0, false);
    EXPECT_EQ(hint.toString(), "+....");
    hint.set(4, true);
    EXPECT_EQ(hint.toString(), "+...#");
    hint.set(2, true);
    EXPECT_EQ(hint.toString(), "+.#.#");
    EXPECT_EQ(hint.get(0), '+');
    EXPECT_EQ(hint.get(1), '.');
    EXPECT_EQ(hint.get(2), '#');
    EXPECT_EQ(hint.get(3), '.');
    EXPECT_EQ(hint.get(4), '#');
}

TEST(WordleTests, WordleTests)
{
    EXPECT_EQ(Wordle::getHint(Word{"bcdef"}, Word{"aaaaa"}).toString(),
              ".....");  // No matches
    EXPECT_EQ(Wordle::getHint(Word{"abbbb"}, Word{"aaaaa"}).toString(),
              "#....");  // 1 match, no partial matches
    EXPECT_EQ(Wordle::getHint(Word{"aaaaa"}, Word{"aaaaa"}).toString(),
              "#####");  // Full match
    EXPECT_EQ(Wordle::getHint(Word{"eabcd"}, Word{"abcde"}).toString(),
              "+++++");  // All partial matches
    EXPECT_EQ(Wordle::getHint(Word{"edcba"}, Word{"abcde"}).toString(),
              "++#++");  // 1 match, 4 partial matches
    EXPECT_EQ(Wordle::getHint(Word{"ababa"}, Word{"abcde"}).toString(),
              "##...");  // 2 matches, no partial matches
    EXPECT_EQ(Wordle::getHint(Word{"zzaab"}, Word{"abcde"}).toString(),
              "..+.+");  // 2 partial matches
    EXPECT_EQ(Wordle::getHint(Word{"decdz"}, Word{"abcde"}).toString(),
              ".+##.");  // 2 matches, 1 partial match
    EXPECT_EQ(Wordle::getHint(Word{"abcde"}, Word{"abcde"}).toString(),
              "#####");  // 2 matches, 1 partial match
}
