#pragma once

#include "graph.h"

#include "../../TL/is_type_list.h"
#include "../../TL/generate_type_lists.h"
#include "../add_edge.h"

#include "convert_graph.h"

/**
 * Represents graph as a list of edges.
 * @see Graph
 * @see Edge
 * @param vertexes Template parameter, vertexes of a graph
 * @param edge_list Template parameter, TypeList of Edge
 * @returns Parameter result, resulting graph
*/
template<class vertexes, class edge_list>
struct EdgeListGraph {
	static_assert(TL::IsTypeList<vertexes>::value, "Vertexes are not in a TypeList");
	static_assert(TL::IsTypeList<edge_list>::value, "Edge list is not a TypeList");
	using vertexes_ = vertexes;  //!< TypeList of vertexes in graph.
	using edge_list_ = edge_list;  //!< TypeList of edges

	/**
	* Represents an adapter, which converts one type of a graph into another.
	* Is used as an element in Visitor pattern.
	* @param GraphType Template parameter, type of a resulting graph
	* @returns Parameter result, resulting graph
	*/
	template<GraphType>
	struct ConvertTo;

	/**
	* @see ConvertTo
	*/
	template<>
	struct ConvertTo<ADJACENCY_LIST> {
		using result = typename ConvertGraph<
			EDGE_LIST,
			ADJACENCY_LIST,
			EdgeListGraph<vertexes_, edge_list_>
		>::result;
	};
};
