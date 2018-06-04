#ifndef MinQueue_Included
#define MinQueue_Included

#include "min_stack.h"
#include <functional>    // For std::less

namespace util {

/**
 * Class: min_queue<T, Comparator = std::less<T> >
 * ---------------------------------------------------------------------------
 * A class representing a min-queue of elements of type T ordered according to
 * some Comparator type.
 */
template <typename T,
          typename Comparator = std::less<T> >
class min_queue {
public:
  /**
   * Constructor: min_queue(Comparator = Comparator());
   * Usage: min_queue<T> myQueue;
   *        min_queue<T, C> myQueue(myComparator);
   * -------------------------------------------------------------------------
   * Constructs a new min_queue that uses the specified comparator to make
   * comparisons.
   */
  explicit min_queue(Comparator = Comparator());

  /**
   * void enqueue(const T& val);
   * Usage: myQueue.enqueue(137);
   * -------------------------------------------------------------------------
   * Enqueues a new element into the min queue.
   */
  void enqueue(const T& val);

  /**
   * void dequeue();
   * Usage: myQueue.dequeue();
   * -------------------------------------------------------------------------
   * Dequeues the front of the queue.  If the queue is empty, the behavior is
   * undefined.
   */
  void dequeue();

  /**
   * const T& front() const;
   * Usage: cout << myQueue.front() << endl;
   * -------------------------------------------------------------------------
   * Returns an immutable view of the front element of the queue.  If the
   * queue is empty, the behavior is undefined.
   */
  const T& front() const;

  /**
   * const T& min() const;
   * Usage: cout << myQueue.min() << endl;
   * -------------------------------------------------------------------------
   * Returns an immutable view of the minimum element of the queue.  If the
   * queue is empty, the behavior is undefined.  If multiple elements in the
   * queue are tied for the minimum element, returns a reference to the lowest
   * (eldest) of them.
   */
  const T& min() const;

  /**
   * bool   empty() const;
   * size_t size()  const;
   * Usage: while (!myQueue.empty()) { ... }
   *        if (myQueue.size() == 3) { ... }
   * -------------------------------------------------------------------------
   * Returns whether the queue is empty and its size, respectively.
   */
  bool   empty() const;
  size_t size() const;
private:
  /* These stacks are marked mutable so that we can move elements across them
   * when we need to look at the top element.
   */
  mutable min_stack<T, Comparator> mNew, mOld;

  /* The comparator used to rank elements. */
  Comparator mComp;

  /* A utility function to move the contents of the new stack into the old
   * stack if the old stack is empty.
   */
  void moveIfNecessary() const;
};

/* * * * * Implementation Below This Point * * * * */

/* Constructor accepts a comparator and forwards it to both of the nested
 * stacks.
 */
template <typename T, typename Comparator>
min_queue<T, Comparator>::min_queue(Comparator c) 
  : mNew(c), mOld(c), mComp(c) {
  // Handled in initializer list
}

/* To retrieve the size of the queue and whether it's empty, we query the
 * underlying stacks.
 */
template <typename T, typename Comparator>
size_t min_queue<T, Comparator>::size() const {
  return mNew.size() + mOld.size();
}
template <typename T, typename Comparator>
bool min_queue<T, Comparator>::empty() const {
  return mNew.empty() && mOld.empty();
}

/* To retrieve the front element of the queue, we ensure that the old stack is
 * not empty, then look at its top element.
 */
template <typename T, typename Comparator>
const T& min_queue<T, Comparator>::front() const {
  moveIfNecessary();
  return mOld.top();
}

/* To dequeue from the queue, we ensure that the old stack is not empty, then
 * remove its first element.
 */
template <typename T, typename Comparator>
void min_queue<T, Comparator>::dequeue() {
  moveIfNecessary();
  mOld.pop();
}

/* To enqueue a new element, we just put it atop the new stack. */
template <typename T, typename Comparator>
void min_queue<T, Comparator>::enqueue(const T& elem) {
  mNew.push(elem);
}

/* To find the minimum element, we may need to look at the elements of both
 * the stacks.
 */
template <typename T, typename Comparator>
const T& min_queue<T, Comparator>::min() const {
  /* Case 1: If both queues are non-empty, compare them and return whichever
   * is smaller.
   */
  if (!mNew.empty() && !mOld.empty()) {
    /* Compare the two and return whichever is smaller. */
    return mComp(mOld.min(), mNew.min()) ? mOld.min() : mNew.min();
  }
  else if (!mNew.empty()) {
    /* Case two: Only the new queue is nonempty.  Returns its minimum. */
    return mNew.min();
  }
  else {
    /* Case three: Only the old queue is nonempty.  Return its minimum.  Note
     * that it's also possible that the whole queue is empty, which then leads
     * to undefined behavior.
     */
    return mOld.min();
  }
}

/* Logic to actually move the elements from the old stack to the new stack if
 * necessary.
 */
template <typename T, typename Comparator>
void min_queue<T, Comparator>::moveIfNecessary() const {
  /* If the old stack isn't empty, don't move anything. */
  if (!mOld.empty()) return;

  /* While there are elements in the new stack, keep moving them over to the
   * old stack.
   */
  while (!mNew.empty()) {
    mOld.push(mNew.top());
    mNew.pop();
  }
}

} // namespace util.

#endif