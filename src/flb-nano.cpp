#include <time.h>
#include "benchmark/benchmark.h"

#define ONESEC_IN_NSEC 1000000000

struct flb_time {
    struct timespec tm;
};

static inline void flb_time_zero(volatile struct flb_time *tm)
{
    tm->tm.tv_sec = 0;
    tm->tm.tv_nsec = 0;
}

static double flb_time_to_double(volatile struct flb_time *tm)
{
    return (double)(tm->tm.tv_sec) + ((double)tm->tm.tv_nsec/(double)ONESEC_IN_NSEC);
}

static uint64_t flb_time_to_nanosec(volatile struct flb_time *tm)
{
    return (((uint64_t)tm->tm.tv_sec * 1000000000L) + tm->tm.tv_nsec);
}

// Benchmarks

static void BM_None(benchmark::State& state) {
    volatile struct flb_time out_time = {0};
    flb_time_zero(&out_time);
    volatile bool flag;
    for (auto _ : state) {
        flag = true;
    }
}
BENCHMARK(BM_None);

static void BM_Nano(benchmark::State& state) {
    volatile struct flb_time out_time = {0};
    flb_time_zero(&out_time);
    volatile bool flag;
    for (auto _ : state) {
        flag = flb_time_to_nanosec(&out_time) == 0L;
    }
}
BENCHMARK(BM_Nano);

static void BM_Sec(benchmark::State& state) {
    volatile struct flb_time out_time = {0};
    flb_time_zero(&out_time);
    volatile bool flag;
    for (auto _ : state) {
        flag = flb_time_to_double(&out_time) == 0.0;
    }
}
BENCHMARK(BM_Sec);

BENCHMARK_MAIN();
