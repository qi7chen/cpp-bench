cmake_minimum_required(VERSION 2.8)
project (CppBench)

set(CPP_PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(CPP_PROJECT_SRC_DIR ${CPP_PROJECT_ROOT_DIR}/src)

set(EXECUTABLE_OUTPUT_PATH ${CPP_PROJECT_ROOT_DIR}/bin)

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
    add_definitions(-DNOMINMAX)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif(UNIX)
    add_definitions(-D__STDC_LIMIT_MACROS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")
endif()

include_directories(${CPP_PROJECT_SRC_DIR})

add_subdirectory(test) 
