#include "Wordle.h"

#include <random>

#include <benchmark/benchmark.h>

static void BM_WordleGetHint(benchmark::State& state)
{
    std::random_device rand_dev{};
    std::default_random_engine rand_eng{rand_dev()};
    std::uniform_int_distribution<char> dist{'a', 'z'};

    std::vector<std::string> wordlist{};
    for (long i = 0; i < state.range(0); i++)
    {
        std::string str{};
        for (size_t j = 0; j < 5; j++) { str += dist(rand_eng); }

        wordlist.emplace_back(std::move(str));
    }

    for (auto _ : state)
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
