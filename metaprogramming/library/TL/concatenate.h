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

		template<class elements>
		struct IterateThroughReversedFront {
			using result = typename Add<
				typename elements::Head,
				0,
				typename IterateThroughReversedFront<
					typename elements::Tail
				>::result
			>::result;
		};

		template<>
		struct IterateThroughReversedFront<EmptyTypeList> {
			using result = back;
		};

		using result = typename IterateThroughReversedFront<reversed_front>::result;
	};
}