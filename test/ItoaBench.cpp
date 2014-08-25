#include "Benchmark.h"
#include "Logging.h"
#include "Itoa.h"

BENCHMARK(ItoaSprintf, n)
{
    char buf[20];
    u32toa_sprintf(n, buf);

    uint32_t r = 0;
    BENCHMARK_SUSPEND
    {
        r = atoi(buf);
    }
    CHECK(r == n);
}

#ifdef _MSC_VER
BENCHMARK_RELATIVE(ItoaItoa, n)
{
    char buf[20];
    _itoa(n, buf, 10);

    uint32_t r = 0;
    BENCHMARK_SUSPEND
    {
        r = atoi(buf);
    }
    CHECK(r == n);
}
#endif

BENCHMARK_RELATIVE(ItoaMwilson, n)
{
    char buf[20];
    u32toa_mwilson(buf, n);

    uint32_t r = 0;
    BENCHMARK_SUSPEND
    {
        r = atoi(buf);
    }
    CHECK(r == n);
}

BENCHMARK_RELATIVE(ItoaNaive, n)
{
    char buf[20];
    u32toa_naive(n, buf);

    uint32_t r = 0;
    BENCHMARK_SUSPEND
    {
        r = atoi(buf);
    }
    CHECK(r == n);
}

BENCHMARK_RELATIVE(ItoaCount, n)
{
    char buf[20];
    u32toa_count(n, buf);

    uint32_t r = 0;
    BENCHMARK_SUSPEND
    {
        r = atoi(buf);
    }
    CHECK(r == n);
}

BENCHMARK_RELATIVE(ItoaLut, n)
{
    char buf[20];
    u32toa_lut(n, buf);

    uint32_t r = 0;
    BENCHMARK_SUSPEND
    {
        r = atoi(buf);
    }
    CHECK(r == n);
}
