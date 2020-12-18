#pragma once

#include "contains.h"
#include "type_list.h"

namespace TL {
	/**
	 * Finds and returns TypeList that has T
	 * @param T Template parameter
	 * @param type_list Template parameter, first TypeList among other TypeLists
	 * @param ...type_lists Template parameter, other TypeLists to check
	 * @returns Parameter result, first TypeList that contains T, compilation error otherwise
	 */
	template<typename T, class type_list, class ...type_lists>
	struct FindTypeListByClass;
}

template<bool contains_class, typename T, class type_list, class ...type_lists>
struct CheckFindTypeListByClass {
	using result = NullType;
};

template<typename T, class type_list, class ...type_lists>
struct CheckFindTypeListByClass<true, T, type_list, type_lists...> {
	using result = type_list;
};

template<typename T, class type_list, class ...type_lists>
struct CheckFindTypeListByClass<false, T, type_list, type_lists...> {
	using result = typename TL::FindTypeListByClass<T, type_lists...>::result;
};

namespace TL {
	template<typename T, class type_list, class ...type_lists>
	struct FindTypeListByClass {
		using result = typename CheckFindTypeListByClass<
			TL::Contains<type_list, T>::result,
			T,
			type_list,
			type_lists...
		>::result;
	};
}
