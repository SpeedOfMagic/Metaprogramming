#pragma once

#include "add.h"
#include "type_list.h"

namespace TL {
	/* Replace class on a specific position in TypeList */

	template<typename T, size_t ind, class Arg, class ...Args>
	struct Replace {};

	template<typename T, size_t ind, class Arg, class ...Args>
	struct Replace<T, ind, TypeList<Arg, Args...>> {
		using end = typename Replace<
			T,
			ind - 1,
			TypeList<Args...>
		>::result;

		using result = typename Add<Arg, 0, end>::result;
	};

	template<typename T, class Arg, class ...Args>
	struct Replace<T, 0, TypeList<Arg, Args...>> {
		using result = TypeList<T, Args...>;
	};
}