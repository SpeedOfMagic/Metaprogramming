#pragma once

#include "type_list.h"

namespace TL {
	/** Gets length of a TypeList
	 * @param TypeList Template parameter
	 * @returns Parameter size, amount of elements in TypeList
	 */
	template<class TypeList>
	struct Size {
		constexpr static size_t size = 1 + Size<typename TypeList::Tail>::size;
	};

	/**
	 * @see Size
	 */
	template<>
	struct Size<EmptyTypeList> {
		constexpr static size_t size = 0;
	};
}