#include <iostream>
#include <string>
#include <iomanip>

#include "MoeSTL/algorithm.h"
#include "MoeSTL/vector.h"

void print_vec(const MoeSTL::vector<int>& vec)
{
	for (auto x : vec) {
		std::cout << ' ' << x;
	}
	std::cout << '\n';
}

int main()
{
	MoeSTL::vector<int> vec(size_t(3), 100);
	print_vec(vec);


	// "it" 不再合法，获取新值：

	MoeSTL::vector<int> vec2(size_t(2), 400);
	vec.insert(vec.begin() + 2, vec2.begin(), vec2.end());
	print_vec(vec);

	int arr[] = { 501,502,503 };
	vec.insert(vec.begin(), arr, arr + 3);
	print_vec(vec);
}