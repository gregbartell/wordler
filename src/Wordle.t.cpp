#include "Wordle.h"

#include <gtest/gtest.h>

TEST(WordleTests, WordleTests)
{
    EXPECT_EQ(Wordle::getHint("bcdef", "aaaaa"), ".....");  // No matches
    EXPECT_EQ(Wordle::getHint("abbbb", "aaaaa"),
              "#....");  // 1 match, no partial matches
    EXPECT_EQ(Wordle::getHint("aaaaa", "aaaaa"), "#####");  // Full match

    EXPECT_EQ(Wordle::getHint("eabcd", "abcde"),
              "+++++");  // All partial matches
    EXPECT_EQ(Wordle::getHint("edcba", "abcde"),
              "++#++");  // 1 match, 4 partial matches
    EXPECT_EQ(Wordle::getHint("ababa", "abcde"),
              "##...");  // 2 matches, no partial matches
    EXPECT_EQ(Wordle::getHint("zzaab", "abcde"), "..+.+");  // 2 partial matches
    EXPECT_EQ(Wordle::getHint("decdz", "abcde"),
              ".+##.");  // 2 matches, 1 partial match
    EXPECT_EQ(Wordle::getHint("abcde", "abcde"),
              "#####");  // 2 matches, 1 partial match
}
