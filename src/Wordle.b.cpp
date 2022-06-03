#include "Wordle.h"

#include <random>

#include <benchmark/benchmark.h>

static void BM_WordleGetHint(benchmark::State& state)
{
    std::random_device rand_dev{};
    std::default_random_engine rand_eng{rand_dev()};
    std::uniform_int_distribution<char> dist{'a', 'z'};

    std::vector<Word> wordlist{};
    std::string str(5, 'a');
    for (long i = 0; i < state.range(0); i++)
    {
        for (auto& c : str) { c = dist(rand_eng); }

        wordlist.emplace_back(str);
    }

    for (auto _ : state)  // NOLINT
    {
        for (const auto& guess : wordlist)
        {
            for (const auto& solution : wordlist)
            {
                benchmark::DoNotOptimize(Wordle::getHint(guess, solution));
            }
        }
    }
}
BENCHMARK(BM_WordleGetHint)->Arg(1000);
