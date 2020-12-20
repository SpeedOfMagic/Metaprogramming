#pragma once

#include <type_traits>

#include "graphs/convert_graph.h"
#include "graphs/pointer_structure_graph.h"

#include "../TL/concatenate.h"
#include "../TL/reverse.h"

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
	template<class graph_raw, class start, class finish>
	struct FindPath {
		using graph = typename ConvertGraph<graph_raw::TYPE, POINTER_STRUCTURE, graph_raw>::result;

		using find_start = typename graph::FindNodeByVertex<start>;
		using start_node = typename find_start::result;

		using find_finish = typename graph::FindNodeByVertex<finish>;
		using finish_node = typename find_finish::result;
		
		using dfs_search = typename graph::DFS<start_node>::result;
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