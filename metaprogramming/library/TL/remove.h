#include "type_list.h"

namespace TL {
	/* Remove first ocurrence of class from TypeList */
	template<class type_list, typename T>
	struct Remove {
		using result = TypeList<typename type_list::Head,
			typename Remove<typename type_list::Tail, T>::result>;
	};

	template<class type_list>
	struct Remove<type_list, typename type_list::Head> {
		using result = typename type_list::Tail;
	};

	template<typename T>
	struct Remove<EmptyTypeList, T> {
		using result = EmptyTypeList;
	};

	/* Remove all ocurrences of class from TypeList */
	template<class type_list, class T>
	struct RemoveAll {
		using result = TypeList<typename type_list::Head,
			typename RemoveAll<
				typename type_list::Tail, T
			>::result
		>;
	};

	template<class type_list>
	struct RemoveAll<type_list, typename type_list::Head> {
		using result = typename RemoveAll<
			typename type_list::Tail, typename type_list::Head
		>::result;
	};
}