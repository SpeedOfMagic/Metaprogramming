#pragma once

#include "../TL/type_list.h"

#include "graphs/pointer_structure_graph.h"

namespace GLib {
	/**
	* Finds node corresponding to this vertex.
	* @param vertex Template parameter, vertex, node of which to find.
	* @param graph Template parameter, graph that should be passed.
    * @returns Parameter result, required node if found, NullType otherwise.
	*/
	template<typename vertex, class graph>
	struct FindNodeByVertex {
		static_assert(graph::TYPE == POINTER_STRUCTURE, "Type of a graph is not a POINTER_STRUCTURE");

		template<class current_nodes>
		struct IterateThroughNode {
			using current_node = typename current_nodes::Head;
			using result = std::conditional_t<
				std::is_same<vertex, typename current_node::vertex>::value,
				current_node,
				typename IterateThroughNode<typename current_nodes::Tail>::result
			>;
		};

		template<>
		struct IterateThroughNode<EmptyTypeList> {
			using result = NullType;
		};

		using result = IterateThroughNode<typename graph::nodes_>;
	};

	template<typename vertex>
	struct FindNodeByVertex<vertex, EmptyTypeList> {
		using result = NullType;
	};
}