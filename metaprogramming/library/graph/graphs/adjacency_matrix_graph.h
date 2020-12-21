#pragma once

#include "graph.h"

#include "../../TL/is_type_list.h"
#include "../../TL/fill_type_list_with_object.h"
#include "../GLib/add_edge.h"

#include "../convert/convert_graph.h"

/**
 * Represents graph as an adjacency matrix.
 * Element in row i, column j must be Objects::Boolean. 
 * If it's Boolean<false>, then there's no edge between them. Otherwise there is.
 * If element is Boolean<true>, then the weight is NullType. Otherwise it's equal to this element.
 * If you wish to have Boolean as a weight, then consider wrapping it in some other class.
 * @see Objects::Boolean
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
