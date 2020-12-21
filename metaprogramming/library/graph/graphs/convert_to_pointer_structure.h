#pragma once

#include "convert_graph.h"

#include "../../TL/add.h"
#include "../../TL/generate_type_lists.h"
#include "../../TL/size.h"
#include "../../TL/type_list.h"

#include "../GLib/add_edge.h"

#include "adjacency_list_graph.h"
#include "adjacency_matrix_graph.h"
#include "edge_list_graph.h"
#include "pointer_structure_graph.h"
#include "pointer_structure_node.h"

#include "graph_type.h"

/**
 * @see ConvertGraph
 */
template<class graph>
struct ConvertGraph<ADJACENCY_LIST, POINTER_STRUCTURE, graph> {
	static_assert(ADJACENCY_LIST == graph::TYPE, "Type of a graph must be equal to passed argument.");

	template<class current_vertexes, class current_adjacency_list>
	struct MakePointerStructureGraph {
		using type_list_without_first = typename MakePointerStructureGraph<
			typename current_vertexes::Tail,
			typename current_adjacency_list::Tail
		>::result;

		using result = typename TL::Add<
			PointerStructureNode<
			typename current_vertexes::Head,
			typename current_adjacency_list::Head
			>,
			0,
			type_list_without_first
		>::result;
	};

	template<>
	struct MakePointerStructureGraph<EmptyTypeList, EmptyTypeList> {
		using result = EmptyTypeList;
	};

	using result = PointerStructureGraph<
		typename MakePointerStructureGraph<
		typename graph::vertexes_,
		typename graph::adjacency_list_
		>::result
	>;
};

/**
 * @see ConvertGraph
 */
template<class graph>
struct ConvertGraph<EDGE_LIST, POINTER_STRUCTURE, graph> {
	static_assert(EDGE_LIST == graph::TYPE, "Type of a graph must be equal to passed argument.");
	using adjacency_list = typename ConvertGraph<EDGE_LIST, ADJACENCY_LIST, graph>::result;
	using result = typename ConvertGraph<ADJACENCY_LIST, POINTER_STRUCTURE, adjacency_list>::result;
};