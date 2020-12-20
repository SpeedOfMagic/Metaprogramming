#pragma once

#include "../../TL/is_type_list.h"

/**
 * Default version of a suitable class for PointerStructureGraph.
 * It's not necessary to use this one. In fact, it's encouraged to make your objects suitable to PointerStructureGraph.
 * It can be done by adding field ''children'' to every vertex in the graph.
 * @param vertex_ Template parameter, vertex that this node represents
 * @param children_ Template parameter, TypeList of Edges, showing who can be reached from this vertex.
 */
template<class vertex_, class children_>
struct PointerStructureNode {
	static_assert(TL::IsTypeList<children_>::value, "Passed children are not in a TypeList");
	using vertex = vertex_;
	using children = children_;
};
