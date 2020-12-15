#pragma once

#include "is_base_of.h"
#include "type_list.h"

namespace TL {
	/* Finds and returns TypeList that is the parent of T */
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
