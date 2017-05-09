cmake_minimum_required(VERSION 2.8)
project (BenchTest)

set(TARGET_NAME BenchTest)

file(GLOB_RECURSE BENCH_HEADER_FILES ${CPP_PROJECT_SRC_DIR}/*.h)
file(GLOB_RECURSE BENCH_SOURCE_FILES ${CPP_PROJECT_SRC_DIR}/*.cpp)

set(SOURCE_FILES
    main.cpp
    map_bench.cpp
    ) 
    
add_executable(${TARGET_NAME} ${BENCH_HEADER_FILES} ${BENCH_SOURCE_FILES} ${SOURCE_FILES})

if (WIN32)
    TARGET_LINK_LIBRARIES(${TARGET_NAME})
elseif(UNIX)
    TARGET_LINK_LIBRARIES(${TARGET_NAME} rt)
endif()
