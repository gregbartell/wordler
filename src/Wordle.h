#pragma once

#include <array>
#include <cassert>
#include <cctype>
#include <limits>
#include <string>

class Wordle
{
public:
    // No objects, static functions only
    Wordle() = delete;

    static std::string getHint(std::string guess, const std::string& solution)
    {
        std::array<uint_fast8_t, 26> freqs{};
        // A possibility to speed it up: decrease size of freqs

        assert(guess.size() == solution.size());
        assert(guess.size() <
               std::numeric_limits<decltype(freqs)::value_type>::max());

        for (size_t i = 0; i < guess.size(); i++)
        {
            const auto& guess_letter    = guess[i];
            const auto& solution_letter = solution[i];
            assert(std::islower(static_cast<unsigned char>(guess_letter)));

            if (guess_letter == solution_letter) { guess[i] = '#'; }
            else
            {
                freqs[solution_letter - 'a']++;
            }
        }

        for (auto& guess_letter : guess)
        {
            if (guess_letter == '#') { continue; }

            if (freqs[guess_letter - 'a'] > 0)
            {
                freqs[guess_letter - 'a']--;
                guess_letter = '+';
            }
            else
            {
                guess_letter = '.';
            }
        }

        return guess;
    }
};
