#include <string>

#include "ternary_search_tree.h"
#include "gtest/gtest.h"

TEST(MyAvlTree, DefaultConstructor) {
  util::ternary_search_tree<char> tree;

  EXPECT_EQ(0u, tree.size());
}
