#include <iostream>
#include "Benchmark.h"
#include <time.h>
#include <stdlib.h>

using std::cout;
using std::endl;


int main(int argc, char* argv[])
{
    srand((int)time(NULL));
    cout << "\nPATIENCE, BENCHMARKS IN PROGRESS." << endl;
    runBenchmarks();
    cout << "MEASUREMENTS DONE." << endl;
    return 0;
}
