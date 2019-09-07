// Copyright (C) 2014-present prototyped.cn All rights reserved.
// Distributed under the terms and conditions of the Apache License. 
// See accompanying files LICENSE.

#include <stdlib.h>
#include <map>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "Benchmark.h"

const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const int MAX_KEY_LEN = 64;

std::string randAlphabetString(int length)
{
    std::string text;
    text.resize(length);
    for (int i = 0; i < length; i++)
    {
        int idx = rand() % alphabet.size();
        text[i] = alphabet[idx];
    }
    return std::move(text);
}

template <typename T>
T& createStringKeyMap(const std::vector<std::string>& vec, T& dict)
{
    for (auto i = 0U; i < vec.size(); i++)
    {
        dict[vec[i]] = i * i;
    }
    return dict;
}

void createStringIndex(std::vector<std::string>& vec, int n)
{
    vec.resize(n);
    for (int i = 0; i < n; i++)
    {
        vec[i] = randAlphabetString(rand() % MAX_KEY_LEN);
    }
}


// random find
BENCHMARK(TreeMapStringFind, n)
{
    std::map<std::string, int> dict;
    std::vector<std::string> index;
    BENCHMARK_SUSPEND
    {
        createStringIndex(index, n);
        createStringKeyMap(index, dict);
        std::random_shuffle(index.begin(), index.end());
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

BENCHMARK_RELATIVE(HashMapStringFind, n)
{
    std::unordered_map<std::string, int> dict;
    std::vector<std::string> index;
    BENCHMARK_SUSPEND
    {
        createStringIndex(index, n);
        createStringKeyMap(index, dict);
        std::random_shuffle(index.begin(), index.end());
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