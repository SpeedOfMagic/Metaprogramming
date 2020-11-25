#include "contains.h"
#include "type_list.h"

namespace TL {
	/* Finds and returns TypeList that contains T among all other TypeLists */

	template<typename T, class type_list, class ...type_lists>
	struct FindTypeListByClass;

	template<bool contains_class, typename T, class type_list, class ...type_lists>
	struct CheckTypeList {
		using result = NullType;
	};

	template<typename T, class type_list, class ...type_lists>
	struct CheckTypeList<true, T, type_list, type_lists...> {
		using result = type_list;
	};

	template<typename T, class type_list, class ...type_lists>
	struct CheckTypeList<false, T, type_list, type_lists...> {
		using result = typename FindTypeListByClass<T, type_lists...>::result;
	};

	template<typename T, class type_list, class ...type_lists>
	struct FindTypeListByClass {
		using result = typename CheckTypeList<
			TL::Contains<type_list, T>::result,
			T,
			type_list,
			type_lists...
		>::result;
	};
}
