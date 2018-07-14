#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>

#include "MoeSTL/vector.h"

int main()
{
	MoeSTL::vector<std::string> vec{ "1","2","3","4" };
	auto iter = vec.insert(vec.begin() + 1, "0u");
	
	std::cout << *iter << std::endl;
	vec.erase(iter, vec.end());
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(std::cout));
    return 0;
}