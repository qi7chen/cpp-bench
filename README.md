# cpp-bench


Lightweight bencharking component for your C++ code.


## Introduction

This component was taken from [folly](https://github.com/facebook/folly/blob/master/folly/Benchmark.h), 
with efforts porting to Visual C++.

## Usage

The `BENCHMARK` macro introduces a benchmark function:
~~~~~~~~cpp
BENCHMARK(vectorPushBack, n)
{
   vector<int> v;
   v.push_back(42);
}
~~~~~~~~
and any number of `BENCHMARK_RELATIVE' macro defined introduce relative benchmarks associated with a
baseline:
~~~~~~~~cpp
BENCHMARK_RELATIVE(vectorPushFront, n)
{
   vector<int> v;
   v.insert(v.begin(), 42);
}
~~~~~~~~


`BENCHMARK_SUSPEND` allows execution of code that doesn't count torward the benchmark's
time budget:
~~~~~~~~cpp
BENCHMARK(insertVectorBegin, n) 
{
   vector<int> v;
   BENCHMARK_SUSPEND 
   {
     v.reserve(n);
   }
   for(auto i = 0; i < n; i++) 
   {
     v.insert(v.begin(), 42);
   }
}
~~~~~~~~
and `BENCHMARK_DRAW_LINE` draws a line of dashes.
~~~~~~~~cpp
BENCHMARK_DRAW_LINE()
~~~~~~~~

## Results

The `src\ItoaBench.cpp` takes an example usage of cpp-bench, measures different `itoa` algorithms.
taken from `rapidjson`'s [itoa-benchmark](https://github.com/miloyip/itoa-benchmark).

Function      | Description
--------------|-----------
sprintf       | `sprintf()` in C standard library
naive         | Compute division/modulo of 10 for each digit, store digits in temp array and copy to buffer in reverse order.
count         | Count number of decimal digits first, using technique from [1].
lut           | Uses lookup table (LUT) of digit pairs for division/modulo of 100. Mentioned in [2]

The following are `sequential` results measured on a 64bit PC (Core i5 @3.10Ghz)

~~~~~~~~cpp
Ubuntu x64 12.04 (i5-3.10GHz 4G)
----------------------------------------------------------------------------
../test/ItoaBench.cpp                           relative  time/iter  iters/s
----------------------------------------------------------------------------
ItoaSprintf                                                 91.52ns   10.93M
ItoaMwilson                                      294.35%    31.09ns   32.16M
ItoaNaive                                        318.20%    28.76ns   34.77M
ItoaCount                                        299.49%    30.56ns   32.72M
ItoaLut                                          363.15%    25.20ns   39.68M
----------------------------------------------------------------------------

Windows 7 x64 (i5-3.10GHz 4G)
----------------------------------------------------------------------------
../test/ItoaBench.cpp                           relative  time/iter  iters/s
----------------------------------------------------------------------------
ItoaSprintf                                                102.49ns    9.76M
ItoaMwilson                                      405.10%    25.30ns   39.53M
ItoaNaive                                        405.12%    25.30ns   39.53M
ItoaCount                                        399.97%    25.62ns   39.03M
ItoaLut                                          424.08%    24.17ns   41.38M
----------------------------------------------------------------------------
~~~~~~~~
