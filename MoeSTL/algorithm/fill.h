#pragma once

namespace MoeSTL {

template< class ForwardIt, class T >
void fill(ForwardIt first, ForwardIt last, const T& value)
{
	while (first != last)
	{
		++first = value;
	}
}

template< class OutputIt, class Size, class T >
OutputIt fill_n(OutputIt first, Size count, const T& value)
{
	for (Size i = 0; i < count; ++i)
	{
		*first++ = value;
	}
	return first;
}

}