#pragma once

#include "../utility/move.h"
#include <iterator>
using std::iterator_traits;

namespace MoeSTL {

template< class T >
T* addressof(T& arg)
{
	return reinterpret_cast<T*>(
		&const_cast<char&>(
			reinterpret_cast<const volatile char&>(arg)));
}


template< class InputIt, class ForwardIt >
ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first)
{
	using ValueType = typename std::iterator_traits<ForwardIt>::value_type;
	ForwardIt current = d_first;
	try
	{
		while (first != last)
		{
			new (static_cast<void*>(MoeSTL::addressof(*current++))) ValueType(*first++);
		}
		return current;
	}
	catch (...)
	{
		while (d_first != current)
		{
			(d_first++)->~ValueType();
		}
		throw;
	}
}

template< class InputIt, class Size, class ForwardIt >
ForwardIt uninitialized_copy_n(InputIt first, Size count, ForwardIt d_first)
{
	using ValueType = typename std::iterator_traits<ForwardIt>::value_type;
	ForwardIt current = d_first;
	try
	{
		while (count--)
		{
			new (static_cast<void*>(MoeSTL::addressof(*current++))) ValueType(*first++);
		}
		return current;
	}
	catch (...)
	{
		while (d_first != current)
		{
			(d_first++)->~ValueType();
		}
		throw;
	}
}

template< class ForwardIt, class T >
void uninitialized_fill(ForwardIt first, ForwardIt last, const T& value)
{
	using ValueType = typename std::iterator_traits<ForwardIt>::value_type;
	ForwardIt current = first;
	try
	{
		while (first != last)
		{
			new (static_cast<void*>(MoeSTL::addressof(*current++))) ValueType(value);
		}
	}
	catch (...)
	{
		while (first != current)
		{
			(first++)->~ValueType();
		}
		throw;
	}
}

template< class ForwardIt, class Size, class T >
ForwardIt uninitialized_fill_n(ForwardIt first, Size count, const T& value)
{
	using ValueType = typename std::iterator_traits<ForwardIt>::value_type;
	ForwardIt current = first;
	try
	{
		while (count--)
		{
			new (static_cast<void*>(MoeSTL::addressof(*current++))) ValueType(value);
		}
		return current;
	}
	catch (...)
	{
		while (first != current)
		{
			(first++)->~ValueType();
		}
		throw;
	}
}

template< class InputIt, class ForwardIt >
ForwardIt uninitialized_move(InputIt first, InputIt last, ForwardIt d_first)
{
	using ValueType = typename std::iterator_traits<ForwardIt>::value_type;
	ForwardIt current = d_first;
	try
	{
		while (first != last)
		{
			new (static_cast<void*>(MoeSTL::addressof(*current++))) ValueType(MoeSTL::move(*first++));
		}
		return current;
	}
	catch (...)
	{
		while (d_first != current)
		{
			(d_first++)->~ValueType();
		}
		throw;
	}
}

template< class InputIt, class Size, class ForwardIt >
ForwardIt uninitialized_move_n(InputIt first, Size count, ForwardIt d_first)
{
	using ValueType = typename std::iterator_traits<ForwardIt>::value_type;
	ForwardIt current = d_first;
	try
	{
		while (count--)
		{
			new (static_cast<void*>(MoeSTL::addressof(*current++))) ValueType(MoeSTL::move(*first++));
		}
		return current;
	}
	catch (...)
	{
		while (d_first != current)
		{
			(d_first++)->~ValueType();
		}
		throw;
	}
}

}