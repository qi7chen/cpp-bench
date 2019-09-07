# cpp-bench


cpp-bench是一个非常轻量级的C++基准测试组件(benchmark component)。

这个组件取自[folly](https://github.com/facebook/folly/blob/master/folly/Benchmark.h),
并且移植到了Visual C++ 2013.




## How To Build

* 安装[CMake](https://cmake.org/download/)
* 使用CMake生成Visual Studio工程或者Linux Make files


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
i5-7500 3.4GHZ Windows 10 x64 (Visual C++ 2017)
============================================================================
cpp-bench\test\hashmap_bench.cpp                relative  time/iter  iters/s
============================================================================
TreeMapInsert                                                3.13us  319.92K
HashMapInsert                                    134.84%     2.32us  431.38K
TreeMapDelete                                                3.10us  322.84K
HashMapDelete                                    198.26%     1.56us  640.06K
TreeMapIntFind                                               2.21us  453.43K
HashMapIntFind                                   144.20%     1.53us  653.84K
============================================================================

E5-2630 2.3GHZ CentOS 7 x64 (GCC 5.3)
============================================================================
../test/map_bench.cpp                            relative  time/iter  iters/s
============================================================================
TreeMapInsert                                                3.23us  309.40K
HashMapInsert                                    103.37%     3.13us  319.83K
TreeMapDelete                                                3.15us  317.05K
HashMapDelete                                    147.78%     2.13us  468.54K
TreeMapIntFind                                               2.16us  463.27K
HashMapIntFind                                   138.02%     1.56us  639.42K
============================================================================

~~~~~~~~


说明:

`relative` 表示跟基准测试对比的数值

`time/iter`表示函数每次迭代消耗的时间

`iters/s` 表示函数每秒可以迭代多少次



[1]: https://graphics.stanford.edu/~seander/bithacks.html#IntegerLog10

[2]: http://www.slideshare.net/andreialexandrescu1/three-optimization-tips-for-c-15708507
