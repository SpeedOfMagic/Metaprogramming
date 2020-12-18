#pragma once

#include "add.h"
#include "type_list.h"

namespace TL {
	/** Replaces typename on a specific position in TypeList
	 * @param T Typename that will be on a specific position in TypeList
	 * @param ind Number of this position
	 * @param TypeList<Arg, Args...> This TypeList
	 * @result Parameter result, new type list with typename added to position ind
	 */
	template<typename T, size_t ind, class Arg, class ...Args>
	struct Replace {};

	/**
	 * @see Replace
	 */
	template<typename T, size_t ind, class Arg, class ...Args>
	struct Replace<T, ind, TypeList<Arg, Args...>> {
		using end = typename Replace<
			T,
			ind - 1,
			TypeList<Args...>
		>::result;

		using result = typename Add<Arg, 0, end>::result;
	};

	/**
	 * @see Replace
	 */
	template<typename T, class Arg, class ...Args>
	struct Replace<T, 0, TypeList<Arg, Args...>> {
		using result = TypeList<T, Args...>;
	};
}