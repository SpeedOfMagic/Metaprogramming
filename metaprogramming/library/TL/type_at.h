#include "type_list.h"

namespace TL {
	/* Get class at specific index of TypeList*/

	template<class type_list, size_t ind>
	struct TypeAt {
		using value = typename TypeAt<typename type_list::Tail, ind - 1>::value;
	};

	template<class type_list>
	struct TypeAt<type_list, 0> {
		using value = typename type_list::Head;
	};
}