#pragma once

/**
 * Represents holder for a typename
 * @param T Template parameter, typename that should be contained
*/
template<typename T>
struct Class {
	using value = T;  //!< Holder of a typename
};