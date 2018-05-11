#pragma once

#include "move.h"

namespace MoeSTL {

template< class T >
void swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = MoeSTL::move(temp);
}

}