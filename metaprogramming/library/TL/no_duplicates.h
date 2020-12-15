#include "remove.h"
#include "type_list.h"

namespace TL {
	/* Remove duplicates from TypeList */
	template<class type_list>
	struct NoDuplicates {
		using result = TypeList<
			typename type_list::Head,
			typename NoDuplicates<
				typename RemoveAll<
					typename type_list::Tail, typename type_list::Head
				>::result
			>::result
		>;
	};

	template<>
	struct NoDuplicates<EmptyTypeList> {
		using result = EmptyTypeList;
	};
}