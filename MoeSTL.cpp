#include <iostream>
#include <string>
#include <iomanip>

#include "MoeSTL/algorithm.h"
#include "MoeSTL/list.h"

int main()
{
	MoeSTL::list<int> numbers;

	numbers.push_back(5);
	numbers.push_back(3);
	numbers.push_back(4);
	// 内容为 { 5, 3, 4 }
	numbers.pop_back();
	numbers.pop_back();
	numbers.pop_back();
	// 内容为 { 5, 3 }

	for (auto&& i : numbers) std::cout << i << ' ';
}