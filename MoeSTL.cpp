#include <iostream>
#include <string>
#include <algorithm>

#include "MoeSTL/algorithm.h"
#include "MoeSTL/array.h"

int main()
{
	// 用聚合初始化构造
	MoeSTL::array<int, 3> a1{ { 1, 2, 3 } }; // C++11 中要求双花括号（ C++14 中不要求）
	MoeSTL::array<int, 3> a2 = { 1, 2, 3 };  // 决不要求在 = 后
	MoeSTL::array<std::string, 2> a3 = { std::string("a"), "b" };

	// 支持容器操作
	std::sort(a1.begin(), a1.end());
	std::reverse_copy(a2.begin(), a2.end(),
	std::ostream_iterator<int>(std::cout, " "));

	std::cout << '\n';

	// 支持带范围 for 循环
	for (const auto& s : a3)
		std::cout << s << ' ';
}