#include <string>

#include "splay_tree.h"
#include "gtest/gtest.h"

TEST(MyAvlTree, DefaultConstructor) {
  util::splay_tree<std::string, int> tree;

  EXPECT_EQ(0u, tree.size());
}
/*
TEST(MyAvlTree, CopyConstructor_Small) {
  util::splay_tree<int> tree1;
  tree1.push(10);
  tree1.push(20);
  
  util::splay_tree<int> tree2(tree1);

  EXPECT_EQ(tree1.size() ,tree2.size());
}
*/
/*
TEST(MyAvlTree, CopyConstructor_Large) {
  util::splay_tree<int> tree1;
  for (int i = 1; i <= 1000; i++) {
    tree1.push(i);
  }

  util::splay_tree<int>tree2(tree1);


  EXPECT_EQ(tree1.size() ,tree2.size());
}


TEST(MyAvlTree, Push_Normal) {

  util::splay_tree<int> tree;
  for (int i = 1; i <= 10; i++) {
    tree.push(i);
  }
  EXPECT_EQ(10, tree.size());
}

TEST(MyAvlTree, Push_Large) {

  util::splay_tree<int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.push(i);
  }
  EXPECT_EQ(10000, tree.size());
}

TEST(MyAvlTree, Top) {
  
  util::splay_tree<int> tree;
  for (int i = 1; i <= 10; i++) {
    tree.push(i);
  }
  EXPECT_EQ(1, tree.top());
  tree.pop();
  EXPECT_EQ(2, tree.top());
  tree.pop();
  EXPECT_EQ(3, tree.top());
  tree.pop();
  EXPECT_EQ(4, tree.top());
  tree.pop();
  EXPECT_EQ(5, tree.top());
}

TEST(MyAvlTree, Pop_Normal) {

  util::splay_tree<int> tree;
  for (int i = 1; i <= 10; i++) {
    tree.push(i);
  }
  EXPECT_EQ(10, tree.size());
  for (int i = 1; i <= 10; i++) {
    tree.pop();
  }
  EXPECT_EQ(0u, tree.size());
}


TEST(MyAvlTree, Pop_Large) {

  util::splay_tree<int> tree;
  for (int i = 1; i <= 10000; i++) {
    tree.push(i);
  }
  EXPECT_EQ(10000, tree.size());
   for (int i = 1; i <= 10000; i++) {
    tree.pop();
  }
  EXPECT_EQ(0u, tree.size());
}

TEST(MyAvlTree, Merge1_Small) {

  util::splay_tree<int> tree1;
  for (int i = 1; i <= 10; i++) {
    tree1.push(i);
  }

  util::splay_tree<int> tree2;
  tree2.merge(tree1);

  EXPECT_EQ(10,tree2.size());
}

TEST(MyAvlTree, Merge1_Large) {

  util::splay_tree<int> tree1;
  for (int i = 1; i <= 1000; i++) {
    tree1.push(i);
  }

  util::splay_tree<int>tree2;
 tree2.merge(tree1);

  EXPECT_EQ(1000,tree2.size());
}


TEST(MyAvlTree, Merge12_Small) {

  util::splay_tree<int> tree1;
  for (int i = 1; i <= 10; i++) {
    tree1.push(i);
  }

  util::splay_tree<int>tree2;
  for (int i = 1; i <= 10; i++) {
   tree2.push(i);
  }
  
 tree2.merge(tree1);

  EXPECT_EQ(20,tree2.size());
}

TEST(MyAvlTree, Merge12_Large) {

  util::splay_tree<int> tree1;
  for (int i = 1; i <= 1000; i++) {
    tree1.push(i);
  }

  util::splay_tree<int>tree2;
  for (int i = 1; i <= 1000; i++) {
   tree2.push(i);
  }
  
 tree2.merge(tree1);

  EXPECT_EQ(2000, tree2.size());
}


TEST(MyAvlTree, Swap_Small) {
  util::splay_tree<int> tree1;
  for (int i = 1; i <= 10; i++) {
    tree1.push(i);
  }

  util::splay_tree<int>tree2;
  for (int i = 1; i <= 20; i++) {
   tree2.push(i);
  }

  tree1.swap(tree2);
  EXPECT_EQ(20, tree1.size());
  EXPECT_EQ(10,tree2.size());
}

TEST(MyAvlTree, Swap_Large) {
  util::splay_tree<int> tree1;
  for (int i = 1; i <= 1000; i++) {
    tree1.push(i);
  }

  util::splay_tree<int>tree2;
  for (int i = 1; i <= 2000; i++) {
   tree2.push(i);
  }

  tree1.swap(tree2);
  EXPECT_EQ(2000, tree1.size());
  EXPECT_EQ(1000,tree2.size());
}

TEST(MyAvlTree, Empty) {
  util::splay_tree<int> tree1;
  util::splay_tree<int> tree2(tree1);

  EXPECT_TRUE(tree1.empty());
  EXPECT_TRUE(tree2.empty());

  tree1.push(1);
  tree2.push(2);
  EXPECT_FALSE(tree1.empty());
  EXPECT_FALSE(tree2.empty());
}


*/


