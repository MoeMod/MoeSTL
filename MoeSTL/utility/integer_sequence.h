#pragma once

namespace MoeSTL
{
	template<class T, T...I> struct integer_sequence
	{
		using value_type = T;
		static constexpr std::size_t size() noexcept
		{
			return sizeof...(I);
		}
	};
	template<size_t... Ints> using index_sequence = std::integer_sequence<size_t, Ints...>;

	namespace detail
	{
		template<class T, T N, bool = (N == 0)> struct make_integer_sequence_impl
		{
			template<class Seq, bool> struct integer_sequence_double;
			template<T...I> struct integer_sequence_double<integer_sequence<T, I...>, false>
			{
				using type = integer_sequence<T, I..., (I + N / 2)...>;
			};
			template<T...I> struct integer_sequence_double<integer_sequence<T, I...>, true>
			{
				using type = integer_sequence<T, I..., (I + N / 2)..., N - 1>;
			};

			using type = typename integer_sequence_double<typename make_integer_sequence_impl<T, (N / 2)>::type, (N % 2 != 0)>::type;
		};
		template<class T, T N> struct make_integer_sequence_impl<T, N, true>
		{
			using type = integer_sequence<T>;
		};
	}
	template<class T, T N> using make_integer_sequence = typename detail::make_integer_sequence_impl<T, N>::type;
	template<size_t N> using make_index_sequence = make_integer_sequence<size_t, N>;
	template<class... T> using index_sequence_for = make_index_sequence<sizeof...(T)>;
}