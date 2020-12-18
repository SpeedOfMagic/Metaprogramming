#include "remove.h"
#include "type_list.h"

namespace TL {
	/**
	 * Removes duplicated from TypeList type_list
	 * @param type_list Template parameter
	 * @returns Parameter result, new TypeList without any duplicates
	 */
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

	/**
	 * @see NoDuplicates
	 */
	template<>
	struct NoDuplicates<EmptyTypeList> {
		using result = EmptyTypeList;
	};
}