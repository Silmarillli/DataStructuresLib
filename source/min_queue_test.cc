#include <string>

#include "min_queue.h"
#include "gtest/gtest.h"

TEST(MyAvlTree, DefaultConstructor) {
  util::min_queue<int> tree;

  EXPECT_EQ(0u, tree.size());
}