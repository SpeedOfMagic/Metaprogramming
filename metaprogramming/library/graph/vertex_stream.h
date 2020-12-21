#pragma once

#include <ranges>
#include <vector>

#include "../TL/add.h"
#include "../TL/contains.h"
#include "../TL/index_of.h"
#include "../TL/type_list.h"

#include "stream.h"

/**
 * Represents a stream of vertexes of a graph
 * @param stream Template parameter, TypeList of vertexes of a graph
 * @param graph Template parameter
*/
template<class stream, class graph>
class VertexStream {
public:
	/**
	* Converts given stream into reversed vector of indexes of vertexes.
	* Also it's based on a variation of "Chain of a responsibility" pattern
	* @returns Vector of reversed indexes of vertexes
	*/
	static std::vector<size_t> MapVertexesToReversedIndexes() {
		std::vector<size_t> result = VertexStream<typename stream::Tail, graph>::MapVertexesToReversedIndexes();
		static_assert(TL::Contains<typename graph::vertexes_, typename stream::Head>::result,
			"Some vertex in stream was not present in the graph");
		result.push_back(TL::IndexOf<typename graph::vertexes_, typename stream::Head>::value);
		return result;
	}

	/**
	* Converts given stream into vector of indexes of vertexes.
	* @returns Vector of indexes of vertexes
	*/
	static Stream<size_t> MapVertexesToIndexes() {
		std::vector<size_t> result = MapVertexesToReversedIndexes();
		std::reverse(result.begin(), result.end());
		return Stream<size_t>(std::move(result));
	}

};

/**
 * @see VertexStream
 */
template<class graph>
struct VertexStream<EmptyTypeList, graph> {
	static std::vector<size_t> MapVertexesToReversedIndexes() {
		return {};
	}
};

/** \example vertex_stream_example.cpp
* An example of how to use VertexStream.
*/