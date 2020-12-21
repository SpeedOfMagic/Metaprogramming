#pragma once

#include "index_of.h"
#include "type_list.h"

namespace TL {
	/**
	 * Checks if type_list contains typename T
	 * @param type_list Template parameter
	 * @param T Template parameter
	 * @returns Parameter value, true if type_list contains typename T, false otherwise
	 */
	template<class type_list, typename T>
	struct Contains {
		constexpr static bool value = IndexOf<type_list, T>::value >= 0;
	};
};