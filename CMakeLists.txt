cmake_minimum_required(VERSION 2.6)

# Locate GTest

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library

add_executable(binomial_heap binomial_heap_test.cc gtest_main.cc)
add_executable(avl_tree avl_tree_test.cc gtest_main.cc)
add_executable(bounded_pq bounded_pq_test.cc gtest_main.cc)
add_executable(min_queue min_queue_test.cc gtest_main.cc)
add_executable(min_stack min_stack_test.cc gtest_main.cc)
add_executable(splay_tree splay_tree_test.cc gtest_main.cc)
add_executable(ternary_search_tree ternary_search_tree_test.cc gtest_main.cc)
add_executable(treap treap_test.cc gtest_main.cc)
add_executable(skew_binomial_heap skew_binomial_heap_test.cc gtest_main.cc)
add_executable(van_emde_boas_tree van_emde_boas_tree_test.cc gtest_main.cc)
add_executable(two_three_heap two_three_heap_test.cc gtest_main.cc)


target_link_libraries(binomial_heap ${GTEST_LIBRARIES} pthread)
target_link_libraries(avl_tree ${GTEST_LIBRARIES} pthread)
target_link_libraries(bounded_pq ${GTEST_LIBRARIES} pthread)
target_link_libraries(min_queue ${GTEST_LIBRARIES} pthread)
target_link_libraries(min_stack ${GTEST_LIBRARIES} pthread)
target_link_libraries(splay_tree ${GTEST_LIBRARIES} pthread)
target_link_libraries(ternary_search_tree ${GTEST_LIBRARIES} pthread)
target_link_libraries(treap ${GTEST_LIBRARIES} pthread)
target_link_libraries(skew_binomial_heap ${GTEST_LIBRARIES} pthread)
target_link_libraries(van_emde_boas_tree ${GTEST_LIBRARIES} pthread)
target_link_libraries(two_three_heap ${GTEST_LIBRARIES} pthread)
