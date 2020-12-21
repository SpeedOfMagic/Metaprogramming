#pragma once

#include "../../TL/contains.h"

#include "../graphs/pointer_structure_graph.h"

namespace GLib {
	/**
	 * Performs Depth-First Search, starting from passed vertex.
	 * It doesn't visit vertexes that have been visited already.
	 * It returns visited edges in chronological order, from which it's easy to deduce DFS.
	 * It's more versatile than one may think)
	 * Also a variation of Composite pattern.
	 * @param cur_nod Template parameter, starting node in DFS.
	 * @param graph Graph, where DFS should be performed.
	 * @param visited_nodes Optional template parameter, nodes that are not allowed to be visited.
	 * @returns Parameter result, TypeList of visited edges in chronological order.
	 *			Also returns parameter new_visited as a side effect,
	 *			which is a TypeList of visited nodes.
	*/
	template<class cur_node, class graph, class visited_nodes = EmptyTypeList>
	struct DFS {
		static_assert(graph::TYPE == POINTER_STRUCTURE, "Type of a graph is not a POINTER_STRUCTURE");

		using upd_visited = typename TL::Add<cur_node, 0, visited_nodes>::result;

		template<class cur_children, class cur_visited>
		struct IterateThroughChildren {
			using cur_edge = typename cur_children::Head;
			using cur_child = typename GLib::FindNodeByVertex<
				typename cur_edge::to, 
				graph
			>::result;

			using new_visited = std::conditional_t<
				TL::Contains<cur_visited, cur_child>::result,
				upd_visited,
				typename DFS<cur_child, graph, upd_visited>::new_visited
			>;

			using result = std::conditional_t<
				TL::Contains<upd_visited, cur_child>::result,
				typename IterateThroughChildren<
					typename cur_children::Tail,
					new_visited
				>::result,
				typename TL::Add<
					cur_edge,
					0,
					typename TL::Concatenate<
						typename DFS<cur_child, graph, upd_visited>::result,
						typename IterateThroughChildren<
							typename cur_children::Tail,
							new_visited
						>::result
					>::result
				>::result
			>;
		};

		template<class cur_unvisited>
		struct IterateThroughChildren<EmptyTypeList, cur_unvisited> {
			using result = EmptyTypeList;
			using new_visited = upd_visited;
		};

		using iterate_through_children = IterateThroughChildren<
			typename cur_node::children,
			upd_visited
		>;
		using new_visited = typename iterate_through_children::new_visited;
		using result = typename iterate_through_children::result;
	};
}
/** \example get_reached_vertexes.h
* An example of how to use DFS.
*/

/** \example get_nodes_from_roots.h
* An example of how to use DFS.
*/
