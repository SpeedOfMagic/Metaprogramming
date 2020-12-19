#pragma once

#include "is_type_list.h"
#include "type_list.h"

namespace TL {
	/** Gets length of a TypeList
	 * @param TypeList Template parameter
	 * @returns Parameter size, amount of elements in TypeList
	 */
	template<class type_list>
	struct Size {
		static_assert(IsTypeList<type_list>::value, "Passed template argument is not a TypeList");
		constexpr static size_t size = 1 + Size<typename type_list::Tail>::size;
	};

	/**
	 * @see Size
	 */
	template<>
	struct Size<EmptyTypeList> {
		constexpr static size_t size = 0;
	};
}