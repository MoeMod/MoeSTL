#pragma once

#include <utility>
using std::move;

namespace MoeSTL {

template< class T >
void swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = std::move(temp);
}

}