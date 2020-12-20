#pragma once

#include "add.h"
#include "reverse.h"
#include "size.h"

#include "is_type_list.h"

namespace TL {
	/**
	* Concatenates two TypeLists
	* @param front Template parameter
	* @param back  Template parameter
	* @returns Parameter result, Concatenated TypeList
	*/
	template<class front, class back>
	struct Concatenate {
		static_assert(IsTypeList<front>::value, "front is not a TypeList");
		static_assert(IsTypeList<back>::value, "back is not a TypeList");

		using reversed_front = typename Reverse<front>::result;

		template<class elements, class current>
		struct IterateThroughReversedFront {
			using added = typename Add<
				typename elements::Head,
				0,
				current
			>::result;

			using result = typename IterateThroughReversedFront<
				typename elements::Tail,
				added
			>::result;
		};

		template<class current>
		struct IterateThroughReversedFront<EmptyTypeList, current> {
			using result = current;
		};

		using result = typename IterateThroughReversedFront<reversed_front, back>::result;
	};
}