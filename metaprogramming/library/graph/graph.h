#pragma once

#include "../TL/contains.h"
#include "../TL/index_of.h"
#include "../TL/size.h"
#include "../TL/type_at.h"
#include "../TL/type_list.h"

/**
 * Represents graph vertexes defined in vertexes_, and edges, which are derived from adjacency_list_
 * Size of an adjacency list must be equal to amount of vertexes
 * @param vertexes_ TypeList of vertexes in graph.
 * @param adjacency_list_ - TypeList of TypeLists of edges, which are grouped by starting vertex
 *							i.e. edge (from, to, weight) goes to adjacency_list_[from]
 */
template<class vertexes, class adjacency_list>
struct Graph {
	using vertexes_ = vertexes;  //!< TypeList of vertexes in graph.
	using adjacency_list_ = adjacency_list;  //!< TypeList of TypeLists of edges, which are grouped by starting vertex
	static_assert(TL::Size<vertexes_>::size == TL::Size<adjacency_list_>::size, "Amount of vertexes and adjacency lists differ");

	/**
	 * Checks if edge, passed as a template, is located in this graph
	 * @param edge Template parameter, represents an edge to check
	 * @return true if this edge in the graph, false otherwise
	*/
	template<class edge>
	constexpr bool HasEdge() {
		constexpr int vertex_num = TL::IndexOf<vertexes_, typename edge::from>::value;
		using adjacent_vertexes = typename TL::TypeAt<adjacency_list_, vertex_num>::value;
		return TL::Contains<adjacent_vertexes, edge>::result;
	}
};
