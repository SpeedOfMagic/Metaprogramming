#pragma once

#include <type_traits>

#include "../TL/concatenate.h"
#include "../TL/reverse.h"

#include "find_node_by_vertex.h"
#include "dfs.h"

#include "graphs/convert_graph.h"
#include "graphs/convert_from_adjacency_list.h"
#include "graphs/convert_from_edge_list.h"
#include "graphs/convert_from_pointer_structure.h"

namespace GLib {
	/**
	* Finds path in graph between vertexes start and finish.
	* @param graph Template parameter
	* @param start Template parameter
	* @param finish Template parameter
	* @returns Two parameters: path and weights. ''path'' is a TypeList of vertexes that make this path. 
	*		   ''weights'' is a TypeList of weights, that were on the edges in this path.
	*		   If there's no path, path and weights are EmptyTypeList.
	*/
	template<class graph_raw, typename start, typename finish>
	struct FindPath {
		using graph = typename ConvertGraph<graph_raw::TYPE, POINTER_STRUCTURE, graph_raw>::result;

		using start_node = typename FindNodeByVertex<start, graph>::result;
		using finish_node = typename FindNodeByVertex<finish, graph>::result;
		
		using dfs_search = typename DFS<start_node, graph>::result;
		using reversed = typename TL::Reverse<dfs_search>::result;
		
		template<class cur_edges, class wanted>
		struct IterateThroughEdges {
			constexpr static bool found = std::is_same<typename cur_edges::Head::to, wanted>::value;

			using path = typename std::conditional_t<found,
				typename TL::Add<
					wanted,
					0,
					typename IterateThroughEdges<
						typename cur_edges::Tail, 
						typename cur_edges::Head::From
					>::path
				>,
				typename IterateThroughEdges<typename cur_edges::Tail, wanted>::path
			>;

			using weights = typename std::conditional_t<found,
				typename TL::Add<
					wanted,
					0,
					typename IterateThroughEdges<
						typename cur_edges::Tail,
						typename cur_edges::Head::weight
					>::weights
				>,
				typename IterateThroughEdges<typename cur_edges::Tail, wanted>::weights
			>;
		};

		template<class wanted>
		struct IterateThroughEdges<EmptyTypeList, wanted> {
			using path = EmptyTypeList;
			using weights = EmptyTypeList;
		};

		using iterate_through_edges = IterateThroughEdges<reversed, finish_node>;
		using path = typename iterate_through_edges::path;
		using weights = typename iterate_through_edges::weights;
	};
}
