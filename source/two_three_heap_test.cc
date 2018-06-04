#include <string>

#include "two_three_heap.h"
#include "gtest/gtest.h"

TEST(MyAvlTree, DefaultConstructor) {
  util::two_three_heap<int> tree;

  EXPECT_EQ(0u, tree.size());
}
