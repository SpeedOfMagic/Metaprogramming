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
template<class nodes, class matrix>
struct AdjacencyMatrixGraph {
	constexpr static GraphType TYPE = ADJACENCY_MATRIX;

	static_assert(TL::IsTypeList<nodes>::value, "Vertexes are not in a TypeList");
	using vertexes_ = nodes;  //!< TypeList of vertexes in graph.
	using matrix_ = matrix;  //!< TypeList of TypeLists of Edges

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
			AdjacencyMatrixGraph<nodes, matrix>
		>::result;
	};
};
