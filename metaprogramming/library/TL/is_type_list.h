#pragma once

#include <type_traits>

#include "type_list.h"

namespace TL {
	/**
	 * Checks if passed class T is a TypeList
	 * @param T Template argument
	 * @returns Parameter value, true if T is a TypeList, false otherwise
	 */
	template<class T>
	struct IsTypeList : public std::false_type {};

	template<class ...Args>
	struct IsTypeList<TypeList<Args...>> : public std::true_type {};
}