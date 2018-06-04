#ifndef MinStack_Included
#define MinStack_Included

#include <deque>
#include <functional> // For std::less
#include <utility>    // For std::pair


namespace util {
/**
 * Class: min_stack<T, Comparator = std::less<T>>
 * Usage: min_stack<int> myMinStack;
 * ----------------------------------------------------------------------------
 * A class representing a LIFO stack supporting constant-time push, pop, and
 * find-min.  The comparator may be customized.
 */
template <typename T, 
          typename Comparator = std::less<T> > 
class min_stack {
public:
  /**
   * Constructor: min_stack(Comparator = Comparator());
   * Usage: min_stack<T> myStack;
   *        min_stack<T, C> myStack(myComparator);
   * --------------------------------------------------------------------------
   * Constructs a new min_stack that uses the specified comparator to make
   * comparisons.
   */
  explicit min_stack(Comparator = Comparator());

  /**
   * void push(const T& val);
   * Usage: myStack.push(137);
   * --------------------------------------------------------------------------
   * Pushes a new element atop the stack.
   */
  void push(const T& val);

  /**
   * void pop();
   * Usage: myStack.pop();
   * --------------------------------------------------------------------------
   * Pops the top element off the stack.  If the stack is empty, the behavior
   * is undefined.
   */
  void pop();

  /**
   * const T& top() const;
   * Usage: cout << myStack.top() << endl;
   * --------------------------------------------------------------------------
   * Returns an immutable view of the top element of the stack.  If the stack
   * is empty, the behavior is undefined.
   */
  const T& top() const;

  /**
   * const T& min() const;
   * Usage: cout << myStack.min() << endl;
   * --------------------------------------------------------------------------
   * Returns an immutable view of the minimum element of the stack.  If the
   * stack is empty, the behavior is undefined.  If multiple elements in the
   * stack are tied for the minimum element, returns a reference to the lowest
   * (eldest) of them.
   */
  const T& min() const;

  /**
   * bool   empty() const;
   * size_t size()  const;
   * Usage: while (!myStack.empty()) { ... }
   *        if (myStack.size() == 3) { ... }
   * --------------------------------------------------------------------------
   * Returns whether the stack is empty and its size, respectively.
   */
  bool   empty() const;
  size_t size() const;

private:
  /* The actual stack.  Each entry is a pair of an element and the index of the
   * minimum element at or below this point.
   */
  std::deque< std::pair<T, size_t> > mStack;

  /* The comparator used to determine what the smallest element is. */
  Comparator mComp;
};

/* * * * * Implementation Below This Point * * * * */

/* Constructor stores the comparator for future use. */
template <typename T, typename Comparator>
min_stack<T, Comparator>::min_stack(Comparator c) 
  : mStack(), mComp(c) {
  // Handled in initialization list
}

/* Size and empty queries forward directly to the underlying deque. */
template <typename T, typename Comparator>
size_t min_stack<T, Comparator>::size() const {
  return mStack.size();
}
template <typename T, typename Comparator>
bool min_stack<T, Comparator>::empty() const {
  return mStack.empty();
}

/* Returning the top element looks at the back of the deque. */
template <typename T, typename Comparator>
const T& min_stack<T, Comparator>::top() const {
  return mStack.back().first;
}

/* Returning the min element looks at the element in the deque that is the
 * smallest so far.  It's held at the index at the top of the stack. */
template <typename T, typename Comparator>
const T& min_stack<T, Comparator>::min() const {
  return mStack[mStack.back().second].first;
}

/* Inserting a new element adds it to the stack and updates the minimum element
 * if the new element is smaller.
 */
template <typename T, typename Comparator>
void min_stack<T, Comparator>::push(const T& elem) {
  /* If the stack is empty, add the new element and mark that it's the smallest
   * so far.
   */
  if (empty()) {
    mStack.push_back(std::make_pair(elem, 0));
  }
  else {
    /* Otherwise, find the index of the smallest element and insert the new
     * element annotated with that index.
     */
    size_t smallestIndex = mStack.back().second;

    /* If this new element is smaller, the smallest element will now be at the
     * back of the list.
     */
    if (mComp(elem, min()))
      smallestIndex = mStack.size();

    /* Add the element in. */
    mStack.push_back(std::make_pair(elem, smallestIndex));
  }
}

/* Popping an element off the stack just removes the top pair from the
 * deque.
 */
template <typename T, typename Comparator>
void min_stack<T, Comparator>::pop() {
  mStack.pop_back();
}

} // namespace util

#endif
