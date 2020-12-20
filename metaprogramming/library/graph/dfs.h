#pragma once

#include "graphs/pointer_structure_graph.h"

namespace GLib {
	/**
	 * Performs Depth-First Search, starting from passed vertex.
	 * It doesn't visit vertexes that have been visited already.
	 * It returns visited edges in chronological order, from which it's easy to deduce DFS.
	 * It's more versatile than one may think)
	 * Also a variation of Composite pattern.
	 * @param starting_vertex Template parameter, starting vertex of DFS.
	 * @param graph Graph, where DFS should be performed.
	 * @param visited_vertexes Optional template parameter, vertexes that are not allowed to be visited.
	 * @returns Parameter result, TypeList of visited edges in chronological order.
	*/
	template<class current_vertex, class graph, class visited_vertexes = EmptyTypeList>
	struct DFS {
		static_assert(graph::TYPE == POINTER_STRUCTURE, "Type of a graph is not a POINTER_STRUCTURE");

		using upd_visited = typename TL::Add<current_vertex, 0, visited_vertexes>::result;

		template<class current_children, class cur_visited>
		struct IterateThroughChildren {
			using cur_edge = typename current_children::Head;
			using cur_child = typename GLib::FindNodeByVertex<typename cur_edge::to, PointerStructureGraph<typename graph::nodes_>>::result;

			using new_visited = std::conditional_t<
				TL::Contains<cur_visited, cur_child>::result,
				upd_visited,
				typename DFS<cur_child, upd_visited>::new_visited
			>;

			using result = std::conditional_t<
				TL::Contains<cur_visited, cur_child>::result,
				typename IterateThroughChildren<
					typename current_children::Tail,
					new_visited
				>::result,
				typename TL::Concatenate<
					typename DFS<cur_child, upd_visited>::result,
					typename IterateThroughChildren<
						typename current_children::Tail,
						new_visited
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
			typename current_vertex::children,
			upd_visited
		>;
		using new_visited = typename iterate_through_children::new_visited;
		using result = typename iterate_through_children::result;
	};
}
