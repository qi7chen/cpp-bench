#include <stdlib.h>
#include <map>
#include <unordered_map>
#include <algorithm>
#include "Benchmark.h"

template <typename T>
T& createMap(T& dict, int n)
{
    for (int i = 0; i < n; i++)
    {
        dict[i] = i * i;
    }
    return dict;
}

void createIndex(std::vector<int>& vec, int n) 
{
    vec.resize(n);
    for (int i = 0; i < n; i++)
    {
        vec[i] = i;
    }
    random_shuffle(vec.begin(), vec.end());
}

// random insert
BENCHMARK(MapInsert, n)
{
    std::map<int, int> dict;
    std::vector<int> index;
    BENCHMARK_SUSPEND{
        createIndex(index, n);
    }
    for (unsigned i = 0; i < n; i++)
    {
        dict[index[i]] = i;
    }
    doNotOptimizeAway(dict);
}

BENCHMARK(HashMapInsert, n)
{
    std::unordered_map<int, int> dict;
    std::vector<int> index;
    BENCHMARK_SUSPEND{
        createIndex(index, n);
    }
    for (unsigned i = 0; i < n; i++)
    {
        dict[index[i]] = i;
    }
    doNotOptimizeAway(dict);
}

// random delete
BENCHMARK(MapDelete, n)
{
    std::map<int, int> dict;
    std::vector<int> index;
    BENCHMARK_SUSPEND{
        createMap(dict, n);
        createIndex(index, n);
    }
    for (unsigned i = 0; i < n; i++)
    {
        dict.erase(index[i]);
    }
    doNotOptimizeAway(dict);
}

BENCHMARK(HashMapDelete, n)
{
    std::unordered_map<int, int> dict;
    std::vector<int> index;
    BENCHMARK_SUSPEND{
        createMap(dict, n);
        createIndex(index, n);
    }
    for (unsigned i = 0; i < n; i++)
    {
        dict.erase(index[i]);
    }
    doNotOptimizeAway(dict);
}

// random find
BENCHMARK(MapFind, n)
{
    std::map<int, int> dict;
    std::vector<int> index;
    BENCHMARK_SUSPEND{
        createMap(dict, n);
        createIndex(index, n);
    }
    int64_t total = 0;
    for (unsigned i = 0; i < n; i++)
    {
        auto iter = dict.find(index[i]);
        if (iter != dict.end())
        {
            total += iter->second;
        }
    }
    doNotOptimizeAway(dict);
    doNotOptimizeAway(total);
}

BENCHMARK(HashMapFind, n)
{
    std::unordered_map<int, int> dict;
    std::vector<int> index;
    BENCHMARK_SUSPEND{
        createMap(dict, n);
        createIndex(index, n);
    }
    int64_t total = 0;
    for (unsigned i = 0; i < n; i++)
    {
        auto iter = dict.find(index[i]);
        if (iter != dict.end())
        {
            total += iter->second;
        }
    }
    doNotOptimizeAway(dict);
    doNotOptimizeAway(total);
}
