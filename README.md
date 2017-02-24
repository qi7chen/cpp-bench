# cpp-bench


cpp-bench是一个非常轻量级的C++基准测试组件(benchmark component)。

这个组件取自[folly](https://github.com/facebook/folly/blob/master/folly/Benchmark.h),
并且移植到了Visual C++ 2013.




## Build

需要[cmake](https://cmake.org/)工具链.


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


在`BENCHMARK_SUSPEND` 宏里面的代码不会计入基准测试时间。

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
Windows 7 x64
============================================================================
..\test\itoa_bench.cpp                          relative  time/iter  iters/s
============================================================================
ItoaSprintf                                                128.21ns    7.80M
ItoaMwilson                                      435.79%    29.42ns   33.99M
ItoaNaive                                        464.58%    27.60ns   36.24M
ItoaCount                                        424.83%    30.18ns   33.14M
ItoaLut                                          491.63%    26.08ns   38.35M
============================================================================

Ubuntu x64 14.04
============================================================================
../test/itoa_bench.cpp                          relative  time/iter  iters/s
============================================================================
ItoaSprintf                                                 70.47ns   14.19M
ItoaMwilson                                      303.36%    23.23ns   43.05M
ItoaNaive                                        318.15%    22.15ns   45.15M
ItoaCount                                        286.85%    24.57ns   40.70M
ItoaLut                                          332.35%    21.20ns   47.16M
============================================================================
~~~~~~~~


说明:

`relative` 表示跟基准测试对比的数值

`time/iter`表示函数每次迭代消耗的时间

`iters/s` 表示函数每秒可以迭代多少次



[1]: https://graphics.stanford.edu/~seander/bithacks.html#IntegerLog10

[2]: http://www.slideshare.net/andreialexandrescu1/three-optimization-tips-for-c-15708507
