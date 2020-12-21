#pragma once

#include "convert_graph.h"

#include "../../TL/type_list.h"
#include "../../TL/generate_type_lists.h"
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
struct ConvertGraph<POINTER_STRUCTURE, EDGE_LIST, graph> {
	static_assert(POINTER_STRUCTURE == graph::TYPE, "Type of a graph must be equal to passed argument");


};

/**
 * @see ConvertGraph
 */
template<class graph>
struct ConvertGraph<ADJACENCY_MATRIX, EDGE_LIST, graph> {
	static_assert(ADJACENCY_MATRIX == graph::TYPE, "Type of a graph must be equal to passed argument");


};

