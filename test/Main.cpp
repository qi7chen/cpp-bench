#include <iostream>
#include "Benchmark.h"

using std::cout;
using std::endl;


int main(int argc, char* argv[])
{
    FLAGS_benchmark = true;

    // benchmarks
    if (FLAGS_benchmark)
    {
        cout << "\nPATIENCE, BENCHMARKS IN PROGRESS." << endl;
        runBenchmarks();
        cout << "MEASUREMENTS DONE." << endl;
    }
    
    return 0;
}
