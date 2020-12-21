#pragma once

#include "../functor.h"

/**
 * Represents different types of functors for use in VertexStream.
 * To use it, you need to pass graph as a template parameter and an index of a vertex in this graph as an argument.
 * @see Class
 * @see Functor
 * @see Package java.util.function in Java
*/
namespace StreamFunctorType {
	template<class graph>
	using Consumer = Functor<void(size_t)>;

	template<class graph>
	using Predicate = Functor<bool(size_t)>;

	template<class graph, class ResultType>
	using Function = Functor<ResultType(size_t)>;

	template<class graph, class ResultType>
	using BinaryOperation = Functor<ResultType(ResultType, size_t)>;
}
