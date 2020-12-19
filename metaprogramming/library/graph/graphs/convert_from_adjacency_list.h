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
struct ConvertGraph<ADJACENCY_LIST, POINTER_STRUCTURE, graph> {
	template<class current_vertexes, class current_adjacency_list>
	struct MakePointerStructureGraph {
		using type_list_without_first = MakePointerStructureGraph<
			typename current_vertexes::Tail,
			typename current_adjacency_list::Tail
		>::result;

		using result = TL::Add<
			PointerStructureGraph::Node<
			typename current_vertexes::Head,
			typename current_adjacency_list::Head
			>,
			0,
			typename type_list_without_first
		>::result;
	};

	template<>
	struct MakePointerStructureGraph<EmptyTypeList, EmptyTypeList> {}

	using result = PointerStructureGraph<
		typename MakePointerStructureGraph<vertexes_, adjacency_list_>::result
	>;
};
