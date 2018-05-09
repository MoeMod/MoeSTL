#include <iostream>
#include <string>

#include "MoeSTL/algorithm.h"
#include "MoeSTL/vector.h"

template<typename T>
std::ostream& operator<<(std::ostream& s, const MoeSTL::vector<T>& v) {
	s.put('[');
	char comma[3] = { '\0', ' ', '\0' };
	for (const auto& e : v) {
		s << comma << e;
		comma[0] = ',';
	}
	return s << ']';
}

int main()
{
	// c++11 初始化器列表语法：
	MoeSTL::vector<std::string> words1{ "the", "frogurt", "is", "also", "cursed" };
	std::cout << "words1: " << words1 << '\n';

	// words2 == words1
	MoeSTL::vector<std::string> words2(words1.begin(), words1.end());
	words2.insert(words2.begin() + 2, words1.begin(), words1.end());
	std::cout << "words2: " << words2 << '\n';

	// words3 == words1
	MoeSTL::vector<std::string> words3(words1);
	std::cout << "words3: " << words3 << '\n';

	// words4 为 {"Mo", "Mo", "Mo", "Mo", "Mo"}
	MoeSTL::vector<std::string> words4(5, "Mo");
	std::cout << "words4: " << words4 << '\n';
	
	std::cout << sizeof(words4) << '\n';
}