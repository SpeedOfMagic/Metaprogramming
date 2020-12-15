#pragma once

#include "size.h"
#include "type_list.h"

#include <type_traits>

namespace TL {
	/* Get class at specific index of TypeList*/
	template<class type_list, size_t ind>
	struct TypeAt {
		static_assert(ind < TL::Size<type_list>::size, "Index reached out of bounds");
		using value = typename TypeAt<typename type_list::Tail, ind - 1>::value;
	};

	template<class type_list>
	struct TypeAt<type_list, 0> {
		using value = typename type_list::Head;
	};
}
