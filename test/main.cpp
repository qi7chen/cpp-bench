// Copyright (C) 2014-present prototyped.cn All rights reserved.
// Distributed under the terms and conditions of the Apache License. 
// See accompanying files LICENSE.

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
