#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "benchmark/benchmark.h"

void BM_branch_predicted(benchmark::State& state) {
    srand(1);
    const unsigned int N = state.range(0);

    int *in1 = (int *)malloc(N * sizeof(int));
    int *in2 = (int *)malloc(N * sizeof(int));
    int *cond = (int *)malloc(N * sizeof(int));
    for (size_t i = 0; i < N; ++i) {
        in1[i] = 3;
        in2[i] = 3;
        cond[i] = 1; // always true
    }

    for (auto _ : state) {
        unsigned long a1 = 0, a2 = 0;
        for (size_t i = 0; i < N; ++i) {
            if (cond[i]) {
                a1 += in1[i];
            } else {
                a1 += in2[i];
            }
        }
        benchmark::DoNotOptimize(a1);
        benchmark::DoNotOptimize(a2);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(N*state.iterations());
}

#define ARGS \
    ->Arg(1<<22)

BENCHMARK(BM_branch_predicted) ARGS;

BENCHMARK_MAIN();

