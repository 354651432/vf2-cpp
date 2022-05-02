cmake_minimum_required(VERSION 3.0)
project(test LANGUAGES CXX)

set(gtest ~/code/googletest/googletest)
link_directories(${gtest}/build/lib)
include_directories(${gtest}/include)
link_libraries(pthread gtest gtest_main)

add_compile_options(-g)

add_executable(test match-test.cpp other-test.cpp)