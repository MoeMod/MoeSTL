#pragma once

namespace MoeSTL {

template< class T >
void swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

}