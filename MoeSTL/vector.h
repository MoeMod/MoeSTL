#pragma once


#include <malloc.h>
#include <assert.h>

#include <initializer_list>
using std::initializer_list;
#include <stdexcept>
using std::out_of_range;
#include <utility>
using std::move;
#include <iterator>
using std::distance;

#include "algorithm.h"

namespace MoeSTL {

template<class T> 
class vector
{
public:
	using value_type = T;
	using allocator_type = void; // TBD
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = T &;
	using const_reference = const T &;
	using pointer = T *;
	using const_pointer = const T *;

	using iterator = pointer;
	using const_iterator = const_pointer;
	using reverse_iterator = pointer;
	using const_reverse_iterator = pointer;

	vector() :m_pData(nullptr), m_iSize(0), m_iCapacity(0) {}

	explicit vector(size_type count)
	{
		if (count > 0)
		{
			m_iCapacity = m_iSize = count;
			m_pData = (T *)malloc(sizeof(T) * count);
			fill_n(m_pData, count, T{});
		}
	}

	vector(size_type count, const T &value) : vector(count)
	{
		fill_n(m_pData, count, value);
	}

	template< class InputIt >
	vector(InputIt first, InputIt last) : vector()
	{
		size_type count = distance(first, last);
		if (count > 0)
		{
			m_iCapacity = m_iSize = count;
			m_pData = (T *)malloc(sizeof(T) * count);
			assert(m_pData != NULL);
			MoeSTL::copy_n(first, m_iCapacity, begin());
		}
	}

	vector(const vector& other) : vector(other.m_iSize)
	{
		m_iSize = other.m_iSize;
		MoeSTL::copy(other.cbegin(), other.cend(), begin());
	}

	void swap(vector &other)
	{
		using MoeSTL::swap;
		swap(m_pData, other.m_pData);
		swap(m_iSize, other.m_iSize);
		swap(m_iCapacity, other.m_iCapacity);
	}
	
	vector(vector&& other) : vector()
	{
		swap((vector &)other);
	}

	vector(std::initializer_list<T> init) : vector(init.size())
	{
		m_iSize = init.size();
		MoeSTL::copy_n(init.begin(), m_iSize, begin());
	}

	~vector()
	{
		clear();
		free(m_pData);
		m_iCapacity = 0;
	}

	vector& operator=(const vector& other)
	{
		reserve(other.size());
		clear();
		m_iSize = other.m_iSize;
		MoeSTL::copy(other.cbegin(), other.cend(), begin());
		return *this;
	}
	vector& operator=(vector&& other)
	{
		clear();
		swap(other);
		return *this;
	}
	vector& operator=(std::initializer_list<T> ilist)
	{
		reserve(ilist.size());
		clear();
		MoeSTL::copy_n(ilist.begin(), ilist.size(), begin());
		return *this;
	}

	void assign(size_type count, const T& value)
	{
		reserve(count);
		clear();
		m_iSize = count;
		fill_n(m_pData, count, value);
	}

	template< class InputIt >
	void assign(InputIt first, InputIt last)
	{
		size_type count = distance(first, last);
		reserve(count);
		clear();
		m_iSize = count;
		MoeSTL::copy(first, last, begin());
	}

	void assign(std::initializer_list<T> ilist)
	{
		*this = ilist;
	}

	reference at(size_type pos)
	{
		if (pos >= m_iSize)
			throw out_of_range();
		return (*this)[pos];
	}

	const_reference at(size_type pos) const
	{
		if (pos >= m_iSize)
			throw out_of_range();
		return (*this)[pos];
	}

	reference operator[](size_type pos)
	{
		return m_pData[pos];
	}
	reference operator[](size_type pos) const
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
		return (*this)[m_iSize - 1];
	}
	const_reference back() const
	{
		return (*this)[m_iSize - 1];
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
		return data();
	}
	iterator end() noexcept
	{
		return data() + size();
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
		return data();
	}
	const_iterator cend() const noexcept
	{
		return data() + size();
	}

	iterator rbegin() noexcept
	{
		return data() + size() - 1;
	}
	iterator rend() noexcept
	{
		return data() - 1;
	}
	const_iterator rbegin() const noexcept
	{
		return crbegin();
	}
	const_iterator rend() const noexcept
	{
		return crend();
	}
	const_iterator crbegin() const noexcept
	{
		return data() + size() - 1;
	}
	const_iterator crend() const noexcept
	{
		return data() - 1;
	}

	bool empty() const noexcept
	{
		return m_iSize == 0;
	}
	size_type size() const noexcept
	{
		return m_iSize;
	}
	size_type max_size() const noexcept
	{
		return -1;
	}

	void reserve(size_type new_cap)
	{
		if (m_iCapacity < new_cap)
		{
			// alloc memory for new_cap, copy all elements to there, free previous space
			swap(vector(new_cap) = *this);
			// and automatically deconstruct previous object(free previous ptr)
		}
	}
	size_type capacity() const noexcept
	{
		return m_iCapacity;
	}

	void shrink_to_fit()
	{
		if (m_iCapacity != m_iSize)
		{
			vector new_vec(*this);
			swap(new_vec);
		}
	}

	void clear()
	{
		for (size_t i = 0; i < m_iSize; ++i)
		{
			m_pData[i].~T();
		}
		m_iSize = 0;
	}

	iterator insert(const_iterator pos, const T& value)
	{
		return insert(pos, 1, value);
	}
	iterator insert(const_iterator pos, T&& value)
	{
		size_t n = distance(cbegin(), pos);
		reserve(size() + 1);
		m_iSize++;

		move_backward(begin() + n, end() - 1, end()); // end isn't in [pos, cend - 1)
		(*this)[n] = value;
		return begin() + n;
	}

	iterator insert(const_iterator pos, size_type count, const T& value)
	{
		size_t n = distance(cbegin(), pos);
		reserve(size() + count);
		m_iSize += count;

		move_backward(begin() + n, end() - count, end()); // pos isn't in [pos + 1, end)
		iterator ret = begin() + n;
		fill_n(ret, count, value);
		return ret;
	}

	template< class InputIt >
	iterator insert(const_iterator pos, InputIt first, InputIt last)
	{
		size_t n = distance(cbegin(), pos);
		auto count = distance(first, last);
		reserve(size() + count);
		m_iSize += count;

		move_backward(begin() + n, end() - count, end()); // pos isn't in [pos + 1, end)
		iterator ret = begin() + n;
		MoeSTL::copy_n(first, count, ret);
		return ret;
	}

	iterator insert(const_iterator pos, std::initializer_list<T> ilist)
	{
		return insert(pos, ilist.begin(), ilist.end());
	}

	void push_back(const T& value)
	{
		reserve(m_iSize + 1);
		++m_iSize;
		back() = value;
	}
	void push_back(T&& value)
	{
		reserve(m_iSize + 1);
		++m_iSize;
		back() = value;
	}
	template< class... Args >
	void emplace_back(Args&&... args)
	{
		reserve(m_iSize + 1);
		++m_iSize;
		back() = T(args...);
	}

	iterator erase(iterator pos)
	{
		MoeSTL::copy(pos + 1, end(), pos); // pos isn't in [pos + 1, end)
		resize(size() - 1);
		return pos;
	}

	iterator erase(iterator first, iterator last)
	{
		MoeSTL::copy(last, end(), first); // first isn't in [last + 1, end)
		resize(size() - distance(first, last));
		return first;
	}

	void pop_back()
	{
		back().~T();
		--m_iSize;
	}

	void resize(size_type count)
	{
		return resize(count, T{});
	}

	void resize(size_type count, const value_type& value)
	{
		if (count < m_iSize)
		{
			for (size_t i = count; i < m_iSize; ++i)
			{
				m_pData[i].~T();
			}
			m_iSize = count;
		}
		else if (count > m_iSize)
		{
			reserve(count);
			fill_n(m_pData + m_iSize, count - m_iSize, value);
			m_iSize = count;
		}
	}

private:
	T * m_pData;
	size_t m_iSize;
	size_t m_iCapacity;
};

template<class T>
void swap(vector<T> &a, vector<T> &b)
{
	return a.swap(b);
}

}