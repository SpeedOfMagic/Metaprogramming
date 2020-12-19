#pragma once

#include "convert_graph.h"

#include "../../TL/type_list.h"
#include "../../TL/generate_type_lists.h"
#include "../../TL/size.h"
#include "../add_edge.h"

#include "adjacency_list_graph.h"
#include "edge_list_graph.h"
#include "pointer_structure_graph.h"
#include "graph_type.h"

template<class graph>
struct ConvertGraph<EDGE_LIST, ADJACENCY_LIST, graph> {
	template<class edge_list>
	struct IterateThroughEdges {
		using result = typename GLib::AddEdge<
			ADJACENCY_LIST,
			typename IterateThroughEdges<typename edge_list::Tail>::result,
			typename edge_list::Head
		>::result;
	};

	template<>
	struct IterateThroughEdges<EmptyTypeList> {
		using result = AdjacencyListGraph<
			typename graph::vertexes,
			typename TL::GenerateTypeLists<TL::Size<typename graph::vertexes>::size>::result
		>;
	};

	using result = typename IterateThroughEdges<typename graph::edge_list>::result;
};