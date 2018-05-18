#include <iostream>
#include <string>
#include <iomanip>

#include "MoeSTL/algorithm.h"
#include "MoeSTL/list.h"

int main()
{
	MoeSTL::list<int> numbers;
	
	numbers.push_front(5);
	numbers.push_front(3);
	numbers.push_front(4);
	// 内容为 { 5, 3, 4 }

	numbers.swap(numbers);

	for (auto i : numbers) std::cout << i << ' ';
}