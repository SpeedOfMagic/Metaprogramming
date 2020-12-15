#pragma once

#include "../TL/add.h"
#include "../TL/replace.h"
#include "../TL/type_list.h"
#include "../TL/index_of.h"

namespace GLib {
	/* Returns graph with added edge */
	template<class graph, class from, class to>
	struct MakeEdge {
		constexpr static int vertex_num = TL::IndexOf<typename graph::vertexes, from>::value;
		using adjacent_vertexes = typename TL::TypeAt<typename graph::adjacency_list, vertex_num>::value;

		using new_adjacent_vertexes = typename TL::Add<to, 0, adjacent_vertexes>::result;
		using new_adjacency_list = typename TL::Replace<new_adjacent_vertexes, vertex_num, typename graph::adjacency_list>::result;
		using result = typename Graph<typename graph::vertexes, new_adjacency_list>;
	};

	template<class graph, class edge>
	struct AddEdge;

	template<class graph, class from, class to>
	struct AddEdge<graph, TypeList<from, to>> {
		using result = typename MakeEdge<graph, from, to>::result;
	};
}