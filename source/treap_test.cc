#include <string>

#include "treap.h"
#include "gtest/gtest.h"

TEST(MyAvlTree, DefaultConstructor) {
  util::Treap<std::string, int> tree;

  EXPECT_EQ(0u, tree.size());
}
