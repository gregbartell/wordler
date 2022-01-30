#pragma once

#include "Wordle.h"

#include <algorithm>
#include <iostream>
#include <istream>
#include <limits>
#include <string>
#include <unordered_set>
#include <vector>

class Solver
{
public:
    Solver(std::istream& wordlist, bool hard_mode = false) :
        m_hard_mode{hard_mode}
    {
        for (std::string word{}; wordlist >> word;)
        {
            if (m_word_size == 0) { m_word_size = word.size(); }
            else if (m_word_size != word.size())
            {
                std::cerr << "ERROR: wordlist has words of different lengths"
                          << std::endl;
                std::exit(1);
            }

            m_wordlist.emplace_back(word);
            m_solution_set.emplace(word);
        }
    }

    [[nodiscard]] std::string getBestGuess() const
    {
        if (m_solution_set.empty()) { return ""; }
        if (m_solution_set.size() == 1) { return *m_solution_set.begin(); }

        if (m_hard_mode) { return getBestGuess(m_solution_set); }
        return getBestGuess(m_wordlist);
    }

    [[nodiscard]] bool makeGuess(const std::string& guess,
                                 const std::string& hint)
    {
        if (guess.size() != m_word_size)
        {
            std::cerr << "ERROR: guess has incorrect length (" << guess.size()
                      << ", expected " << m_word_size << ")" << std::endl;
            return false;
        }

        if (hint.size() != m_word_size)
        {
            std::cerr << "ERROR: hint has incorrect length (" << hint.size()
                      << ", expected " << m_word_size << ")" << std::endl;
            return false;
        }

        // We won
        if (hint == std::string(guess.size(), '#')) { m_solved = true; }

        std::erase_if(m_solution_set, [&guess, &hint](const auto& solution) {
            return !isSolutionValid(guess, hint, solution);
        });

        // If in easy mode (where we can recommend guesses outside of the
        // solution set), we still want to prioritize guessing words that are in
        // the solution set as long as they're the best guess. We do this by
        // sorting the wordlist (which we will recommend guesses from) so that
        // words in the solution set are ordered first.
        if (!m_hard_mode)
        {
            std::sort(m_wordlist.begin(),
                      m_wordlist.end(),
                      [&](const auto& lhs, const auto& rhs) {
                          return m_solution_set.contains(lhs) >
                                 m_solution_set.contains(rhs);
                      });
        }

        return true;
    }

    [[nodiscard]] bool finished() const { return m_solved; }

    void reset()
    {
        m_solved       = false;
        m_solution_set = {m_wordlist.begin(), m_wordlist.end()};
    }

private:
    [[nodiscard]] static bool
    isSolutionValid(const std::string& guess,
                    const std::string& hint,
                    const std::string& possible_solution)
    {
        return hint == Wordle::getHint(guess, possible_solution);
    }

    [[nodiscard]] std::unordered_set<std::string>
    getPossibleHints(const std::string& guess) const
    {
        std::unordered_set<std::string> possible_hints{};

        for (const auto& possible_solution : m_solution_set)
        {
            possible_hints.emplace(Wordle::getHint(guess, possible_solution));
        }

        return possible_hints;
    }

    template <typename CONTAINER>
    [[nodiscard]] std::string getBestGuess(const CONTAINER& container) const
    {
        std::string best_guess{};
        size_t best_score = 0;

        for (const auto& guess : container)
        {
            auto possible_hints = getPossibleHints(guess);

            size_t min_solutions_eliminated =
                std::numeric_limits<size_t>::max();
            for (const auto& hint : possible_hints)
            {
                size_t solutions_eliminated = 0;
                for (const auto& possible_solution : m_solution_set)
                {
                    if (!isSolutionValid(guess, hint, possible_solution))
                    {
                        solutions_eliminated++;
                    }
                }

                // Pruning - if this hint+solution would eliminate fewer
                // possibilites than our best guess found so far, then this
                // guess is worst than the best one we've found so far
                if (solutions_eliminated < best_score)
                {
                    min_solutions_eliminated = 0;
                    break;
                }

                min_solutions_eliminated =
                    std::min(min_solutions_eliminated, solutions_eliminated);
            }

            if (min_solutions_eliminated > best_score)
            {
                best_score = min_solutions_eliminated;
                best_guess = guess;
            }
        }

        return best_guess;
    }

    std::vector<std::string> m_wordlist{};
    std::unordered_set<std::string> m_solution_set{};

    size_t m_word_size = 0;

    bool m_hard_mode{false};
    bool m_solved{false};
};
