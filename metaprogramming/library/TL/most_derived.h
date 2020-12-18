#pragma once

#include <type_traits>

#include "type_list.h"

namespace TL {
	/**
	 * Finds the most derived child of T in type_list
	 * @param type_list Template parameter
	 * @param T Template parameter
	 * @returns Parameter result, the most derived child of T in type_list
	 */
	template<class type_list, typename T>
	struct MostDerived;
}

template<class type_list, typename T, bool is_head_parent_of_T>
struct CheckMostDerived {
	using result = NullType;
};

template<class type_list, typename T>
struct CheckMostDerived<type_list, T, true> {
	using result = typename TL::MostDerived<typename type_list::Tail, typename type_list::Head>::result;
};

template<class type_list, typename T>
struct CheckMostDerived<type_list, T, false> {
	using result = typename TL::MostDerived<typename type_list::Tail, T>::result;
};

namespace TL {
	template<class type_list, typename T>
	struct MostDerived {
		using result = typename CheckMostDerived<
			type_list,
			T,
			std::is_base_of<T, typename type_list::Head>::value
		>::result;
	};

	template<typename T>
	struct MostDerived<EmptyTypeList, T> {
		using result = T;
	};
};