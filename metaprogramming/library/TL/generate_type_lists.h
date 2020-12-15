#pragma once

#include "add.h"
#include "type_list.h"

namespace TL {
	/* Generates TypeList of n EmptyTypeLists */
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