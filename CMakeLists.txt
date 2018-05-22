cmake_minimum_required(VERSION 2.6)

# Locate GTest

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library

add_executable(BinomialHeap Binomial_heap_test.cc gtest_main.cc)
target_link_libraries(BinomialHeap ${GTEST_LIBRARIES} pthread)