#pragma once

namespace MoeSTL {

template< class InputIt, class UnaryFunction >
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
{
	while(first != last)
	{
		f(*first++);
	}
	return f;
}

template< class InputIt, class Size, class UnaryFunction >
InputIt for_each_n(InputIt first, Size count, UnaryFunction f)
{
	while (count--)
	{
		f(*first++);
	}
	return f;
}

}