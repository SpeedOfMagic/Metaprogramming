#pragma once

#include <type_traits>

#include "find_node_by_vertex.h"
#include "dfs.h"

#include "../graphs/convert_graph.h"
#include "../graphs/convert_to_pointer_structure.h"

namespace GLib {
	/**
	* Gets all vertexes that can be reached from vertex start.
	* @see DFS
	* @param graph Template parameter, graph to process
	* @param start Template parameter
	* @returns Parameter result, all vertexes that are reached from start.
	*/
	template<class graph, typename start>
	struct GetReachedVertexes {
		// Other types are not supported. If that's a problem, then one can simply convert graph into this type.
		static_assert(POINTER_STRUCTURE == graph::TYPE, "Graph must be of POINTER_STRUCTURE type");

		// We present start vertex as a node since DFS is working with them
		using start_node = typename FindNodeByVertex<start, graph>::result;

		using dfs_search = typename DFS<start_node, graph>::result;  // Result of a DFS search.
		
		// Iterates through each edge and extracts vertexes from them.
		template<class cur_edges>
		struct IterateThroughEdges {
			using cur_edge = typename cur_edges::Head;
			using result = typename TL::Add<
				typename cur_edge::to,  // We don't need to also add ''from'' vertex.
				0,
				typename IterateThroughEdges<typename cur_edges::Tail>::result
			>::result;
		};

		template<>
		struct IterateThroughEdges<EmptyTypeList> {
			using result = EmptyTypeList;
		};

		// Also we add start vertex since it's not included in IterateThroughEdges.
		using result = typename TL::Add<
			start, 0, typename IterateThroughEdges<dfs_search>::result
		>::result;
	};
}
