// Copyright (C) 2014 ichenq@gmail.com. All rights reserved.
// Distributed under the terms and conditions of the Apache License.
// See accompanying files LICENSE.

/*
 * Copyright 2014 Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <functional>
#include "preprocessor.h"



/**
 * Runs all benchmarks defined. Usually put in main().
 */
void runBenchmarks();


namespace detail {

typedef std::pair<uint64_t, unsigned int> TimeIterPair;

/**
 * Adds a benchmark wrapped in a std::function. Only used
 * internally. Pass by value is intentional.
 */
void addBenchmarkImpl(const char* file,
                      const char* name,
                      std::function<TimeIterPair(unsigned int)>);

typedef std::function<void(void)> BenchmarkInitializer;

void addBenchmarkInit(BenchmarkInitializer initializer);

} // namespace detail

// Current tick count(in nanoseconds)
uint64_t getNowTickCount();



/**
 * Supporting type for BENCHMARK_SUSPEND defined below.
 */
struct BenchmarkSuspender
{
    BenchmarkSuspender() : start_(getNowTickCount())
    {
    }

    BenchmarkSuspender(const BenchmarkSuspender &) = delete;
    BenchmarkSuspender(BenchmarkSuspender&& rhs)
        : start_(rhs.start_)
    {
        rhs.start_ = getNowTickCount();
    }

    BenchmarkSuspender& operator=(const BenchmarkSuspender &) = delete;
    BenchmarkSuspender& operator=(BenchmarkSuspender && rhs)
    {
        start_ = rhs.start_;
        rhs.start_ = getNowTickCount();
        return *this;
    }

    ~BenchmarkSuspender()
    {
        tally();
    }

    void dismiss()
    {
        tally();
        start_ = getNowTickCount();
    }

    void rehire()
    {
        start_ = getNowTickCount();
    }

    /**
     * This helps the macro definition. To get around the dangers of
     * operator bool, returns a pointer to member (which allows no
     * arithmetic).
     */
    operator int BenchmarkSuspender::*() const
    {
        return nullptr;
    }

    /**
     * Accumulates nanoseconds spent outside benchmark.
     */
    typedef uint64_t NanosecondsSpent;
    static NanosecondsSpent nsSpent;

private:
    void tally()
    {
        auto end = getNowTickCount();
        nsSpent += (end - start_);
        start_ = end;
    }

    uint64_t    start_;
};

/**
 * Adds a benchmark. Usually not called directly but instead through
 * the macro BENCHMARK defined below. The lambda function involved
 * must take exactly one parameter of type unsigned, and the benchmark
 * uses it with counter semantics (iteration occurs inside the
 * function).
 */
template <typename Lambda>
void addBenchmarkWithTimes(const char* file, const char* name, Lambda&& lambda)
{
    auto execute = [=](unsigned int times)
    {
        BenchmarkSuspender::nsSpent = 0;
        unsigned int niter;

        // CORE MEASUREMENT STARTS
        auto const start = getNowTickCount();
        niter = lambda(times);
        auto const end = getNowTickCount();
        // CORE MEASUREMENT ENDS

        return detail::TimeIterPair(end - start - BenchmarkSuspender::nsSpent, niter);
    };

    detail::addBenchmarkImpl(file, name,
        std::function<detail::TimeIterPair(unsigned int)>(execute));
}

template <typename Lambda>
void addBenchmark(const char* file, const char* name, Lambda&& lambda) 
{
    addBenchmarkWithTimes(file, name, [=](unsigned int times) 
    {
        unsigned int niter = 0;
        while (times-- > 0) {
            niter += lambda(times);
        }
        return niter;
    });
}

/**
 * Call doNotOptimizeAway(var) against variables that you use for
 * benchmarking but otherwise are useless. The compiler tends to do a
 * good job at eliminating unused variables, and this function fools
 * it into thinking var is in fact needed.
 */
#ifdef _MSC_VER
#pragma optimize("", off)
#endif

template <class T>
void doNotOptimizeAway(T&& datum)
{
    // This forces the value to never be optimized away
    // by taking a reference then using it.
    const void* p = &datum;
    if (p == nullptr)
    {
        putchar(*reinterpret_cast<const char*>(p));
    }
}

#ifdef _MSC_VER
#pragma optimize("", on)
#endif



/**
 * Introduces a benchmark function. Used internally, see BENCHMARK and
 * friends below.
 */
#define BENCHMARK_IMPL(funName, stringName, paramType, paramName)       \
  static void funName(paramType);                                       \
  static bool FB_ANONYMOUS_VARIABLE(follyBenchmarkUnused) = (           \
      addBenchmark(__FILE__, stringName,                                \
      [](paramType paramName) -> unsigned { funName(paramName);         \
        return 1; }), true);                                            \
  static void funName(paramType paramName)

/**
 * Introduces a benchmark function with support for returning the actual
 * number of iterations. Used internally, see BENCHMARK_MULTI and friends
 * below.
 */
#define BENCHMARK_MULTI_IMPL(funName, stringName, paramType, paramName) \
  static unsigned funName(paramType);                                   \
  static bool FB_ANONYMOUS_VARIABLE(follyBenchmarkUnused) = (           \
      addBenchmark(__FILE__, stringName,                                \
      [](paramType paramName) { return funName(paramName); }),          \
    true);                                                              \
  static unsigned funName(paramType paramName)

/**
 * Introduces a benchmark function. Use with two arguments. The first 
 * is the name of the benchmark. Use something descriptive, such as 
 * insertVectorBegin. The second argument may be missing, or could be 
 * a symbolic counter. The counter dictates how many internal iteration 
 * the benchmark does. Example:
 *
 * BENCHMARK(insertVectorBegin, n) {
 *   vector<int> v;
 *   for(auto i = 0; i < n; i++) {
 *     v.insert(v.begin(), 42);
 *   }
 * }
 */
#define BENCHMARK(name, n)      \
      BENCHMARK_IMPL(           \
        name,                   \
        FB_STRINGIZE(name),     \
        unsigned,               \
        n)

/**
 * Draws a line of dashes.
 */
#define BENCHMARK_DRAW_LINE()                                       \
  static bool FB_ANONYMOUS_VARIABLE(follyBenchmarkUnused) = (       \
    addBenchmark(__FILE__, "-",                                     \
        [](unsigned) -> unsigned { return 0; }),                    \
    true);

/**
 * Draws a line of dashes.
 */
#define BENCHMARK_INITIALIZER(funName)                              \
    static void funName();                                          \
    static bool FB_ANONYMOUS_VARIABLE(follyBenchmarkUnused) = (     \
    detail::addBenchmarkInit(funName), true);                       \
    static void funName()

/**
 * Allows execution of code that doesn't count torward the benchmark's
 * time budget. Example:
 *
 * BENCHMARK_START_GROUP(insertVectorBegin, n) {
 *   vector<int> v;
 *   BENCHMARK_SUSPEND {
 *     v.reserve(n);
 *   }
 *   for(auto i = 0; i < n; i++) {
 *     v.insert(v.begin(), 42);
 *   }
 * }
 */
#define BENCHMARK_SUSPEND                               \
  if (auto FB_ANONYMOUS_VARIABLE(BENCHMARK_SUSPEND) =   \
      BenchmarkSuspender()) {}                          \
  else


/**
* Just like BENCHMARK, but prints the time relative to a
* baseline. The baseline is the most recent BENCHMARK() seen in
* lexical order. Example:
*
* // This is the baseline
* BENCHMARK(insertVectorBegin, n) {
*   vector<int> v;
*   for(auto i = 0; i < n; i++) {
*     v.insert(v.begin(), 42);
*   }
* }
*
* BENCHMARK_RELATIVE(insertListBegin, n) {
*   list<int> s;
*   for(auto i = 0; i < n; i++) {
*     s.insert(s.begin(), 42);
*   }
* }
*
* Any number of relative benchmark can be associated with a
* baseline. Another BENCHMARK() occurrence effectively establishes a
* new baseline.
*/
#define BENCHMARK_RELATIVE(name, n)     \
      BENCHMARK_IMPL(                   \
        name,                           \
        "%" FB_STRINGIZE(name),         \
        unsigned,                       \
        n)
