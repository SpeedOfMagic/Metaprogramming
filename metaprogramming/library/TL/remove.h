#include "type_list.h"

namespace TL {
	/**
	 * Removes first ocurrence of T in type_list
	 * @param type_list Template parameter
	 * @param T Template parameter
	 * @returns Parameter result, new TypeList without first ocurrence of T
	 */
	template<class type_list, typename T>
	struct Remove {
		using result = TypeList<typename type_list::Head,
			typename Remove<typename type_list::Tail, T>::result>;
	};

	/**
	 * @see Remove
	 */
	template<class type_list>
	struct Remove<type_list, typename type_list::Head> {
		using result = typename type_list::Tail;
	};

	/**
	 * @see Remove
	 */
	template<typename T>
	struct Remove<EmptyTypeList, T> {
		using result = EmptyTypeList;
	};

	/**
	 * Removes all ocurrences of T in type_list
	 * @param type_list Template parameter
	 * @param T Template parameter
	 * @returns Parameter result, new TypeList without ocurrences of T
	 */
	template<class type_list, class T>
	struct RemoveAll {
		using result = TypeList<typename type_list::Head,
			typename RemoveAll<
				typename type_list::Tail, T
			>::result
		>;
	};

	/**
	 * @see RemoveAll
	 */
	template<class type_list>
	struct RemoveAll<type_list, typename type_list::Head> {
		using result = typename RemoveAll<
			typename type_list::Tail, typename type_list::Head
		>::result;
	};
}