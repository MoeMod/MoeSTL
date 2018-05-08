#pragma once

#include <utility>
using std::move;

namespace MoeSTL {

template< class InputIt, class OutputIt >
OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
{
	while (first != last)
	{
		*d_first++ = *first++;
	}
	return d_first;
}

template< class InputIt, class OutputIt, class UnaryPredicate >
OutputIt copy_if(InputIt first, InputIt last,
	OutputIt d_first,
	UnaryPredicate pred)
{
	while (first != last)
	{
		if(pred(*first))
			*d_first++ = first;
		first++;
	}
	return d_first;
}

template< class InputIt, class Size, class OutputIt >
OutputIt copy_n(InputIt first, Size count, OutputIt result)
{
	while (count--)
	{
		*result++ = *first++;
	}
	return result;
}

template< class BidirIt1, class BidirIt2 >
BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
{
	while (first != last)
	{
		*(--d_last) = *(--last);
	}
	return d_last;
}

template< class InputIt, class OutputIt >
OutputIt move(InputIt first, InputIt last, OutputIt d_first)
{
	while (first != last)
	{
		*d_first++ = std::move(*first++);
	}
	return d_first;
}

template< class BidirIt1, class BidirIt2 >
BidirIt2 move_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
{
	while (first != last)
	{
		*(--d_last) = std::move(*(--last));
	}
	return d_last;
}

}