#pragma once

#include <type_traits>

#include "type_list.h"

namespace TL {
	template<class type_list, typename T>
	struct MostDerived;

	template<class type_list, typename T, bool is_head_parent_of_T>
	struct CheckDerived {
		using result = NullType;
	};

	template<class type_list, typename T>
	struct CheckDerived<type_list, T, true> {
		using result = typename MostDerived<typename type_list::Tail, typename type_list::Head>::result;
	};

	template<class type_list, typename T>
	struct CheckDerived<type_list, T, false> {
		using result = typename MostDerived<typename type_list::Tail, T>::result;
	};

	template<class type_list, typename T>
	struct MostDerived {
		using result = typename CheckDerived<
			type_list, T, std::is_base_of<T, typename type_list::Head>::value
		>::result;
	};

	template<typename T>
	struct MostDerived<EmptyTypeList, T> {
		using result = T;
	};
};