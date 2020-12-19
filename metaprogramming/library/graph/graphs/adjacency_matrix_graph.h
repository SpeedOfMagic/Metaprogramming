#pragma once

#include "graph.h"

#include "../../TL/is_type_list.h"
#include "../../TL/generate_type_lists.h"
#include "../add_edge.h"

#include "convert_graph.h"

/**
 * Represents graph as an adjacency matrix.
 * If element in row i, column j is NullType, then there's no edge between them.
 * Otherwise it should be a corresponding Edge.
 * @see Graph
 * @see Edge
 * @param vertexes Template parameter, vertexes of a graph
 * @param matrix Template parameter, an adjacencty matrix
 * @returns Parameter result, resulting graph
*/
template<class vertexes, class matrix>
struct AdjacencyMatrixGraph {
	static_assert(TL::IsTypeList<vertexes>::value, "Vertexes are not in a TypeList");
	using vertexes_ = vertexes;  //!< TypeList of vertexes in graph.
	using matrix_ = matrix;  //!< TypeList of TypeLists of Edges

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
	struct ConvertTo<EDGE_LIST> {
		using result = typename ConvertGraph<
			ADJACENCY_MATRIX,
			EDGE_LIST,
			AdjacencyMatrixGraph<vertexes_, matrix_>
		>::result;
	};
};
