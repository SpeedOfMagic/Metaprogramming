#pragma once

#include "null_type.h"

/**
 @see TypeList<H, T...>
 */
template<typename ...Args>
struct TypeList {
	using Head = NullType;
	using Tail = TypeList<>; 
};

/**
 Represents TypeList with no data
 @see TypeList
 */
using EmptyTypeList = TypeList<>;

/**
 @see TypeList<H, T...>
 */
template<typename T>
struct TypeList<T> {
	using Head = T;
	using Tail = EmptyTypeList;
};

/**
 * Represents a list of various types
 * @param H Template parameter, first object in a type list
 * @param T Template parameter, other objects in a type list
 */
template<typename H, typename ...T>
struct TypeList<H, T...> {
	using Head = H;  //!< First type in a type list
	using Tail = TypeList<T...>;  //!< TypeList of other types
};

/**
 @see TypeList<H, T...>
 */
template<typename ...Args>
using Typelist = TypeList<Args...>;


/**
 * Represents functions (as structs) for working with TypeList
 */
namespace TL {};