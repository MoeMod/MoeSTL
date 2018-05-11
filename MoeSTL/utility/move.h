#pragma once
#include <type_traits>

namespace MoeSTL {

template< class T >
typename std::remove_reference<T>::type&& move(T&& t) noexcept
{
	return static_cast<typename std::remove_reference<T>::type&&>(t);
}

}