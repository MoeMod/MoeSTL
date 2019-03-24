#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>

#include "MoeSTL/utility.h"

int main()
{
	using A = MoeSTL::make_integer_sequence<int, 2333>;
	std::cout << typeid(A).name() << std::endl;
    return 0;
}