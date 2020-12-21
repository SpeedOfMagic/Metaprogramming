#pragma once

#include "graph.h"

#include "../../TL/concatenate.h"
#include "../../TL/is_type_list.h"
#include "../../TL/remove.h"

#include "../GLib/find_node_by_vertex.h"

#include "pointer_structure_node.h"

#include "../convert/convert_graph.h"

/** 
 * Represents graph as a structure with pointers
 * Every vertex must be contained within node. Node must have a TypeList ''children'', 
 * which is a TypeList of Edges, showing who can be reached from this vertex.
 * Also node must have a field ''vertex'' ~--- the vertex this node contains.
 * @param nodes Template parameter, nodes in this graph
 */
template<class nodes>
struct PointerStructureGraph : public Graph {
	constexpr static GraphType TYPE = POINTER_STRUCTURE;

	static_assert(TL::IsTypeList<nodes>::value, "Passed vertexes are not in a TypeList");
	using nodes_ = nodes;  //!< All accounted vertexes in this graph

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
			PointerStructureGraph<nodes>
		>::result;
	};
};
