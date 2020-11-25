#include "type_list.h"

namespace TL {
	/* Get length of TypeList */

	template<class TypeList>
	struct Size {
		constexpr static size_t size = 1 + Size<typename TypeList::Tail>::size;
	};

	template<>
	struct Size<EmptyTypeList> {
		constexpr static size_t size = 0;
	};
}