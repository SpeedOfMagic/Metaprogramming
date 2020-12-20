#pragma once

#include "../library/TL/is_base_of.h"
#include "../library/TL/type_list.h"

namespace TL {
	/* Finds typelist, that is most derived, parent of derived_typelist and is not derived_typelist */

	template<class type_lists, class derived_typelist, class found_type_list = derived_typelist>
	struct FindRequiredTypeList;
}

template<class type_lists, typename derived_typelist, class found_type_list, bool is_head_parent_of_derived_type_list>
struct CheckFindRequiredTypeList {};

template<class type_lists, typename derived_typelist, class found_type_list>
struct CheckFindRequiredTypeList<type_lists, derived_typelist, found_type_list, true> {
	using result = typename TL::FindRequiredTypeList<
		typename type_lists::Tail,
		derived_typelist,
		typename type_lists::Head
	>::result;
};

template<class type_lists, typename derived_typelist, class found_type_list>
struct CheckFindRequiredTypeList<type_lists, derived_typelist, found_type_list, false> {
	using result = typename TL::FindRequiredTypeList<
		typename type_lists::Tail,
		derived_typelist,
		found_type_list
	>::result;
};

namespace TL {
	template<class type_lists, class derived_typelist, class found_type_list>
	struct FindRequiredTypeList {
		using result = typename CheckFindRequiredTypeList<
			type_lists,
			derived_typelist,
			found_type_list,
			TL::IsBaseOf<typename type_lists::Head, derived_typelist>::result &&
			(TL::IsBaseOf<found_type_list, typename type_lists::Head>::result
				|| std::is_same<found_type_list, derived_typelist>::value
				) &&
			!std::is_same<derived_typelist, typename type_lists::Head>::value
		>::result;
	}; \

		template<class derived_typelist, class found_type_list>
	struct FindRequiredTypeList<EmptyTypeList, derived_typelist, found_type_list> {
		using result = found_type_list;
	};
};
