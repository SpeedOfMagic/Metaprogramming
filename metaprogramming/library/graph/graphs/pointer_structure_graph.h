#pragma once

#include "graph.h"

#include "../../TL/is_type_list.h"

template<class starting_vertexes>
struct PointerStructureGraph : public Graph {
	static_assert(TL::IsTypeList<starting_vertexes>::value, "Passed vertexes are not in a TypeList");
	using starting_vertexes_ = starting_vertexes;

	template<class vertex_, class children_>
	struct Node {
		static_assert(TL::IsTypeList<children_>::value, "Passed children are not in a TypeList");
		using vertex = vertex_;
		using children = children_;
	};
};
