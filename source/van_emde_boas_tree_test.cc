#include <string>

#include "van_emde_boas_tree.cc"
#include "gtest/gtest.h"

TEST(MyAvlTree, DefaultConstructor) {
  util::van_emde_boas_tree tree;
  tree.insert(137);

  EXPECT_EQ(1, tree.size());
}
