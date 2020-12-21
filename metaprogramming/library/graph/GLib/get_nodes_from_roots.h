#pragma once

#include "dfs.h"

namespace GLib {
	/**
	* Gets all nodes that can be reached from roots.
	* It's a good way to get full structure of a graph without entering every node.
	* @param nodes Template parameter, initial nodes.
	* @returns Parameter result, nodes for bui
	*/
	template<class nodes, class graph>
	struct GetNodesFromRoots {
		using tail_result = typename GetNodesFromRoots<typename nodes::Tail, graph>::result;

		using new_visited = typename DFS<
			typename nodes::Head,
			graph,
			tail_result
		>::new_visited;

		using result = typename TL::Concatenate<new_visited, tail_result>::result;
	};

	/**
	* @see GetNodesFromRoots
	*/
	template<class graph>
	struct GetNodesFromRoots<EmptyTypeList, graph> {
		using result = EmptyTypeList;
	};
}