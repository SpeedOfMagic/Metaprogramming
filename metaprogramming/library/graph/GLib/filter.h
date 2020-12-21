#pragma once

#include <type_traits>

#include "../process_vertex.h"

#include "../../TL/add.h"

namespace GLib {
	/**
	* Leaves only vertexes that return true when called with ProcessVertex.
	* ProcessVertex must have constexpr static parameter called ''result'' that can be casted to bool.
	* @see ProcessVertex
	* @param id Template parameter, integer, which ForEach uses to access specific ProcessVertex implementation.
	* @param graph Template parameter, graph, where vertexes are located.
	* @param vertexes Optional template parameter, vertexes to process. Is equal to graph's vertexes by default.
	* @returns Parameter result, TypeList of vertexes which return true on ProcessVertex.
	*/
	template<int id, class graph, class vertexes = typename graph::vertexes_>
	struct Filter {
		using tail_result = typename Filter<id, graph, typename vertexes::Tail>::result;

		using result = std::conditional_t<
			ProcessVertex<id, graph, typename vertexes::Head>::result,
			typename TL::Add<typename vertexes::Head, 0, tail_result>::result,
			tail_result
		>;
	};

	/**
	* @see Filter
	*/
	template<int id, class graph>
	struct Filter<id, graph, EmptyTypeList> {
		using result = EmptyTypeList;
	};
}
/** \example vertex_stream_example.cpp
* An example of how to use Filter.
*/