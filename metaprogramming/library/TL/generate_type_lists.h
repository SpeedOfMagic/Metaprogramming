#pragma once

#include "add.h"
#include "type_list.h"

namespace TL {
	/**
	 * Generates TypeList of n EmptyTypeLists
	 * @see EmptyTypeList
	 * @param n Template parameter, a number of EmptyTypeLists to generate
	 * @returns Parameter result, TypeList of n EmptyTypeList
	 */
	/*  */
	template<int n>
	struct GenerateTypeLists {
		using result = typename Add<
			EmptyTypeList, 
			0, 
			typename GenerateTypeLists<n - 1>::result
		>::result;
	};

	template<>
	struct GenerateTypeLists<0> {
		using result = EmptyTypeList;
	};
}