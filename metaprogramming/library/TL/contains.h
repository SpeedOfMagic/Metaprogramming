#include "index_of.h"
#include "type_list.h"

namespace TL {
	/* Checks if TypeList contains T */

	template<class type_list, typename T>
	struct Contains {
		constexpr static bool result = IndexOf<type_list, T>::value >= 0;
	};
};