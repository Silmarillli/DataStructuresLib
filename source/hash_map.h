#ifndef HASH_MAP_H_
#define HASH_MAP_H_

#include <cstddef>
#include <vector>
#include <list>
#include <iterator> 
#include <string>
#include <initializer_list>
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <utility>

namespace util {

	// A default hash object
	template <typename T>
	class hash
	{
	public:
		size_t operator()(const T& key) const;
	};

	// A hash specialization for strings
	template <>
	class hash<std::string>
	{
	public:
		size_t operator()(const std::string& key) const;
	};

	
	// const_hash_map_iterator class definition
	template <typename HashMap>
	class const_hash_map_iterator
	{
		// The hash_map class needs access to all members of the const_hash_map_iterator
		friend HashMap;

	public:
		using value_type = typename HashMap::value_type;
		using difference_type = ptrdiff_t;
		using iterator_category = std::bidirectional_iterator_tag;
		using pointer = value_type*;
		using reference = value_type&;
		using list_iterator_type = typename HashMap::ListType::const_iterator;

		// Bidirectional iterators must supply a default constructor.
		// Using an iterator constructed with the default constructor
		// is undefined, so it doesn't matter how it's initialized.
		const_hash_map_iterator() = default;

		const_hash_map_iterator(size_t bucket, list_iterator_type listIt, const HashMap* hashmap);

		// Don't need to define a copy constructor or operator= because the
		// default behavior is what we want.

		// Don't need destructor because the default behavior
		// (not deleting mHashmap) is what we want!

		const value_type& operator*() const;

		// Return type must be something to which -> can be applied.
		// Return a pointer to a pair<const Key, T>, to which the compiler
		// will apply -> again.
		const value_type* operator->() const;

		const_hash_map_iterator<HashMap>& operator++();
		const_hash_map_iterator<HashMap> operator++(int);

		const_hash_map_iterator<HashMap>& operator--();
		const_hash_map_iterator<HashMap> operator--(int);

		// The following are ok as member functions because we don't
		// support comparisons of different types to this one.
		bool operator==(const const_hash_map_iterator<HashMap>& rhs) const;
		bool operator!=(const const_hash_map_iterator<HashMap>& rhs) const;

	protected:
		size_t mBucketIndex = 0;
		list_iterator_type mListIterator;
		const HashMap* mHashmap = nullptr;

		// Helper methods for operator++ and operator--
		void increment();
		void decrement();
	};

	template <typename HashMap>
	class hash_map_iterator : public const_hash_map_iterator<HashMap>
	{
		// The hash_map class needs access to all members of the hash_map_iterator
		friend HashMap;

	public:
		using value_type = typename const_hash_map_iterator<HashMap>::value_type;
		using difference_type = ptrdiff_t;
		using iterator_category = std::bidirectional_iterator_tag;
		using pointer = value_type*;
		using reference = value_type&;
		using list_iterator_type = typename HashMap::ListType::iterator;

		hash_map_iterator() = default;
		hash_map_iterator(size_t bucket, list_iterator_type listIt, HashMap* hashmap);
		
		value_type& operator*();
		value_type* operator->();

		hash_map_iterator<HashMap>& operator++();
		hash_map_iterator<HashMap> operator++(int);

		hash_map_iterator<HashMap>& operator--();
		hash_map_iterator<HashMap> operator--(int);
	};




	template <typename Key, typename T,
		typename KeyEqual = std::equal_to<>,
		typename Hash = hash<Key>>
	class hash_map
	{
	public:
		using key_type = Key;
		using mapped_type = T;
		using value_type = std::pair<const Key, T>;
		using hasher = Hash;
		using key_equal = KeyEqual;
		using reference = value_type&;
		using const_reference = const value_type&;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using hash_map_type = hash_map<Key, T, KeyEqual, Hash>;
		using iterator = hash_map_iterator<hash_map_type>;
		using const_iterator = const_hash_map_iterator<hash_map_type>;

	private:
		using ListType = std::list<value_type>;
	public:
		using local_iterator = typename ListType::iterator;
		using const_local_iterator = typename ListType::const_iterator;

		// The iterator classes need access to all members of the hash_map
		friend class hash_map_iterator<hash_map_type>;
		friend class const_hash_map_iterator<hash_map_type>;

		// Virtual destructor
		virtual ~hash_map() = default;

		// Throws invalid_argument if the number of buckets is illegal.
		explicit hash_map(const KeyEqual& equal = KeyEqual(), size_type numBuckets = 101, const Hash& hash = Hash());

		// Throws invalid_argument if the number of buckets is illegal.
		template <typename InputIterator>
		hash_map(InputIterator first, InputIterator last, const KeyEqual& equal = KeyEqual(),
			size_type numBuckets = 101, const Hash& hash = Hash());

		// Initializer list constructor
		// Throws invalid_argument if the number of buckets is illegal. 
		explicit hash_map(std::initializer_list<value_type> il, const KeyEqual& equal = KeyEqual(),
			size_type numBuckets = 101, const Hash& hash = Hash());

		// Copy constructor
		hash_map(const hash_map_type& src) = default;
		// Move constructor
		hash_map(hash_map_type&& src) noexcept = default;

		// Copy assignment operator
		hash_map_type& operator=(const hash_map_type& rhs);
		// Move assignment operator
		hash_map_type& operator=(hash_map_type&& rhs) noexcept;
		// Initializer list assignment operator
		hash_map_type& operator=(std::initializer_list<value_type> il);

		// Iterator methods
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;

		// Size methods
		bool empty() const;
		size_type size() const;
		size_type max_size() const;

		// Element insert methods
		T& operator[](const key_type& k);
		std::pair<iterator, bool> insert(const value_type& x);
		iterator insert(const_iterator hint, const value_type& x);
		template <typename InputIterator>
		void insert(InputIterator first, InputIterator last);
		void insert(std::initializer_list<value_type> il);

		// Element delete methods
		size_type erase(const key_type& k);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		// Other modifying utilities
		void swap(hash_map_type& other) noexcept;
		void clear() noexcept;

		// Access methods for Standard Library conformity
		key_equal key_eq() const;
		hasher hash_function() const;

		// Lookup methods
		iterator find(const key_type& k);
		const_iterator find(const key_type& k) const;
		std::pair<iterator, iterator> equal_range(const key_type& k);
		std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const;

		size_type count(const key_type& k) const;

		size_type bucket_count() const;
		size_type max_bucket_count() const;
		size_type bucket(const Key& k) const;
		size_type bucket_size(size_type n) const;
		local_iterator begin(size_type n);
		const_local_iterator begin(size_type n) const;
		const_local_iterator cbegin(size_type n) const;
		local_iterator end(size_type n);
		const_local_iterator end(size_type n) const;
		const_local_iterator cend(size_type n) const;

	private:
		// Returns a pair containing an iterator to the found element with
		// a given key, and the index of that element's bucket.
		std::pair<typename ListType::iterator, size_t> findElement(const key_type& k);

		std::vector<ListType> mBuckets;
		size_type mSize = 0;
		KeyEqual mEqual;
		Hash mHash;
	};


	// Calculate a hash by treating the key as a sequence
	// of bytes and summing the ASCII values of the bytes.
	template <typename T>
	size_t hash<T>::operator()(const T& key) const
	{
		size_t bytes = sizeof(key);
		size_t sum = 0;
		for (size_t i = 0; i < bytes; ++i) {
			unsigned char b = *(reinterpret_cast<const unsigned char*>(&key) + i);
			sum += b;
		}
		return sum;
	}




	// Calculate a hash by summing the ASCII values of all characters.
	size_t hash<std::string>::operator()(const std::string& key) const
	{
		size_t sum = 0;
		for (auto c : key) {
			sum += static_cast<unsigned char>(c);
		}
		return sum;
	}




	template<typename HashMap>
	const_hash_map_iterator<HashMap>::const_hash_map_iterator(size_t bucket, list_iterator_type listIt, const HashMap* hashmap)
		: mBucketIndex(bucket), mListIterator(listIt), mHashmap(hashmap)
	{
	}

	// Return a reference to the actual element.
	template<typename HashMap>
	const typename const_hash_map_iterator<HashMap>::value_type&
		const_hash_map_iterator<HashMap>::operator*() const
	{
		return *mListIterator;
	}

	// Return a pointer to the actual element, so the compiler can
	// apply -> to it to access the actual desired field.
	template<typename HashMap>
	const typename const_hash_map_iterator<HashMap>::value_type*
		const_hash_map_iterator<HashMap>::operator->() const
	{
		return &(*mListIterator);
	}

	// Defer the details to the increment() helper.
	template<typename HashMap>
	const_hash_map_iterator<HashMap>& const_hash_map_iterator<HashMap>::operator++()
	{
		increment();
		return *this;
	}

	// Defer the details to the increment() helper.
	template<typename HashMap>
	const_hash_map_iterator<HashMap> const_hash_map_iterator<HashMap>::operator++(int)
	{
		auto oldIt = *this;
		increment();
		return oldIt;
	}

	// Defer the details to the decrement() helper.
	template<typename HashMap>
	const_hash_map_iterator<HashMap>& const_hash_map_iterator<HashMap>::operator--()
	{
		decrement();
		return *this;
	}

	// Defer the details to the decrement() helper.
	template<typename HashMap>
	const_hash_map_iterator<HashMap> const_hash_map_iterator<HashMap>::operator--(int)
	{
		auto oldIt = *this;
		decrement();
		return oldIt;
	}

	template<typename HashMap>
	bool const_hash_map_iterator<HashMap>::operator==(const const_hash_map_iterator<HashMap>& rhs) const
	{
		// All fields, including the hash_map to which the iterators refer,
		// must be equal.
		return (mHashmap == rhs.mHashmap &&
			mBucketIndex == rhs.mBucketIndex &&
			mListIterator == rhs.mListIterator);
	}

	template<typename HashMap>
	bool const_hash_map_iterator<HashMap>::operator!=(const const_hash_map_iterator<HashMap>& rhs) const
	{
		return !(*this == rhs);
	}

	// Behavior is undefined if mListIterator already refers to the past-the-end
	// element, or is otherwise invalid.
	template<typename HashMap>
	void const_hash_map_iterator<HashMap>::increment()
	{
		// mListIterator is an iterator into a single bucket. Increment it.
		++mListIterator;

		// If we're at the end of the current bucket,
		// find the next bucket with elements.
		auto& buckets = mHashmap->mBuckets;
		if (mListIterator == end(buckets[mBucketIndex])) {
			for (size_t i = mBucketIndex + 1; i < buckets.size(); i++) {
				if (!buckets[i].empty()) {
					// We found a non-empty bucket.
					// Make mListIterator refer to the first element in it.
					mListIterator = begin(buckets[i]);
					mBucketIndex = i;
					return;
				}
			}
			// No more non-empty buckets. Set mListIterator to refer to the
			// end iterator of the last list.
			mBucketIndex = buckets.size() - 1;
			mListIterator = end(buckets[mBucketIndex]);
		}
	}

	// Behavior is undefined if mListIterator already refers to the first
	// element, or is otherwise invalid.
	template<typename HashMap>
	void const_hash_map_iterator<HashMap>::decrement()
	{
		// mListIterator is an iterator into a single bucket.
		// If it's at the beginning of the current bucket, don't decrement it.
		// Instead, try to find a non-empty bucket before the current one.
		auto& buckets = mHashmap->mBuckets;
		if (mListIterator == begin(buckets[mBucketIndex])) {
			for (int i = mBucketIndex - 1; i >= 0; --i) {
				if (!buckets[i].empty()) {
					mListIterator = --end(buckets[i]);
					mBucketIndex = i;
					return;
				}
			}
			// No more non-empty buckets. This is an invalid decrement.
			// Set mListIterator to refer to the end iterator of the last list.
			mBucketIndex = buckets.size() - 1;
			mListIterator = end(buckets[mBucketIndex]);
		} else {
			// We're not at the beginning of the bucket, so just move down.
			--mListIterator;
		}
	}




	template<typename HashMap>
	hash_map_iterator<HashMap>::hash_map_iterator(size_t bucket, list_iterator_type listIt, HashMap* hashmap)
		: const_hash_map_iterator<HashMap>(bucket, listIt, hashmap)
	{
	}

	// Return a reference to the actual element.
	template<typename HashMap>
	typename hash_map_iterator<HashMap>::value_type&
		hash_map_iterator<HashMap>::operator*()
	{
		return const_cast<value_type&>(*this->mListIterator);
	}

	// Return a pointer to the actual element, so the compiler can
	// apply -> to it to access the actual desired field.
	template<typename HashMap>
	typename hash_map_iterator<HashMap>::value_type*
		hash_map_iterator<HashMap>::operator->()
	{
		return const_cast<value_type*>(&(*this->mListIterator));
	}

	// Defer the details to the increment() helper in the base class.
	template<typename HashMap>
	hash_map_iterator<HashMap>& hash_map_iterator<HashMap>::operator++()
	{
		this->increment();
		return *this;
	}

	// Defer the details to the increment() helper in the base class.
	template<typename HashMap>
	hash_map_iterator<HashMap> hash_map_iterator<HashMap>::operator++(int)
	{
		auto oldIt = *this;
		this->increment();
		return oldIt;
	}

	// Defer the details to the decrement() helper in the base class.
	template<typename HashMap>
	hash_map_iterator<HashMap>& hash_map_iterator<HashMap>::operator--()
	{
		this->decrement();
		return *this;
	}

	// Defer the details to the decrement() helper in the base class.
	template<typename HashMap>
	hash_map_iterator<HashMap> hash_map_iterator<HashMap>::operator--(int)
	{
		auto oldIt = *this;
		this->decrement();
		return oldIt;
	}




	template <typename Key, typename T, typename KeyEqual, typename Hash>
	void swap(hash_map<Key, T, KeyEqual, Hash>& first, hash_map<Key, T, KeyEqual, Hash>& second) noexcept
	{
		first.swap(second);
	}




	// Resize mBuckets with the number of buckets.
	template <typename Key, typename T, typename KeyEqual, typename Hash>
	hash_map<Key, T, KeyEqual, Hash>::hash_map(const KeyEqual& equal, size_type numBuckets, const Hash& hash)
		: mBuckets(numBuckets), mEqual(equal), mHash(hash)
	{
		if (numBuckets == 0) {
			throw std::invalid_argument("Number of buckets must be positive");
		}
	}

	// Make a call to insert() to actually insert the elements.
	template <typename Key, typename T, typename KeyEqual, typename Hash>
	template <typename InputIterator>
	hash_map<Key, T, KeyEqual, Hash>::hash_map(InputIterator first, InputIterator last, const KeyEqual& equal, size_type numBuckets, const Hash& hash)
		: hash_map(equal, numBuckets, hash)
	{
		insert(first, last);
	}

	// Initializer list constructor
	template <typename Key, typename T, typename KeyEqual, typename Hash>
	hash_map<Key, T, KeyEqual, Hash>::hash_map(std::initializer_list<value_type> il, const KeyEqual& equal, size_type numBuckets, const Hash& hash)
		: hash_map(equal, numBuckets, hash)
	{
		insert(std::begin(il), std::end(il));
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	hash_map<Key, T, KeyEqual, Hash>&
		hash_map<Key, T, KeyEqual, Hash>::operator=(const hash_map_type& rhs)
	{
		// check for self-assignment
		if (this == &rhs) {
			return *this;
		}

		// Copy-and-swap idiom
		auto copy = rhs;  // Do all the work in a temporary instance
		swap(copy);       // Commit the work with only non-throwing operations
		return *this;
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	hash_map<Key, T, KeyEqual, Hash>&
		hash_map<Key, T, KeyEqual, Hash>::operator=(hash_map_type&& rhs) noexcept
	{
		swap(rhs);
		return *this;
	}

	// Initializer list assignment operator
	template <typename Key, typename T, typename KeyEqual, typename Hash>
	hash_map<Key, T, KeyEqual, Hash>&
		hash_map<Key, T, KeyEqual, Hash>::operator=(std::initializer_list<value_type> il)
	{
		// Do all the work in a temporary instance
		hash_map_type newHashMap(il, mEqual, mBuckets.size(), mHash);
		swap(newHashMap);  // Commit the work with only non-throwing operations
		return *this;
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	std::pair<typename hash_map<Key, T, KeyEqual, Hash>::ListType::iterator, size_t>
		hash_map<Key, T, KeyEqual, Hash>::findElement(const key_type& k)
	{
		// Hash the key to get the bucket.
		size_t bucket = mHash(k) % mBuckets.size();

		// Search for the key in the bucket.
		auto iter = find_if(std::begin(mBuckets[bucket]), std::end(mBuckets[bucket]),
			[this, &k](const auto& element) { return mEqual(element.first, k); });

		// Return a pair of the iterator and the bucket index.
		return std::make_pair(iter, bucket);
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::iterator
		hash_map<Key, T, KeyEqual, Hash>::find(const key_type& k)
	{
		// Use the findElement() helper, and C++17 structured bindings.
		auto[it, bucket] = findElement(k);
		if (it == std::end(mBuckets[bucket])) {
			// Element not found -- return the end iterator.
			return end();
		}
		// Element found -- convert the bucket/iterator to a hash_map_iterator.
		return hash_map_iterator<hash_map_type>(bucket, it, this);
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::const_iterator
		hash_map<Key, T, KeyEqual, Hash>::find(const key_type& k) const
	{
		return const_cast<hash_map_type*>(this)->find(k);
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	std::pair<typename hash_map<Key, T, KeyEqual, Hash>::iterator,
		typename hash_map<Key, T, KeyEqual, Hash>::iterator>
		hash_map<Key, T, KeyEqual, Hash>::equal_range(const key_type& k)
	{
		auto it = find(k);
		return std::make_pair(it, it);
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	std::pair<typename hash_map<Key, T, KeyEqual, Hash>::const_iterator,
		typename hash_map<Key, T, KeyEqual, Hash>::const_iterator>
		hash_map<Key, T, KeyEqual, Hash>::equal_range(const key_type& k) const
	{
		auto it = find(k);
		return std::make_pair(it, it);
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::size_type
		hash_map<Key, T, KeyEqual, Hash>::count(const key_type& k) const
	{
		// There are either 1 or 0 elements matching key k.
		// If we can find a match, return 1, otherwise return 0.
		if (find(k) == end()) {
			return 0;
		} else {
			return 1;
		}
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	T& hash_map<Key, T, KeyEqual, Hash>::operator[] (const key_type& k)
	{
		// It's a bit cryptic, but it basically attempts to insert
		// a new key/value pair of k and a zero-initialized value. Regardless
		// of whether the insert succeeds or fails, insert() returns a pair of
		// an iterator/bool. The iterator refers to a key/value pair, the
		// second element of which is the value we want to return.
		return ((insert(std::make_pair(k, T()))).first)->second;
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	std::pair<typename hash_map<Key, T, KeyEqual, Hash>::iterator, bool>
		hash_map<Key, T, KeyEqual, Hash>::insert(const value_type& x)
	{
		// Try to find the element.
		auto[it, bucket] = findElement(x.first);
		bool inserted = false;
		if (it == std::end(mBuckets[bucket])) {
			// We didn't find the element, so insert a new one.
			it = mBuckets[bucket].insert(it, x);
			inserted = true;
			mSize++;
		}
		return std::make_pair(hash_map_iterator<hash_map_type>(bucket, it, this), inserted);
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::iterator
		hash_map<Key, T, KeyEqual, Hash>::insert(const_iterator /*hint*/, const value_type& x)
	{
		// Completely ignore position.
		return insert(x).first;
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	template <typename InputIterator>
	void hash_map<Key, T, KeyEqual, Hash>::insert(InputIterator first, InputIterator last)
	{
		// Copy each element in the range by using an insert_iterator adapter.
		// Give begin() as a dummy position -- insert ignores it anyway.
		std::insert_iterator<hash_map_type> inserter(*this, begin());
		std::copy(first, last, inserter);
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	void hash_map<Key, T, KeyEqual, Hash>::insert(std::initializer_list<value_type> il)
	{
		insert(std::begin(il), std::end(il));
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::size_type
		hash_map<Key, T, KeyEqual, Hash>::erase(const key_type& k)
	{
		// First, try to find the element.
		auto[it, bucket] = findElement(k);
		if (it != std::end(mBuckets[bucket])) {
			// The element exists -- erase it.
			mBuckets[bucket].erase(it);
			mSize--;
			return 1;
		}
		else {
			return 0;
		}
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::iterator
		hash_map<Key, T, KeyEqual, Hash>::erase(iterator position)
	{
		iterator next = position;
		++next;

		// Erase the element from its bucket.
		mBuckets[position.mBucketIndex].erase(position.mListIterator);
		mSize--;

		return next;
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::iterator
		hash_map<Key, T, KeyEqual, Hash>::erase(iterator first, iterator last)
	{
		// Erase all the elements in the range.
		for (iterator next = first; next != last;) {
			next = erase(next);
		}

		return last;
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	void hash_map<Key, T, KeyEqual, Hash>::clear() noexcept
	{
		// Call clear on each bucket.
		for (auto& bucket : mBuckets) {
			bucket.clear();
		}
		mSize = 0;
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	bool hash_map<Key, T, KeyEqual, Hash>::empty() const
	{
		return mSize == 0;
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::size_type
		hash_map<Key, T, KeyEqual, Hash>::size() const
	{
		return mSize;
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::size_type
		hash_map<Key, T, KeyEqual, Hash>::max_size() const
	{
		// In the worst case, all the elements hash to the same
		// list, so the max_size is the max_size of a single list.
		// This code assumes that all the lists have the same max_size.
		return mBuckets[0].max_size();
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	void hash_map<Key, T, KeyEqual, Hash>::swap(hash_map_type& other) noexcept
	{
		using std::swap;

		swap(mBuckets, other.mBuckets);
		swap(mSize, other.mSize);
		swap(mEqual, other.mEqual);
		swap(mHash, other.mHash);
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::iterator
		hash_map<Key, T, KeyEqual, Hash>::begin()
	{
		if (mSize == 0) {
			// Special case: there are no elements, so return the end iterator.
			return end();
		}

		// We know there is at least one element. Find the first element.
		for (size_t i = 0; i < mBuckets.size(); ++i) {
			if (!mBuckets[i].empty()) {
				return hash_map_iterator<hash_map_type>(i, std::begin(mBuckets[i]), this);
			}
		}
		// Should never reach here, but if we do, return the end iterator.
		return end();
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::const_iterator
		hash_map<Key, T, KeyEqual, Hash>::begin() const
	{
		// Use const_cast to call the non-const version of begin(). That
		// one returns an iterator which is convertible to a const_iterator.
		return const_cast<hash_map_type*>(this)->begin();
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::const_iterator
		hash_map<Key, T, KeyEqual, Hash>::cbegin() const
	{
		return begin();
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::iterator
		hash_map<Key, T, KeyEqual, Hash>::end()
	{
		// The end iterator is the end iterator of the list of the last bucket.
		size_t bucket = mBuckets.size() - 1;
		return hash_map_iterator<hash_map_type>(bucket, std::end(mBuckets[bucket]), this);
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::const_iterator
		hash_map<Key, T, KeyEqual, Hash>::end() const
	{
		// Use const_cast to call the non-const version of end(). That
		// one returns an iterator which is convertible to a const_iterator.
		return const_cast<hash_map_type*>(this)->end();
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::const_iterator
		hash_map<Key, T, KeyEqual, Hash>::cend() const
	{
		return end();
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::key_equal
		hash_map<Key, T, KeyEqual, Hash>::key_eq() const
	{
		return mEqual;
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::hasher
		hash_map<Key, T, KeyEqual, Hash>::hash_function() const
	{
		return mHash;
	}


	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::size_type
		hash_map<Key, T, KeyEqual, Hash>::bucket_count() const
	{
		return mBuckets.size();
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::size_type
		hash_map<Key, T, KeyEqual, Hash>::max_bucket_count() const
	{
		return mBuckets.max_size();
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::size_type
		hash_map<Key, T, KeyEqual, Hash>::bucket(const Key& k) const
	{
		return const_cast<hash_map_type*>(this)->findElement(k).second;
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::size_type
		hash_map<Key, T, KeyEqual, Hash>::bucket_size(size_type n) const
	{
		return mBuckets[n].size();
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::local_iterator
		hash_map<Key, T, KeyEqual, Hash>::begin(size_type n)
	{
		return mBuckets[n].begin();
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::const_local_iterator
		hash_map<Key, T, KeyEqual, Hash>::begin(size_type n) const
	{
		return mBuckets[n].begin();
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::const_local_iterator
		hash_map<Key, T, KeyEqual, Hash>::cbegin(size_type n) const
	{
		return mBuckets[n].cbegin();
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::local_iterator
		hash_map<Key, T, KeyEqual, Hash>::end(size_type n)
	{
		return mBuckets[n].end();
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::const_local_iterator
		hash_map<Key, T, KeyEqual, Hash>::end(size_type n) const
	{
		return mBuckets[n].end();
	}

	template <typename Key, typename T, typename KeyEqual, typename Hash>
	typename hash_map<Key, T, KeyEqual, Hash>::const_local_iterator
		hash_map<Key, T, KeyEqual, Hash>::cend(size_type n) const
	{
		return mBuckets[n].cend();
	}

} //namespace util

#endif HASH_MAP_H_
