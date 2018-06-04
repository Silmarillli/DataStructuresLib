#include "bounded_pq.h"
#include "gtest/gtest.h"

TEST(MyAvlTree, DefaultConstructor) {
  BoundedPQueue<int> tree(15);

  EXPECT_EQ(0u, tree.size());
}