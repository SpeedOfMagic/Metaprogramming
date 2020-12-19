#include "add.h"
#include "size.h"

#include "is_type_list.h"

namespace TL {
	/**
	* Concatenates two TypeLists
	* @param front Template parameter
	* @param back  Template parameter
	* @returns Parameter result, Concatenated TypeList
	*/
	template<class front, class back>
	struct Concatenate {
		static_assert(IsTypeList<front>::value, "front is not a TypeList");
		static_assert(IsTypeList<back>::value, "back is not a TypeList");

		using result = Concatenate<
			typename Add<
				typename back::Head, 
				Size<front>::size,
				front
			>::result,
			typename back::Tail
		>;
	};

	/**
	* @see Concatenate
	*/
	template<class front>
	struct Concatenate<front, EmptyTypeList> {
		static_assert(IsTypeList<front>::value, "front is not a TypeList");
		using result = front;
	};
}