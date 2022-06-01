#include "Solver.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>

#include <tclap/CmdLine.h>

int main(int argc, char* argv[])
{
    // Vars that will hold the arguments read from TCLAP
    std::string wordlist_filename{};
    bool hard_mode          = false;
    bool recalc_first_guess = false;
    bool stats_mode         = false;

    // TCLAP throws exceptions, so we need to wrap it in a try-catch block
    try
    {
        TCLAP::CmdLine cmd{"Wordler, a solver for Wordle", ' '};

        TCLAP::UnlabeledValueArg<std::string> wordlistArg{
            "wordlistFilename",
            "Wordlist file to use. Defaults to 'wordlist.txt' if unspecified.",
            false,
            "wordlist.txt",
            "wordlist.txt",
            cmd};

        TCLAP::SwitchArg recalcFirstGuessArg{
            "r",
            "recalc-first-guess",
            "Calculating the first guess takes a long time, so the first guess for the official Wordler wordlist is hardcoded into this program and used by default. Set this option to recalculate it based on the provided wordlist.",
            cmd};

        TCLAP::SwitchArg statsArg{
            "",
            "stats",
            "Solve every possible puzzle and print statistics about the number of guesses required.",
            cmd};

        TCLAP::SwitchArg hardModeArg{
            "",
            "hard",
            "Play in 'Hard Mode', where all guessed words must be possible solutions according to previously-given clues.",
            cmd};

        cmd.parse(argc, argv);

        // Put TCLAP args into our vars, so we don't have to do everything in
        // this try-catch block
        wordlist_filename  = wordlistArg.getValue();
        hard_mode          = hardModeArg.getValue();
        recalc_first_guess = recalcFirstGuessArg.getValue();
        stats_mode         = statsArg.getValue();
    }
    catch (TCLAP::ArgException& e)
    {
        std::cerr << "ERROR: Caught TCLAP exception: " << e.what() << std::endl;
        return 1;
    }

    if (!std::filesystem::exists(wordlist_filename))
    {
        std::cerr << "ERROR: No such file: " << wordlist_filename << std::endl;
        return 1;
    }
    std::ifstream wordlist{wordlist_filename};

    Solver solver{wordlist, hard_mode};

    std::string first_guess =
        (recalc_first_guess ? solver.getBestGuess() : "serai");

    if (stats_mode)
    {
        std::vector<size_t> guess_counts{};

        // Reopen wordlist
        wordlist = std::ifstream{wordlist_filename};
        for (std::string solution{}; wordlist >> solution;)
        {
            auto hint = Wordle::getHint(first_guess, solution);
            if (!solver.makeGuess(first_guess, hint))
            {
                std::cerr << "ERROR: made bad guess. guess=" << first_guess
                          << " solution=" << solution
                          << " hint=" << hint.toString() << std::endl;
                return 1;
            }
            size_t num_guesses = 1;

            while (!solver.finished())
            {
                auto guess = solver.getBestGuess();
                auto hint  = Wordle::getHint(guess, solution);
                if (!solver.makeGuess(guess, hint))
                {
                    std::cerr << "ERROR: made bad guess. guess=" << guess
                              << " solution=" << solution
                              << " hint=" << hint.toString() << std::endl;
                    return 1;
                }

                num_guesses++;
            }

            guess_counts.emplace_back(num_guesses);

            solver.reset();
        }

        std::cout << "Statistics for wordlist with " << guess_counts.size()
                  << " words, " << (hard_mode ? "hard" : "easy") << " mode"
                  << std::endl;
        std::cout << "Max guesses required: "
                  << *std::max_element(guess_counts.begin(), guess_counts.end())
                  << std::endl;
        std::cout << "Average (mean):       "
                  << (static_cast<double>(std::accumulate(guess_counts.begin(),
                                                          guess_counts.end(),
                                                          0ULL)) /
                      static_cast<double>(guess_counts.size()))
                  << std::endl;
    }
    else
    {
        std::string hint{};

        std::cout << "Start by entering '" << first_guess
                  << "' as your first guess ("
                  << solver.getNumSolutionsRemaining()
                  << " possible solutions left)" << std::endl;
        std::cout
            << "Enter hint (use '.' for miss, '+' for yellow match, '#' for green match):"
            << std::endl;
        std::cin >> hint;
        if (!solver.makeGuess(first_guess, hint)) { return 1; }

        while (!solver.finished())
        {
            std::cout << "-----" << std::endl;
            auto best_guess = solver.getBestGuess();
            if (best_guess.empty())
            {
                std::cerr << "ERROR: no possible solutions left" << std::endl;
                return 1;
            }
            std::cout << "Now guess: '" << best_guess << "' ("
                      << solver.getNumSolutionsRemaining()
                      << " possible solutions left)" << std::endl;
            std::cout << "Please enter hint:" << std::endl;
            std::cin >> hint;

            if (!solver.makeGuess(best_guess, hint)) { return 1; }
        }

        std::cout << "Congratulations, puzzle solved!" << std::endl;
    }

    return 0;
}
