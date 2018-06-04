#include <string>

#include "hash_map.h"
#include "gtest/gtest.h"

TEST(MyAvlTree, DefaultConstructor) {
  util::hash_map<std::string, int> tree;

  EXPECT_EQ(0u, tree.size());
}
/*