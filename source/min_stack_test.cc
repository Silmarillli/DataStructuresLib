#include <string>

#include "min_stack.h"
#include "gtest/gtest.h"

TEST(MyAvlTree, DefaultConstructor) {
  util::min_stack<int> tree;

  EXPECT_EQ(0u, tree.size());
}