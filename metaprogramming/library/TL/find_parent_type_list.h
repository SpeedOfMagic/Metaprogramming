#pragma once

#include "is_base_of.h"
#include "type_list.h"

namespace TL {
	/**
	 * Finds and returns TypeList that has the parent of T
	 * @param T
	 * @param type_list First TypeList among other TypeLists
	 * @param ...type_lists Other TypeLists to check
	 * @returns Parameter result, first TypeList that contains the parent of T, compilation error otherwise
	 */
	template<typename T, class type_list, class ...type_lists>
	struct FindParentTypeList;
}

template<bool contains_class, typename T, class type_list, class ...type_lists>
struct CheckFindParentTypeList {
	using result = NullType;
};

template<typename T, class type_list, class ...type_lists>
struct CheckFindParentTypeList<true, T, type_list, type_lists...> {
	using result = type_list;
};

template<typename T, class type_list, class ...type_lists>
struct CheckFindParentTypeList<false, T, type_list, type_lists...> {
	using result = typename TL::FindParentTypeList<T, type_lists...>::result;
};

namespace TL {
	template<typename T, class type_list, class ...type_lists>
	struct FindParentTypeList {
		using result = typename CheckFindParentTypeList<
			TL::IsBaseOf<type_list, T>::result,
			T,
			type_list,
			type_lists...
		>::result;
	};
}
