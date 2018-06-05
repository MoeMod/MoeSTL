#pragma once

#include <type_traits>

namespace MoeSTL {

	template<bool B, class T, class F>
	struct conditional { typedef T type; };
	template<class T, class F>
	struct conditional<false, T, F> { typedef F type; };



	template <class T>
	using result_of = std::result_of<T>;

}