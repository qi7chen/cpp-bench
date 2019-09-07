# Copyright (C) 2014-present prototyped.cn All rights reserved.
# Distributed under the terms and conditions of the Apache License. 
# See accompanying files LICENSE.

project (BenchTest)


file(GLOB BENCH_HEADER_FILES *.h)
file(GLOB BENCH_SOURCE_FILES *.cpp)


if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
    add_executable(BenchTest WIN32 ${BENCH_HEADER_FILES} ${BENCH_SOURCE_FILES})
elseif(UNIX)
    add_executable(BenchTest ${BENCH_HEADER_FILES} ${BENCH_SOURCE_FILES})
    target_link_libraries(BenchTest rt)
endif()

target_link_libraries(BenchTest libbench)
