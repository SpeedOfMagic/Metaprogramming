#pragma once

#include "../TL/add.h"
#include "../TL/replace.h"
#include "../TL/type_list.h"
#include "../TL/index_of.h"

namespace GLib {
	/** Returns new graph with added edge
	 * @param graph Template parameter, initial graph
	 * @param edge Template parameter, edge to add
	 * @returns Parameter result, new graph with added edge
	*/
	template<class graph, class edge>
	struct AddEdge {
		constexpr static int vertex_num = TL::IndexOf<typename graph::vertexes_, typename edge::from>::value;
		using adjacent_vertexes = typename TL::TypeAt<typename graph::adjacency_list_, vertex_num>::value;

		using new_adjacent_vertexes = typename TL::Add<edge, 0, adjacent_vertexes>::result;
		using new_adjacency_list = typename TL::Replace<new_adjacent_vertexes, vertex_num, typename graph::adjacency_list_>::result;
		using result = Graph<typename graph::vertexes_, new_adjacency_list>;
	};
}
