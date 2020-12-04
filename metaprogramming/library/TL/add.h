#pragma once

#include "type_list.h"

namespace TL {
	/* Add class to specific position in TypeList */

	template<typename T, size_t ind, class Arg, class ...Args>
	struct Add {};

	template<typename T, size_t ind, class Arg, class ...Args>
	struct Add<T, ind, TypeList<Arg, Args...>> {
		using end = typename Add<
			T,
			ind - 1,
			TypeList<Args...>
		>::result;

		using result = typename Add<Arg, 0, end>::result;
	};

	template<typename T, class Arg, class ...Args>
	struct Add<T, 0, TypeList<Arg, Args...>> {
		using result = TypeList<T, Arg, Args...>;
	};

	template<typename T, class ...Args>
	struct Add<T, 0, TypeList<Args...>> {
		using result = TypeList<T, Args...>;
	};
}