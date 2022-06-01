#pragma once

#include <array>
#include <cassert>
#include <cctype>
#include <functional>  // std::hash
#include <limits>
#include <string>

class Hint
{
public:
    Hint() = default;

    Hint(const std::string& hint)
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

        for (size_t i = 0; i < 5; i++) { ret += get(i); }

        return ret;
    }

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

    // Hint is encoded in base three, left-to-right, with value 0 for miss, 1
    // for yellow, 2 for green
    uint8_t m_hint = 0;
};
static_assert(sizeof(Hint) == 1);

template <>
struct std::hash<Hint>
{
    auto operator()(Hint const& hint) const noexcept
    {
        return std::hash<uint8_t>{}(hint.m_hint);
    }
};

class Wordle
{
public:
    // No objects, static functions only
    Wordle() = delete;

    static Hint getHint(const std::string& guess, const std::string& solution)
    {
        Hint hint{};

        // How often a given letter appears in solution, not counting matches
        std::array<uint_fast8_t, 26> freqs{};

        assert(guess.size() == solution.size());
        assert(guess.size() <
               std::numeric_limits<decltype(freqs)::value_type>::max());

        for (size_t i = 0; i < guess.size(); i++)
        {
            const auto& guess_letter    = guess[i];
            const auto& solution_letter = solution[i];
            assert(std::islower(static_cast<unsigned char>(guess_letter)));

            if (guess_letter == solution_letter) { hint.set(i, true); }
            else
            {
                freqs[solution_letter - 'a']++;
            }
        }

        for (size_t i = 0; i < guess.size(); i++)
        {
            const auto& guess_letter    = guess[i];
            const auto& solution_letter = solution[i];

            // If the letter has already been marked as a match, ignore
            // hint.get() is not very efficient, so checking this way is faster
            if (guess_letter == solution_letter) { continue; }

            // If there are more of these in the solution
            if (freqs[guess_letter - 'a'] > 0)
            {
                freqs[guess_letter - 'a']--;
                hint.set(i, false);
            }
        }

        return hint;
    }
};
