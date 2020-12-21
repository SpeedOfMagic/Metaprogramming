#pragma once

#include "../process_vertex.h"

#include "../../TL/add.h"

namespace GLib {
	/**
	* Processes each vertex by using ProcessVertex.
	* @see ProcessVertex
	* @param id Template parameter, integer, which ForEach uses to access specific ProcessVertex implementation.
	* @param graph Template parameter, graph, where vertexes are located.
	* @param vertexes Optional template parameter, vertexes to process. Is equal to graph's vertexes by default.
	* @returns Parameter result, TypeList of ProcessVertex, applied to each vertex.
	*/
	template<int id, class graph, class vertexes = typename graph::vertexes_>
	struct ForEach {
		using result = typename TL::Add<
			ProcessVertex<id, graph, typename vertexes::Head>,
			0,
			typename ForEach<id, graph, typename vertexes::Tail>::result
		>::result;
	};

	/**
	* @see ForEach
	*/
	template<int id, class graph>
	struct ForEach<id, graph, EmptyTypeList> {
		using result = EmptyTypeList;
	};
}
/** \example vertex_stream_example.cpp
* An example of how to use ForEach.
*/