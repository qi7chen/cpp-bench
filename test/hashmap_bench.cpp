// Copyright (C) 2014-present prototyped.cn All rights reserved.
// Distributed under the terms and conditions of the Apache License. 
// See accompanying files LICENSE.

#include <stdlib.h>
#include <map>
#include <unordered_map>
#include <algorithm>
#include "Benchmark.h"

template <typename T>
T& createIntKeyMap(T& dict, int n)
{
    for (int i = 0; i < n; i++)
    {
        dict[i] = i * i;
    }
    return dict;
}

void createIntIndex(std::vector<int>& vec, int n) 
{
    vec.resize(n);
    for (int i = 0; i < n; i++)
    {
        vec[i] = i;
    }
    random_shuffle(vec.begin(), vec.end());
}

// random insert
BENCHMARK(TreeMapInsert, n)
{
    std::map<int, int> dict;
    std::vector<int> index;
    BENCHMARK_SUSPEND
    {
        createIntIndex(index, n);
    }
    for (unsigned i = 0; i < n; i++)
    {
        dict[index[i]] = i;
    }
    doNotOptimizeAway(dict);
}

BENCHMARK_RELATIVE(HashMapInsert, n)
{
    std::unordered_map<int, int> dict;
    std::vector<int> index;
    BENCHMARK_SUSPEND
    {
        createIntIndex(index, n);
    }
    for (unsigned i = 0; i < n; i++)
    {
        dict[index[i]] = i;
    }
    doNotOptimizeAway(dict);
}

// random delete
BENCHMARK(TreeMapDelete, n)
{
    std::map<int, int> dict;
    std::vector<int> index;
    BENCHMARK_SUSPEND
    {
        createIntKeyMap(dict, n);
        createIntIndex(index, n);
    }
    for (unsigned i = 0; i < n; i++)
    {
        dict.erase(index[i]);
    }
    doNotOptimizeAway(dict);
}

BENCHMARK_RELATIVE(HashMapDelete, n)
{
    std::unordered_map<int, int> dict;
    std::vector<int> index;
    BENCHMARK_SUSPEND
    {
        createIntKeyMap(dict, n);
        createIntIndex(index, n);
    }
    for (unsigned i = 0; i < n; i++)
    {
        dict.erase(index[i]);
    }
    doNotOptimizeAway(dict);
}

// random find
BENCHMARK(TreeMapIntFind, n)
{
    std::map<int, int> dict;
    std::vector<int> index;
    BENCHMARK_SUSPEND
    {
        createIntKeyMap(dict, n);
        createIntIndex(index, n);
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

BENCHMARK_RELATIVE(HashMapIntFind, n)
{
    std::unordered_map<int, int> dict;
    std::vector<int> index;
    BENCHMARK_SUSPEND
    {
        createIntKeyMap(dict, n);
        createIntIndex(index, n);
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
