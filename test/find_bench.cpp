#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include "Benchmark.h"

struct Point {
    int16_t x = 0;
    int16_t y = 0;
};

const int SMALL_FIND_VALUE = 100000;

template<typename T>
static T& getSmallMap(int n)
{
    static T dict;
    if (!dict.empty())
    {
        return dict;
    }
    for (int i = 1; i <= n; i++)
    {
        Point pt;
        pt.x = rand() % 0xFFFF;
        pt.y = rand() % 0xFFFF;
        int32_t cell = (pt.x << 16) | pt.y;
        dict[cell] = pt;
    }
    return dict;
}

template<typename T>
static T& getSmallPtrMap(int n)
{
    static T dict;
    if (!dict.empty())
    {
        return dict;
    }
    for (int i = 1; i <= n; i++)
    {
        auto pt = new Point;
        pt->x = rand() % 0xFFFF;
        pt->y = rand() % 0xFFFF;
        int32_t cell = (pt->x << 16) | pt->y;
        dict[cell] = pt;
    }
    return dict;
}

static std::vector<Point>& getSmallVector(int n)
{
    static std::vector<Point> vec;
    if (!vec.empty())
    {
        return vec;
    }
    for (int i = 1; i <= n; i++)
    {
        Point pt;
        pt.x = rand() % 0xFFFF;
        pt.y = rand() % 0xFFFF;
        vec.push_back(pt);
    }
    return vec;
}

static bool smallVectorFind(const std::vector<Point>& vec, int32_t cell)
{
    for (auto i = 0U; i < vec.size(); i++)
    {
        if (vec[i].x + vec[i].y == cell)
        {
            return true;
        }
    }
    return false;
}

static std::vector<Point*>& getSmallPtrVector(int n)
{
    static std::vector<Point*> vec;
    if (!vec.empty())
    {
        return vec;
    }
    for (int i = 1; i <= n; i++)
    {
        auto pt = new Point;
        pt->x = rand() % 0xFFFF;
        pt->y = rand() % 0xFFFF;
        vec.push_back(pt);
    }
    return vec;
}

static bool smallPtrVectorFind(const std::vector<Point*>& vec, int32_t cell)
{
    for (auto i = 0U; i < vec.size(); i++)
    {
        if (vec[i]->x + vec[i]->y == cell)
        {
            return true;
        }
    }
    return false;
}

BENCHMARK(SmallMapFind, n)
{
    BENCHMARK_SUSPEND
    {
        getSmallMap<std::unordered_map<int32_t, Point>>(SMALL_FIND_VALUE);
    }
    auto dict = getSmallMap<std::unordered_map<int32_t, Point>>(SMALL_FIND_VALUE);
    uint64_t sum = 0;
    for (unsigned i = 1; i <= n; i++)
    {
        int32_t cell = rand() % 0xFFFF;
        if (dict.count(cell) > 0)
        {
            sum += i;
        }
    }
    doNotOptimizeAway(sum);
}

BENCHMARK_RELATIVE(SmallVectorFind, n)
{
    BENCHMARK_SUSPEND
    {
        getSmallVector(SMALL_FIND_VALUE);
    }
    std::vector<Point> vec = getSmallVector(SMALL_FIND_VALUE);
    uint64_t sum = 0;
    for (unsigned i = 1; i <= n; i++)
    {
        int32_t cell = rand() % 0xFFFF;
        if (smallVectorFind(vec, cell))
        {
            sum += i;
        }
    }
    doNotOptimizeAway(sum);
}

BENCHMARK(SmallMapPtrFind, n)
{
    BENCHMARK_SUSPEND
    {
        getSmallPtrMap<std::unordered_map<int32_t, Point*>>(SMALL_FIND_VALUE);
    }
    auto dict = getSmallPtrMap<std::unordered_map<int32_t, Point*>>(SMALL_FIND_VALUE);
    uint64_t sum = 0;
    for (unsigned i = 1; i <= n; i++)
    {
        int32_t cell = rand() % 0xFFFF;
        if (dict.count(cell) > 0)
        {
            sum += i;
        }
    }
    doNotOptimizeAway(sum);
}

BENCHMARK_RELATIVE(SmallVectorPtrFind, n)
{
    BENCHMARK_SUSPEND
    {
        getSmallPtrVector(SMALL_FIND_VALUE);
    }
    std::vector<Point*> vec = getSmallPtrVector(SMALL_FIND_VALUE);
    uint64_t sum = 0;
    for (unsigned i = 1; i <= n; i++)
    {
        int32_t cell = rand() % 0xFFFF;
        if (smallPtrVectorFind(vec, cell))
        {
            sum += i;
        }
    }
    doNotOptimizeAway(sum);
}
