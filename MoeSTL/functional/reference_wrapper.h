#pragma once

#include "../type_traits/value_wrapper.h"

namespace MoeSTL {
	template <class T>
	class reference_wrapper 
	{
	public:
		// ¿‡–Õ
		using type = T;

		reference_wrapper(T& ref) noexcept : _ptr(std::addressof(ref)) {}
		reference_wrapper(T&&) = delete;
		reference_wrapper(const reference_wrapper&) noexcept = default;

		reference_wrapper& operator=(const reference_wrapper& x) noexcept = default;

		operator T& () const noexcept { return *_ptr; }
		T& get() const noexcept { return *_ptr; }

		template< class... ArgTypes >
		std::invoke_result_t<T&, ArgTypes...>
			operator() (ArgTypes&&... args) const {
			return std::invoke(get(), std::forward<ArgTypes>(args)...);
		}

	private:
		T * _ptr;
	};
}