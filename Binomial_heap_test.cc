
#include "BinomialHeap.hh"
#include "gtest/gtest.h"

TEST(MyHeap, DefaultConstructor) {
  BinomialHeap<int> heap;

  EXPECT_EQ(0u, heap.size());
}

TEST(MyHeap, CopyConstructor_Small) {
  BinomialHeap<int> heap1;
  heap1.push(10);
  heap1.push(20);
  
  BinomialHeap<int> heap2(heap1);

  EXPECT_EQ(heap1.size() , heap2.size());
}

/*
TEST(MyHeap, CopyConstructor_Large) {
  BinomialHeap<int> heap1;
  for (int i = 1; i <= 1000; i++) {
    heap1.push(i);
  }

  BinomialHeap<int> heap2(heap1);


  EXPECT_EQ(heap1.size() , heap2.size());
}
*/

TEST(MyHeap, Push_Normal) {

  BinomialHeap<int> heap;
  for (int i = 1; i <= 10; i++) {
    heap.push(i);
  }
  EXPECT_EQ(10, heap.size());
}

TEST(MyHeap, Push_Large) {

  BinomialHeap<int> heap;
  for (int i = 1; i <= 10000; i++) {
    heap.push(i);
  }
  EXPECT_EQ(10000, heap.size());
}

TEST(MyHeap, Top) {
  
  BinomialHeap<int> heap;
  for (int i = 1; i <= 10; i++) {
    heap.push(i);
  }
  EXPECT_EQ(1, heap.top());
  heap.pop();
  EXPECT_EQ(2, heap.top());
  heap.pop();
  EXPECT_EQ(3, heap.top());
  heap.pop();
  EXPECT_EQ(4, heap.top());
  heap.pop();
  EXPECT_EQ(5, heap.top());
}

TEST(MyHeap, Pop_Normal) {

  BinomialHeap<int> heap;
  for (int i = 1; i <= 10; i++) {
    heap.push(i);
  }
  EXPECT_EQ(10, heap.size());
  for (int i = 1; i <= 10; i++) {
    heap.pop();
  }
  EXPECT_EQ(0u, heap.size());
}


TEST(MyHeap, Pop_Large) {

  BinomialHeap<int> heap;
  for (int i = 1; i <= 10000; i++) {
    heap.push(i);
  }
  EXPECT_EQ(10000, heap.size());
   for (int i = 1; i <= 10000; i++) {
    heap.pop();
  }
  EXPECT_EQ(0u, heap.size());
}

TEST(MyHeap, Merge1_Small) {

  BinomialHeap<int> heap1;
  for (int i = 1; i <= 10; i++) {
    heap1.push(i);
  }

  BinomialHeap<int> heap2;
  heap2.merge(heap1);

  EXPECT_EQ(10, heap2.size());
}

TEST(MyHeap, Merge1_Large) {

  BinomialHeap<int> heap1;
  for (int i = 1; i <= 1000; i++) {
    heap1.push(i);
  }

  BinomialHeap<int> heap2;
  heap2.merge(heap1);

  EXPECT_EQ(1000, heap2.size());
}


TEST(MyHeap, Merge12_Small) {

  BinomialHeap<int> heap1;
  for (int i = 1; i <= 10; i++) {
    heap1.push(i);
  }

  BinomialHeap<int> heap2;
  for (int i = 1; i <= 10; i++) {
    heap2.push(i);
  }
  
  heap2.merge(heap1);

  EXPECT_EQ(20, heap2.size());
}

TEST(MyHeap, Merge12_Large) {

  BinomialHeap<int> heap1;
  for (int i = 1; i <= 1000; i++) {
    heap1.push(i);
  }

  BinomialHeap<int> heap2;
  for (int i = 1; i <= 1000; i++) {
    heap2.push(i);
  }
  
  heap2.merge(heap1);

  EXPECT_EQ(2000, heap2.size());
}


TEST(MyHeap, Swap_Small) {
  BinomialHeap<int> heap1;
  for (int i = 1; i <= 10; i++) {
    heap1.push(i);
  }

  BinomialHeap<int> heap2;
  for (int i = 1; i <= 20; i++) {
    heap2.push(i);
  }

  heap1.swap(heap2);
  EXPECT_EQ(20, heap1.size());
  EXPECT_EQ(10, heap2.size());
}

TEST(MyHeap, Swap_Large) {
  BinomialHeap<int> heap1;
  for (int i = 1; i <= 1000; i++) {
    heap1.push(i);
  }

  BinomialHeap<int> heap2;
  for (int i = 1; i <= 2000; i++) {
    heap2.push(i);
  }

  heap1.swap(heap2);
  EXPECT_EQ(2000, heap1.size());
  EXPECT_EQ(1000, heap2.size());
}

TEST(MyHeap, Empty) {
  BinomialHeap<int> heap1;
  BinomialHeap<int> heap2(heap1);

  EXPECT_TRUE(heap1.empty());
  EXPECT_TRUE(heap2.empty());

  heap1.push(1);
  heap2.push(2);
  EXPECT_FALSE(heap1.empty());
  EXPECT_FALSE(heap2.empty());
}






