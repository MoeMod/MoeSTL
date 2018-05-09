#pragma once

#include <stdexcept>
using std::out_of_range;
#include <iterator>
using std::reverse_iterator;

using std::integral_constant;

#include "algorithm/fill.h"
#include "extra/pointer_iterator.h"

namespace MoeSTL
{
template<
	class T,
	std::size_t N
> struct array
{
public:
	using value_type = T;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = T & ;
	using const_reference = const T &;
	using pointer = T * ;
	using const_pointer = const T *;

	using iterator = pointer_iterator<T>;
	using const_iterator = const_pointer_iterator<T>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	reference at(size_type pos)
	{
		if (pos >= N)
			throw out_of_range();
		return (*this)[pos];
	}

	const_reference at(size_type pos) const
	{
		if (pos >= N)
			throw out_of_range();
		return (*this)[pos];
	}

	reference operator[](size_type pos)
	{
		return m_pData[pos];
	}
	const_reference operator[](size_type pos) const
	{
		return const_cast<const_pointer>(m_pData)[pos];
	}

	reference front()
	{
		return (*this)[0];
	}
	const_reference front() const
	{
		return (*this)[0];
	}
	reference back()
	{
		return (*this)[N - 1];
	}
	const_reference back() const
	{
		return (*this)[N - 1];
	}

	T* data() noexcept
	{
		return m_pData;
	}
	const T* data() const noexcept
	{
		return const_cast<const_pointer>(m_pData);
	}

	iterator begin() noexcept
	{
		return iterator(data());
	}
	iterator end() noexcept
	{
		return iterator(data() + size());
	}
	const_iterator begin() const noexcept
	{
		return cbegin();
	}
	const_iterator end() const noexcept
	{
		return cend();
	}
	const_iterator cbegin() const noexcept
	{
		return const_iterator(data());
	}
	const_iterator cend() const noexcept
	{
		return const_iterator(data() + size());
	}
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}
	reverse_iterator rend() noexcept
	{
		return reverse_iterator(begin());
	}
	const_reverse_iterator rbegin() const noexcept
	{
		return crbegin();
	}
	const_reverse_iterator rend() const noexcept
	{
		return crend();
	}
	const_reverse_iterator crbegin() const noexcept
	{
		return reverse_iterator(cend());
	}
	const_reverse_iterator crend() const noexcept
	{
		return reverse_iterator(cbegin());
	}

	bool empty() const noexcept
	{
		return false;
	}

	size_type size() const noexcept
	{
		return N;
	}

	constexpr size_type max_size()  noexcept
	{
		return -1;
	}

	void fill(const T& value)
	{
		return fill_n(begin(), N, value);
	}
	void swap(array& other) noexcept(noexcept(swap(std::declval<T&>(), std::declval<T&>())))
	{
		return swap(m_pData, other.m_pData);
	}

	T m_pData[N];
};

/*
template< class T, size_t N >
class tuple_size< array<T, N> > :
	public integral_constant<size_t, N>
{ };
*/
template<std::size_t I, class T>
struct tuple_element;

template<std::size_t I, class T, std::size_t N>
struct tuple_element<I, std::array<T, N> >
{
	using type = T;
};

template< class T, std::size_t N >
void swap(array<T, N>& lhs,
	array<T, N>& rhs)
{
	return lhs.swap(rhs);
}

}