#pragma once

#include "add.h"

namespace TL {
	/**
	* Reverses type_list
	* @param type_list Template parameter
	* @returns Parameter result, reversed type_list
	*/
	template<class type_list>
	struct Reverse {
		template<class cur_type_list, class cur_result>
		struct IterateThroughElements {
			using result = IterateThroughElements <
				typename cur_type_list::Tail,
				typename TL::Add<
					typename cur_type_list::Head,
					0,
					cur_result
				>::result
			>;
		};

		template<class cur_result>
		struct IterateThroughElements<EmptyTypeList, cur_result> {
			using result = cur_result;
		};

		using result = typename IterateThroughElements<type_list, EmptyTypeList>::result;
	};
}