#pragma once

#include "class.h"
#include "functor.h"

/**
 * Represents different types of functors.
 * @see Package java.util.function in Java
*/
namespace FunctorType {
	template<typename ...InputArgs>
	using Consumer = Functor<void(InputArgs...)>;
}
