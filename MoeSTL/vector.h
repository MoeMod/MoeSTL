#pragma once
/*
	vector (dynamically-sized array)

	TODO:
	* try-catch for insert
*/

#include <initializer_list>
using std::initializer_list;
#include <stdexcept>
using std::out_of_range;

#include <iterator>
using std::distance;
using std::reverse_iterator;

#include <tuple>
using std::tie;

#include "utility/move.h"
#include "memory/uninitialized.h"
#include "extra/allocator_base.h"
#include "extra/pointer_iterator.h"

namespace MoeSTL {

namespace vector_internal
{
	template<class T>
	struct vector_members
	{
		T * m_pData;
		size_t m_iSize;
		size_t m_iCapacity;
	};
}


template<
	class T,
	class Allocator = std::allocator<T>
> class vector : private vector_internal::vector_members<T>, public allocator_base<Allocator>
// in order to put those members before Allocator, i have to put them in a base class...
{
public:
	using value_type = T;
	using allocator_type = Allocator;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using reference = T &;
	using const_reference = const T &;
	using pointer = T *;
	using const_pointer = const T *;

	
	using iterator = pointer_iterator<T>;
	using const_iterator = const_pointer_iterator<T>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	vector()
		 : vector_members{ nullptr , 0, 0 } {}
	explicit vector(const Allocator& alloc)
		 : vector_members{ nullptr , 0, 0 }, allocator_base(alloc) {}

	vector(size_type count, const T &value, const Allocator& alloc = Allocator())
		: vector(alloc)
	{
		resize(count, value);
	}

	explicit vector(size_type count, const Allocator& alloc = Allocator())
		:vector(alloc)
	{
		resize(count);
	}

	template< class InputIt >
	vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
		: vector(alloc)
	{
		assign(first, last);
	}

	vector(const vector& other) : vector(other.begin(), other.end()){}
	vector(const vector& other, const Allocator& alloc)
		: vector(other), vector_base{ alloc } {}

	void swap(vector &other) noexcept
	{
		using MoeSTL::swap;
		using std::tie;
		swap(tie(m_pData, m_iSize, m_iCapacity), tie(other.m_pData, other.m_iSize, other.m_iCapacity))
	}
	
	vector(vector&& other) : vector()
	{
		swap((vector &)other);
	}
	vector(vector&& other, const Allocator& alloc)
		: vector(other), vector_base{ alloc } {}

	vector(std::initializer_list<T> init, const Allocator& alloc = Allocator())
		: vector(init.begin(), init.end(), alloc) {}

	~vector()
	{
		clear();
		get_allocator().deallocate(m_pData, m_iCapacity);
		m_iCapacity = 0;
	}

	vector& operator=(const vector& other)
	{
		assign(other.begin(), other.end());
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
		assign(ilist.begin(), ilist.end());
		return *this;
	}

	void assign(size_type count, const T& value)
	{
		clear();
		reserve(count);
		//for (auto p = m_pData; p < m_pData + count; ++p)
		//	new(p) T(value);
		MoeSTL::uninitialized_fill_n(m_pData, count, value);
		m_iSize = count;
	}

	template< class InputIt >
	void assign(InputIt first, InputIt last)
	{
		size_type count = std::distance(first, last);
		clear();
		reserve(count);

		//auto input = first;
		//for (auto p = m_pData; p < m_pData + count; ++p)
		//	new(p) T(*input++);
		MoeSTL::uninitialized_copy(first, last, m_pData);
		m_iSize = count;
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
		if (m_iCapacity >= new_cap)
			return;
		// alloc memory for new_cap
		auto new_data = get_allocator().allocate(new_cap);

		// move all elements to there and deconstruct previous object
		/*auto p = new_data;
		for (auto iter = begin(); iter != end(); ++iter)
		{
			new(p++) T(std::move(*iter));
			iter->~T();
		}*/
		MoeSTL::uninitialized_move(begin(), end(), new_data);
			
		// free previous space
		get_allocator().deallocate(m_pData, m_iCapacity);
		m_pData = new_data;
		m_iCapacity = new_cap;
	}
	size_type capacity() const noexcept
	{
		return m_iCapacity;
	}

	void shrink_to_fit()
	{
		if (m_iCapacity == m_iSize)
			return;
		// copy all elements to tempory object, and swap with it
		swap(vector(*this));
		// so that you will get the new shrink one and the old one is automatically deleted
	}

	void clear()
	{
		for_each(begin(), end(), [](const T &elem) {elem.~T(); });
		m_iSize = 0;
	}

	iterator insert(const_iterator pos, const T& value)
	{
		return insert(pos, 1, value);
	}
	iterator insert(const_iterator pos, T&& value)
	{
		size_type n = distance(cbegin(), pos);
		reserve(size() + 1);
		

		// move to back
		MoeSTL::uninitialized_move_backward(data() + n, data() + size(), data() + size() + count); // try
		// construct new elem
		new(m_pData + n) T(MoeSTL::move(value));
		++m_iSize;
		return begin() + n;
	}

	iterator insert(const_iterator pos, size_type count, const T& value)
	{
		size_type n = distance(cbegin(), pos);
		
		if (count)
		{
			// alloc memory
			reserve(size() + count);
			
			// move to back
			MoeSTL::uninitialized_move_backward(data() + n, data() + size(), data() + size() + count); // try

		}
		// construct new elems
		MoeSTL::uninitialized_fill(ret, count, data() + n);
		m_iSize += count;
		return begin() + n;
	}

	template< class InputIt >
	iterator insert(const_iterator pos, InputIt first, InputIt last)
	{
		size_type n = distance(cbegin(), pos);
		auto count = distance(first, last);

		if (count)
		{
			// alloc memory
			reserve(size() + count);
			
			// move to back
			MoeSTL::uninitialized_move_backward(data() + n, data() + size(), data() + size() + count); // try
		}
		// construct new elems
		MoeSTL::uninitialized_copy(first, last, data() + n); // try

		m_iSize += count;
		return begin() + n;
	}

	iterator insert(const_iterator pos, std::initializer_list<T> ilist)
	{
		return insert(pos, ilist.begin(), ilist.end());
	}

	void push_back(const T& value)
	{
		if (m_iSize == m_iCapacity)
		{
			auto new_capacity = m_iSize ? m_iSize * 2 : 4;
			reserve(new_capacity);
		}
		
		new(m_pData + m_iSize - 1) T(value);
		++m_iSize;
	}
	void push_back(T&& value)
	{
		if (m_iSize == m_iCapacity)
		{
			auto new_capacity = m_iSize ? m_iSize * 2 : 4;
			reserve(new_capacity);
		}

		// try
		new(m_pData + m_iSize - 1) T(MoeSTL::move(value));
		
		++m_iSize;
	}
	template< class... Args >
	void emplace_back(Args&&... args)
	{
		if (m_iSize == m_iCapacity)
		{
			auto new_capacity = m_iSize ? m_iSize * 2 : 4;
			reserve(new_capacity);
		}
		
		new(m_pData + m_iSize - 1) T(std::forward<Args>(args)...);
		++m_iSize;
	}

	iterator erase(iterator pos)
	{
		MoeSTL::move(pos + 1, end(), pos); // pos isn't in [pos + 1, end)
		resize(size() - 1);
		return pos;
	}

	iterator erase(iterator first, iterator last)
	{
		MoeSTL::move(last, end(), first); // first isn't in [last + 1, end)
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
			for_each(begin() + count, end(), [](const T &elem) {elem.~T(); });
			m_iSize = count;
		}
		else if (count > m_iSize)
		{
			reserve(count);
			
			// construct items
			/*for (auto p = m_pData + m_iSize; p < m_pData + count; ++p)
				new(p) T(value);*/
			MoeSTL::uninitialized_fill_n(m_pData + m_iSize, count - m_iSize, value);
			m_iSize = count;
		}
	}
	
};

template<class T>
void swap(vector<T> &a, vector<T> &b)
{
	return a.swap(b);
}

}