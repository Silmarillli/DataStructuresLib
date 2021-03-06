#ifndef BoundedPQueue_Included
#define BoundedPQueue_Included

#include <map>        // For std::multimap
#include <limits>     // For std::numeric_limits
#include <functional> // For std::less
#include <stdlib.h>   // For size_t

template <typename T, typename Comparator = std::less<T> > 
class BoundedPQueue {
public:
  /* Constructor: BoundedPQueue(size_t maxSize);
   * Usage: BoundedPQueue<int> bpq(15);
   * --------------------------------------------------
   * Constructs a new, empty BoundedPQueue with
   * maximum size equal to the constructor argument.
   */
  explicit BoundedPQueue(size_t maxSize, Comparator comp = Comparator());

  /* void enqueue(const T& value, double priority);
   * Usage: bpq.enqueue("Hi!", 2.71828);
   * --------------------------------------------------
   * Enqueues a new element into the BoundedPQueue with
   * the specified priority.  If this overflows the maximum
   * size of the queue, the element with the highest
   * priority will be deleted from the queue.  Note that
   * this might be the element that was just added.
   */
  void enqueue(const T& value, double priority);

  /* T dequeueMin();
   * Usage: int val = bpq.dequeueMin();
   * --------------------------------------------------
   * Returns the element from the BoundedPQueue with the
   * smallest priority value, then removes that element
   * from the queue.
   */
  T dequeueMin();

  /* size_t size() const;
   * bool  empty() const;
   * Usage: while (!bpq.empty()) { ... }
   * --------------------------------------------------
   * Returns the number of elements in the queue and whether
   * the queue is empty, respectively.
   */
  size_t size() const;
  bool empty() const;
  
  /* size_t maxSize() const;
   * Usage: size_t queueSize = bpq.maxSize();
   * --------------------------------------------------
   * Returns the maximum number of elements that can be
   * stored in the queue.
   */
  size_t maxSize() const;
  
  /* double best() const;
   * double worst() const;
   * Usage: double highestPriority = bpq.worst();
   * --------------------------------------------------
   * best() returns the smallest priority of an element
   * stored in the container (i.e. the priority of the
   * element that will be dequeued first using dequeueMin).
   * worst() returns the largest priority of an element
   * stored in the container.  If an element is enqueued
   * with a priority above this value, it will automatically
   * be deleted from the queue.  Both functions return
   * numeric_limits<double>::infinity() if the queue is
   * empty.
   */
  double best()  const;
  double worst() const;

private:
  /* This class is layered on top of a multimap mapping from priorities
   * to elements with those priorities.
   */
  std::multimap<double, T, Comparator> elems;
  size_t maximumSize;
};

/*************** Implementation Starts Here *****************/

/* Constructor accepts and stores the maximum size.  It also forwards the
 * comparator to the backing multimap.
 */
template <typename T, typename Comparator> 
BoundedPQueue<T, Comparator>::BoundedPQueue(size_t maxSize, Comparator comp) :
  elems(comp) {
  maximumSize = maxSize;
}

/* enqueue adds the element to the map, then deletes the last element of the
 * map if there size exceeds the maximum size.
 */
template <typename T, typename Comparator> 
void BoundedPQueue<T, Comparator>::enqueue(const T& value, double priority) {
  /* Optimization: If this isn't going to be added, don't add it. */
  if (size() == maxSize() && elems.key_comp()(worst(), priority))
    return;
  
  /* Add the element to the collection. */
  elems.insert(make_pair(priority, value));

  /* If there are too many elements in the queue, drop off the last one. */
  if (size() > maxSize()) {
    typename std::multimap<double, T, Comparator>::iterator last = elems.end();
    --last; // Now points to highest-priority element
    elems.erase(last);
  }
}

/* dequeueMin copies the lowest element of the map (the one pointed at by
 * begin()) and then removes it.
 */
template <typename T, typename Comparator> 
T BoundedPQueue<T, Comparator>::dequeueMin() {
  /* Copy the best value. */
  T result = elems.begin()->second;
  
  /* Remove it from the map. */
  elems.erase(elems.begin());
  
  return result;
}

/* size() and empty() call directly down to the underlying map. */
template <typename T, typename Comparator> 
size_t BoundedPQueue<T, Comparator>::size() const {
  return elems.size();
}
template <typename T, typename Comparator> 
bool BoundedPQueue<T, Comparator>::empty() const {
  return elems.empty();
}

/* maxSize just returns the appropriate data member. */
template <typename T, typename Comparator> 
size_t BoundedPQueue<T, Comparator>::maxSize() const {
  return maximumSize;
}

/* The best() and worst() functions check if the queue is empty,
 * and if so return infinity.
 */
template <typename T, typename Comparator> 
double BoundedPQueue<T, Comparator>::best() const {
  return empty()? std::numeric_limits<double>::infinity() : 
    elems.begin()->first;
}
template <typename T, typename Comparator> 
double BoundedPQueue<T, Comparator>::worst() const{
  return empty()? std::numeric_limits<double>::infinity() : 
    elems.rbegin()->first;
}

#endif