#pragma once

#include "add.h"
#include "type_list.h"

namespace TL {
	/**
	 * Generates TypeList of n objects of type obj.
	 * @see EmptyTypeList
	 * @param obj Template parameter, an object to fill TypeList with.
	 * @param n Template parameter, a number of EmptyTypeLists to generate.
	 * @returns Parameter result, TypeList of n EmptyTypeList.
	 */
	template<typename obj, int n>
	struct FillTypeListWithObject {
		using result = typename Add<
			obj, 
			0, 
			typename FillTypeListWithObject<obj, n - 1>::result
		>::result;
	};

	template<typename obj>
	struct FillTypeListWithObject<obj, 0> {
		using result = EmptyTypeList;
	};
}