#include "null_type.h"

namespace TL {
	/**
	* Checks if passed object is of NullType.
	* @param T Template parameter, object to check.
	* @return Parameter value, true if T is NullType.
	*/
	template<typename T>
	struct IsNullType {
		constexpr static bool value = false;
	};

	/**
	* @see IsNullType
	*/
	template<>
	struct IsNullType<NullType> {
		constexpr static bool value = true;
	};
}