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


这是在我机器上测试的结果(Core i5 @3.10Ghz)：

~~~~~~~~cpp
Windows 7 x64 (Visual C++ 2013)
============================================================================
..\test\map_bench.cpp                          relative  time/iter  iters/s
============================================================================
TreeMapInsert                                               12.51us   79.91K
HashMapInsert                                    100.00%    12.51us   79.92K
TreeMapDelete                                               12.51us   79.92K
HashMapDelete                                     67.50%    18.54us   53.94K
TreeMapFind                                                  9.62us  103.98K
HashMapFind                                       88.39%    10.88us   91.91K
============================================================================

CentOS 6.9 x64 (GCC 4.8)
============================================================================
../test/map_bench.cpp                          relative  time/iter  iters/s
============================================================================
MapInsert                                                    2.27us  439.83K
HashMapInsert                                     97.19%     2.34us  427.47K
MapDelete                                                    1.95us  512.66K
HashMapDelete                                    124.85%     1.56us  640.08K
MapFind                                                      1.56us  639.31K
HashMapFind                                      105.54%     1.48us  674.74K
============================================================================
~~~~~~~~


说明:

`relative` 表示跟基准测试对比的数值

`time/iter`表示函数每次迭代消耗的时间

`iters/s` 表示函数每秒可以迭代多少次



[1]: https://graphics.stanford.edu/~seander/bithacks.html#IntegerLog10

[2]: http://www.slideshare.net/andreialexandrescu1/three-optimization-tips-for-c-15708507
