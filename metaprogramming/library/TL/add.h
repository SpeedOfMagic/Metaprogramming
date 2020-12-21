#pragma once

#include "type_list.h"

namespace TL {
	/**
	 * @see Add<T, ind, TypeList<Arg, Args...>>
	 */
	template<typename T, size_t ind, class Arg, class ...Args>
	struct Add;

	/** Adds typename to a specific position in TypeList
	 * @param T Typename to add to a specific position in TypeList
	 * @param ind Number of this position
	 * @param TypeList<Arg, Args...> This TypeList
	 * @value Parameter value, new type list with typename added to position ind
	 */
	template<typename T, size_t ind, class Arg, class ...Args>
	struct Add<T, ind, TypeList<Arg, Args...>> {
		using end = typename Add<
			T,
			ind - 1,
			TypeList<Args...>
		>::result;

		using result = typename Add<Arg, 0, end>::result;
	};

	/**
	 * @see Add<T, ind, TypeList<Arg, Args...>>
	 */
	template<typename T, class Arg, class ...Args>
	struct Add<T, 0, TypeList<Arg, Args...>> {
		using result = TypeList<T, Arg, Args...>;
	};

	/**
	 * @see Add<T, ind, TypeList<Arg, Args...>>
	 */
	template<typename T, class ...Args>
	struct Add<T, 0, TypeList<Args...>> {
		using result = TypeList<T, Args...>;
	};
}