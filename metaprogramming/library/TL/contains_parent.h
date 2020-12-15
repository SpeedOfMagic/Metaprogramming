#pragma once

#include <type_traits>

#include "type_list.h"

namespace TL {
	/* Checks if TypeList contains parent of T */
	template<class type_list, typename T>
	struct ContainsParent;
}

template<class type_list, typename T, bool is_parent>
struct CheckContainsParent {};

template<class type_list, typename T>
struct CheckContainsParent<type_list, T, false> {
	constexpr static bool result = TL::ContainsParent<
		typename type_list::Tail,
		T
	>::result;
};

template<class type_list, typename T>
struct CheckContainsParent<type_list, T, true> {
	constexpr static bool result = true;
};

namespace TL {
	template<class type_list, typename T>
	struct ContainsParent {
		constexpr static bool result = CheckContainsParent<
			type_list,
			T,
			std::is_base_of<typename type_list::Head, T>::value
		>::result;
	};

	template<typename T>
	struct ContainsParent<EmptyTypeList, T> {
		constexpr static bool result = false;
	};
}