#include "Solver.h"

#include <random>
#include <sstream>

#include <benchmark/benchmark.h>

static void BM_SolverGetBestGuess(benchmark::State& state)
{
    std::random_device rand_dev{};
    std::default_random_engine rand_eng{rand_dev()};
    std::uniform_int_distribution<char> dist{'a', 'z'};

    std::stringstream wordlist{};
    for (long i = 0; i < state.range(0); i++)
    {
        std::string str{};
        for (size_t j = 0; j < 5; j++) { str += dist(rand_eng); }
        str += '\n';

        wordlist << str;
    }

    Solver solver{wordlist};

    for (auto _ : state)  // NOLINT
    {
        benchmark::DoNotOptimize(solver.getBestGuess());
    }
}
BENCHMARK(BM_SolverGetBestGuess)->Arg(100);
