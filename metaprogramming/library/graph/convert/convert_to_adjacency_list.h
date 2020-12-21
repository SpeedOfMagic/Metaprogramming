#pragma once

#include "convert_graph.h"

#include "../../TL/type_list.h"
#include "../../TL/fill_type_list_with_object.h"
#include "../../TL/size.h"

#include "../GLib/add_edge.h"

#include "../graphs/adjacency_list_graph.h"
#include "../graphs/adjacency_matrix_graph.h"
#include "../graphs/edge_list_graph.h"
#include "../graphs/pointer_structure_graph.h"
#include "../graphs/graph_type.h"

/**
 * @see ConvertGraph
 */
template<class graph>
struct ConvertGraph<EDGE_LIST, ADJACENCY_LIST, graph> {
	static_assert(EDGE_LIST == graph::TYPE, "Type of a graph must be equal to passed argument");

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
			typename graph::vertexes_,
			typename TL::FillTypeListWithObject<
				EmptyTypeList, 
				TL::Size<typename graph::vertexes_>::size
			>::result
		>;
	};

	using result = typename IterateThroughEdges<typename graph::edge_list_>::result;
};
