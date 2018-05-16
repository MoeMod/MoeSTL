#pragma once

#include <memory>
using std::allocator;

namespace MoeSTL
{
// due to almost every Allocator is empty class
// use EBO here to reduce sizeof(vector), etc...
template<class Allocator> 
class allocator_base : private Allocator
{
protected:
	allocator_base(const Allocator &alloc) : Allocator(alloc) {}
	Allocator get_allocator()
	{
		return *this;
	}
};

}