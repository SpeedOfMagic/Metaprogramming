#pragma once

#include "../TL/type_list.h"
#include "../class.h"
#include "../functor_type.h"

/**
 * Represents a stream of vertexes of a graph
 * @param stream Template parameter, TypeList of vertexes of a graph
 * @param graph Template parameter
*/
template<class stream, class graph>
struct VertexStream {
	using stream_ = stream;  //!< TypeList of vertexes of a graph

	/**
	 * Calls consumer on every vertex in a stream
	 * It's recommended that this object must be of type FunctorTypes::Consumer
	 * Also it's based on a variation of "Chain of a responsibility" pattern
	 * @param consumer Consumer, that accepts Class object of a graph and index of a current vertex
	 * @see FunctorType#Consumer
	 * @see Class
	*/
	template<class Consumer>
	void ForEach(Consumer consumer) {
		constexpr size_t vertex_index = TL::IndexOf<typename graph::vertexes_, typename stream::Head>::value;
		consumer(Class<graph>(), vertex_index);
		VertexStream<typename stream::Tail, graph>().ForEach(consumer);
	}
};

/**
 * @see VertexStream
 */
template<class graph>
struct VertexStream<EmptyTypeList, graph> {
	using stream = EmptyTypeList;

	template<class Consumer>
	void ForEach(Consumer consumer) {}
};
