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

以 [map_bench.cpp](https://github.com/ichenq/cpp-bench/blob/master/test/map_bench.cpp)为例：
它测试std::map和std::unordered_map的insert, erase, find的性能差异。


这是在我机器上测试的结果：

~~~~~~~~cpp
i5-7300 3.4GHZ Windows 7 x64 (Visual C++ 2017)
============================================================================
..\test\map_bench.cpp                          relative  time/iter  iters/s
============================================================================
TreeMapInsert                                                3.13us  319.94K
HashMapInsert                                    124.03%     2.52us  396.81K
TreeMapDelete                                                2.61us  383.27K
HashMapDelete                                    166.52%     1.57us  638.21K
TreeMapIntFind                                               1.75us  572.95K
HashMapIntFind                                   112.74%     1.55us  645.92K
============================================================================

E5-2630 CentOS 7.2 x64 (GCC 5.3)
============================================================================
../test/map_bench.cpp                          relative  time/iter  iters/s
============================================================================
TreeMapInsert                                                6.26us  159.74K
HashMapInsert                                    100.25%     6.24us  160.14K
TreeMapDelete                                                6.70us  149.34K
HashMapDelete                                    125.58%     5.33us  187.54K
TreeMapIntFind                                               5.81us  172.04K
HashMapIntFind                                   128.20%     4.53us  220.57K
============================================================================
~~~~~~~~


说明:

`relative` 表示跟基准测试对比的数值

`time/iter`表示函数每次迭代消耗的时间

`iters/s` 表示函数每秒可以迭代多少次



[1]: https://graphics.stanford.edu/~seander/bithacks.html#IntegerLog10

[2]: http://www.slideshare.net/andreialexandrescu1/three-optimization-tips-for-c-15708507
