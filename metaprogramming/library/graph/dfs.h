#pragma once

#include <vector>

#include "../TL/concatenate.h"
#include "../TL/contains.h"
#include "../TL/remove.h"
#include "../TL/type_at.h"

#include "graphs/graph_type.h"

namespace GLib {
	/**
	 * Performs Depth-First Search, starting from passed vertex.
	 * It doesn't visit vertexes that have been visited already.
	 * It returns visited edges in chronological order, from which it's easy to deduce DFS.
	 * It's more versatile than one may think)
	 * Also a variation of Composite pattern.
	 * @see GraphType
	 * @param GraphType Template parameter, type of passed graph.
	 * @param graph Template parameter, graph, where DFS happens.
	 * @param starting_vertex Template parameter, starting vertex of DFS.
	 * @returns Parameter result, TypeList of visited edges in chronological order.
	*/
	template<GraphType, class graph, typename starting_vertex>
	struct DFS {};

	template<class graph, typename starting_vertex>
	struct DFS<ADJACENCY_LIST, graph, starting_vertex> {
		using vertexes = typename graph::vertexes_;
		static std::vector<char> visited(TL::Size<vertexes>::size, false);

		static std::vector<size_t> vertex_ind;
		static std::vector<size_t> edge_ind;

		static void Visit(size_t cur_vertex_ind) {
			visited[cur_vertex_ind] = true;
			using children = TL::TypeAt<typename graph::adjacency_list, cur_vertex_ind>::value;

			for (size_t i = 0; i < TL::Size<children>::size; ++i) {
				using child = TL::TypeAt<children, i>::value;
				size_t child_ind = TL::IndexOf<vertexes, child>::value;
				if (!visited[child_ind]) {
					vertex_ind.push_back(cur_vertex_ind);
					edge_ind.push_back(i);
					Visit(child_ind);
				}
			}
		}

		Visit(TL::IndexOf<vertexes, starting_vertex>::value);
	};

}