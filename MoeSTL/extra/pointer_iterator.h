#pragma once

#include <iterator>
using std::reverse_iterator;

namespace MoeSTL
{

template<class T>
class const_pointer_iterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = const T;
	using difference_type = ptrdiff_t;
	using pointer = value_type * ;
	using reference = value_type & ;

	explicit const_pointer_iterator(pointer p) : ptr(p) {}
	const_pointer_iterator& operator++() { return ++ptr, *this; }
	const_pointer_iterator operator++(int) { return const_pointer_iterator(ptr++); }
	const_pointer_iterator& operator--() { return --ptr, *this; }
	const_pointer_iterator operator--(int) { return const_pointer_iterator(ptr--); }
	const_pointer_iterator& operator+=(int n) { return ptr += n, *this; }
	const_pointer_iterator& operator-=(int n) { return ptr -= n, *this; }
	const_pointer_iterator operator+(int n) { return const_pointer_iterator(ptr + n); }
	friend const_pointer_iterator operator+(int n, const const_pointer_iterator &iter) { return iter + n; }
	const_pointer_iterator operator-(int n) { return const_pointer_iterator(ptr - n); }
	difference_type operator-(const const_pointer_iterator & other) const { return ptr - other.ptr; }

	bool operator==(const_pointer_iterator other) const { return ptr == other.ptr; }
	bool operator!=(const_pointer_iterator other) const { return !(*this == other); }
	bool operator<(const_pointer_iterator other) const { return ptr < other.ptr; }
	bool operator<=(const_pointer_iterator other) const { return ptr <= other.ptr; }
	bool operator>(const_pointer_iterator other) const { return ptr > other.ptr; }
	bool operator>=(const_pointer_iterator other) const { return ptr >= other.ptr; }

	reference operator*() { return *ptr; }
	pointer operator->() { return ptr; }

private:
	pointer ptr;
};

template<class T>
class pointer_iterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = ptrdiff_t;
	using pointer = value_type * ;
	using reference = value_type & ;

	explicit pointer_iterator(pointer p) : ptr(p) {}
	pointer_iterator& operator++() { return ++ptr, *this; }
	pointer_iterator operator++(int) { return pointer_iterator(ptr++); }
	pointer_iterator& operator--() { return --ptr, *this; }
	pointer_iterator operator--(int) { return pointer_iterator(ptr--); }
	pointer_iterator& operator+=(int n) { return ptr += n, *this; }
	pointer_iterator& operator-=(int n) { return ptr -= n, *this; }
	pointer_iterator operator+(int n) const { return pointer_iterator(ptr + n); }
	friend pointer_iterator operator+(int n, const pointer_iterator &iter) { return iter + n; }
	pointer_iterator operator-(int n) const { return pointer_iterator(ptr - n); }
	difference_type operator-(const pointer_iterator &other) const { return ptr - other.ptr; }

	bool operator==(pointer_iterator other) const { return ptr == other.ptr; }
	bool operator!=(pointer_iterator other) const { return !(*this == other); }
	bool operator<(pointer_iterator other) const { return ptr < other.ptr; }
	bool operator<=(pointer_iterator other) const { return ptr <= other.ptr; }
	bool operator>(pointer_iterator other) const { return ptr > other.ptr; }
	bool operator>=(pointer_iterator other) const { return ptr >= other.ptr; }

	reference operator*() { return *ptr; }
	pointer operator->() { return ptr; }

	operator const_pointer_iterator<T>() { return const_pointer_iterator<T>(ptr); }
private:
	pointer ptr;
};

}