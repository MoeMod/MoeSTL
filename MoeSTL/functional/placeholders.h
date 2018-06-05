#pragma once

#include "../type_traits/value_wrapper.h"

namespace MoeSTL {

	namespace placeholders_impl
	{
		template<int N>
		struct PH {};

	}

	template<class T>
	struct is_placeholder; // undefined
	template<int N>
	struct is_placeholder<placeholders_impl::PH<N>>
		: integral_constant<int, N> {};

	namespace placeholders
	{
		constexpr placeholders_impl::PH<1> _1;
		constexpr placeholders_impl::PH<2> _2;
		constexpr placeholders_impl::PH<3> _3;
		constexpr placeholders_impl::PH<4> _4;
		constexpr placeholders_impl::PH<5> _5;
		constexpr placeholders_impl::PH<6> _6;
		constexpr placeholders_impl::PH<7> _7;
		constexpr placeholders_impl::PH<8> _8;
		constexpr placeholders_impl::PH<9> _9;
		constexpr placeholders_impl::PH<10> _10;
		constexpr placeholders_impl::PH<11> _11;
		constexpr placeholders_impl::PH<12> _12;
		constexpr placeholders_impl::PH<13> _13;
		constexpr placeholders_impl::PH<14> _14;
		constexpr placeholders_impl::PH<15> _15;
		constexpr placeholders_impl::PH<16> _16;
		constexpr placeholders_impl::PH<17> _17;
		constexpr placeholders_impl::PH<18> _18;
		constexpr placeholders_impl::PH<19> _19;
		constexpr placeholders_impl::PH<20> _20;
	}
}