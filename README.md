# cpp-bench


cpp-bench是一个非常轻量级的C++基准测试组件(benchmark component)。


## Introduction

这个组件取自[folly](https://github.com/facebook/folly/blob/master/folly/Benchmark.h),
并且移植到了Visual C++ 2013.


## Build

下载 [premake5](http://premake.github.io/download.html).


## API

使用 `BENCHMARK` 宏来引入一项基准测试
~~~~~~~~cpp
BENCHMARK(vectorPushBack, n)
{
   vector<int> v;
   v.push_back(42);
}
~~~~~~~~

后面所有的 `BENCHMARK_RELATIVE' 宏都以前面的benchmark为基准

~~~~~~~~cpp
BENCHMARK_RELATIVE(vectorPushFront, n)
{
   vector<int> v;
   v.insert(v.begin(), 42);
}
~~~~~~~~


在`BENCHMARK_SUSPEND` 宏里面的代码不会计入基准测试时间。benchmark's

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

可以使用`BENCHMARK_DRAW_LINE` 宏画一条线。

~~~~~~~~cpp
BENCHMARK_DRAW_LINE()
~~~~~~~~

## 示例

以 [ItoaBench.cpp](https://github.com/ichenq/cpp-bench/blob/master/test/ItoaBench.cpp)为例：
它测试不同的整数到字符串转换方法的效率。


Function      | Description
--------------|-----------
sprintf       | `sprintf()` in C standard library
naive         | Compute division/modulo of 10 for each digit, store digits in temp array and copy to buffer in reverse order.
count         | Count number of decimal digits first, using technique from [1].
lut           | Uses lookup table (LUT) of digit pairs for division/modulo of 100. Mentioned in [2]


这是在我机器上测试的结果(Core i5 @3.10Ghz)：

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


说明:

`relative` 表示跟基准测试对比的数值

`time/iter`表示函数每次迭代消耗的时间

`iters/s` 表示函数每秒可以迭代多少次

