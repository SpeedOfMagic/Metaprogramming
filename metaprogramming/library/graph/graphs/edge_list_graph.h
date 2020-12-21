#pragma once

#include "graph.h"

#include "../../TL/is_type_list.h"
#include "../../TL/fill_type_list_with_object.h"
#include "../GLib/add_edge.h"

#include "../convert/convert_graph.h"

/**
 * Represents graph as a list of edges.
 * @see Graph
 * @see Edge
 * @param vertexes Template parameter, vertexes of a graph
 * @param edge_list Template parameter, TypeList of Edge
 * @returns Parameter result, resulting graph
*/
template<class nodes, class edge_list>
struct EdgeListGraph {
	constexpr static GraphType TYPE = EDGE_LIST;

	static_assert(TL::IsTypeList<nodes>::value, "Vertexes are not in a TypeList");
	static_assert(TL::IsTypeList<edge_list>::value, "Edge list is not a TypeList");
	using vertexes_ = nodes;  //!< TypeList of vertexes in graph.
	using edge_list_ = edge_list;  //!< TypeList of edges
	using edges_ = edge_list_;

	/**
	* Represents an adapter, which converts one type of a graph into another.
	* Is used as an element in Visitor pattern.
	* @param GraphType Template parameter, type of a resulting graph
	* @returns Parameter result, resulting graph
	*/
	template<GraphType type>
	struct ConvertTo {
		using result = typename ConvertGraph<
			TYPE,
			type,
			EdgeListGraph<vertexes_, edge_list_>
		>::result;
	};
};
