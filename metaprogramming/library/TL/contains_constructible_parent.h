#pragma once

#include <type_traits>
#include "type_list.h"

namespace TL {
	/* Checks if TypeList contains constructible parent of T */
	template<class type_list, typename T>
	struct ContainsConstructibleParent;
}

template<class type_list, typename T, bool is_parent>
struct CheckContainsConstructibleParent {};

template<class type_list, typename T>
struct CheckContainsConstructibleParent<type_list, T, false> {
	constexpr static bool result = TL::ContainsConstructibleParent<
		typename type_list::Tail,
		T
	>::result;
};

template<class type_list, typename T>
struct CheckContainsConstructibleParent<type_list, T, true> {
	constexpr static bool result = true;
};

namespace TL {
	template<class type_list, typename T>
	struct ContainsConstructibleParent {
		constexpr static bool result = CheckContainsConstructibleParent<
			type_list,
			T,
			std::is_base_of<typename type_list::Head, T>::value &&
			std::is_constructible<typename type_list::Head>::value
		>::result;
	};

	template<typename T>
	struct ContainsConstructibleParent<EmptyTypeList, T> {
		constexpr static bool result = false;
	};
}