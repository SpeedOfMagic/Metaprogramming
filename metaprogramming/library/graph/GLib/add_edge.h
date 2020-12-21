#pragma once

#include "../../TL/replace.h"
#include "../../TL/type_list.h"
#include "../../TL/type_at.h"
#include "../../TL/index_of.h"
#include "../graphs/graph_type.h"
#include "../graphs/adjacency_list_graph.h"

namespace GLib {
	/** Returns new graph with added edge
	 * @param GraphType Template parameter, type of a graph
	 * @param graph Template parameter, initial graph
	 * @param edge Template parameter, edge to add
	 * @see Edge
	 * @see GraphType
	 * @returns Parameter result, new graph with added edge
	 */
	template<GraphType, class graph, class edge>
	struct AddEdge;

	/**
	 * @see AddEdge
	 */
	template<class graph, class edge>
	struct AddEdge<ADJACENCY_LIST, graph, edge> {
		constexpr static size_t vertex_num = graph::template GetVertexIndex<typename edge::from>();
		using adjacent_vertexes = typename TL::TypeAt<typename graph::adjacency_list_, vertex_num>::value;

		using new_adjacent_vertexes = typename TL::Add<edge, 0, adjacent_vertexes>::result;
		using new_adjacency_list = typename TL::Replace<new_adjacent_vertexes, vertex_num, typename graph::adjacency_list_>::result;
		using result = AdjacencyListGraph<typename graph::vertexes_, new_adjacency_list>;
	};
}
