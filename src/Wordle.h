#pragma once

#include <array>
#include <cassert>
#include <cctype>
#include <functional>  // std::hash
#include <limits>
#include <string>
#include <string_view>

class Word
{
public:
    Word()
    {
        // To differentiate an invalid Word (created with this constructor) from
        // "aaaaa", we use 29 as a sentinel value: this will print as "~~~~~"
        m_word.fill(29);
    }

    Word(std::string_view word_str)
    {
        assert(word_str.length() == 5);

        for (size_t i = 0; i < m_word.size(); i++)
        {
            const auto& c = word_str[i];
            assert(std::islower(static_cast<unsigned char>(c)));

            m_word[i] = c - 'a';
        }
    }

    static constexpr size_t size() { return 5; }

    bool operator==(const Word& other) const { return m_word == other.m_word; }

    bool operator!=(const Word& other) const { return !(*this == other); }

    const auto& operator[](size_t i) const { return m_word[i]; }

    bool isValid() const { return (*this != Word{}); }

    std::string toString() const
    {
        std::string ret(5, 'a');

        for (size_t i = 0; i < m_word.size(); i++)
        {
            ret[i] += m_word[i];  // NOLINT
        }

        return ret;
    }

private:
    friend struct std::hash<Word>;

    std::array<uint_fast8_t, 5> m_word{};
};

template <>
struct std::hash<Word>
{
    size_t operator()(Word const& word) const noexcept
    {
        // Each word is 5 numbers, each with a value in the range [0, 25]
        // That's 5 bits for each number, so 25 bits necessary to fit all of
        // them
        size_t hash_val = 0;
        for (const auto& c : word.m_word)
        {
            hash_val <<= 5;
            hash_val |= c;
        }
        return hash_val;
    }
};

class Hint
{
public:
    Hint() = default;

    Hint(std::string_view hint)
    {
        assert(hint.size() <= 5);
        for (size_t i = 0; i < hint.size(); i++)
        {
            if (hint[i] == '#') { set(i, true); }
            else if (hint[i] == '+')
            {
                set(i, false);
            }
        }
    }

    bool operator==(const Hint& other) const { return m_hint == other.m_hint; }

    bool operator!=(const Hint& other) const { return !(*this == other); }

    std::string toString() const
    {
        std::string ret{};
        ret.reserve(5);

        for (size_t i = 0; i < 5; i++) { ret += get(i); }

        return ret;
    }

    bool allCorrect() const { return m_hint == 242; }

    char get(size_t i) const
    {
        switch ((m_hint / threeToThePower(i)) % 3)
        {
            case 0:
                return '.';
            case 1:
                return '+';
            case 2:
                return '#';
        }

        std::abort();
    }

    // Only valid to call if the given position is currently unset ('.')
    void set(size_t i, bool green /* false for yellow */)
    {
        assert(get(i) == '.');

        uint8_t val = static_cast<uint8_t>(green) + 1;
        val *= threeToThePower(i);

        m_hint += val;
    }

private:
    static uint8_t threeToThePower(size_t i)
    {
        assert(i < 5);

        switch (i)
        {
            case 0:
                return 1;
            case 1:
                return 3;
            case 2:
                return 9;
            case 3:
                return 27;
            case 4:
                return 81;
            default:
                std::abort();
        }
    }

    friend struct std::hash<Hint>;

    // Hint is encoded in base three with value 0 for miss, 1 for yellow, 2 for
    // green
    uint_fast8_t m_hint = 0;
};

template <>
struct std::hash<Hint>
{
    size_t operator()(Hint const& hint) const noexcept { return hint.m_hint; }
};

class Wordle
{
public:
    // No objects, static functions only
    Wordle() = delete;

    static Hint getHint(const Word& guess, const Word& solution)
    {
        Hint hint{};

        // How often a given letter appears in solution, not counting matches
        std::array<uint_fast8_t, 26> freqs{};

        for (size_t i = 0; i < Word::size(); i++)
        {
            const auto& guess_letter    = guess[i];
            const auto& solution_letter = solution[i];

            if (guess_letter == solution_letter) { hint.set(i, true); }
            else
            {
                freqs[solution_letter]++;
            }
        }

        for (size_t i = 0; i < Word::size(); i++)
        {
            const auto& guess_letter    = guess[i];
            const auto& solution_letter = solution[i];

            // If the letter has already been marked as a match, ignore
            // hint.get() is not very efficient, so checking this way is faster
            if (guess_letter == solution_letter) { continue; }

            // If there are more of these in the solution
            if (freqs[guess_letter] > 0)
            {
                freqs[guess_letter]--;
                hint.set(i, false);
            }
        }

        return hint;
    }
};
