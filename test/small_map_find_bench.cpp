#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include "Benchmark.h"

struct Point {
    int16_t x = 0;
    int16_t y = 0;
};

const int SMALL_FIND_VALUE = 100;

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

static bool smallVectorFind(const std::vector<Point>& vec, int32_t cell)
{
    for (auto i = 0U; i < vec.size(); i++)
    {
        int32_t v = vec[i].x + vec[i].y;
        if (v == cell)
        {
            return true;
        }
    }
    return false;
}

static bool smallPtrVectorFind(const std::vector<Point*>& vec, int32_t cell)
{
    for (auto i = 0U; i < vec.size(); i++)
    {
        int32_t v = vec[i]->x + vec[i]->y;
        if (v == cell)
        {
            return true;
        }
    }
    return false;
}

auto small_dict = getSmallMap<std::unordered_map<int32_t, Point>>(SMALL_FIND_VALUE);
auto small_dict_ptr = getSmallPtrMap<std::unordered_map<int32_t, Point*>>(SMALL_FIND_VALUE);
auto small_vec = getSmallVector(SMALL_FIND_VALUE);
auto small_vec_ptr = getSmallPtrVector(SMALL_FIND_VALUE);


BENCHMARK(SmallMapFind, n)
{
    const auto& dict = small_dict;
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
    doNotOptimizeAway(dict);
}

BENCHMARK_RELATIVE(SmallVectorFind, n)
{
    const std::vector<Point>& vec = small_vec;
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
    doNotOptimizeAway(vec);
}

BENCHMARK(SmallMapPtrFind, n)
{
    auto dict = small_dict_ptr;
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
    doNotOptimizeAway(dict);
}

BENCHMARK_RELATIVE(SmallVectorPtrFind, n)
{
    const std::vector<Point*>& vec = small_vec_ptr;
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
    doNotOptimizeAway(vec);
}
