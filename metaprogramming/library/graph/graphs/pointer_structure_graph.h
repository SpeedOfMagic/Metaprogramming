#pragma once

#include "graph.h"

#include "../../TL/concatenate.h"
#include "../../TL/is_type_list.h"
#include "../../TL/remove.h"

/** 
 * Represents graph as a structure with pointers
 * Every vertex must contain TypeList ''children'', 
 * which is a TypeList of Edges, showing who can be reached from this vertex.
 * @param vertexes Template parameter, vertexes in this graph
 */
template<class vertexes>
struct PointerStructureGraph : public Graph {
	constexpr static GraphType TYPE = POINTER_STRUCTURE;

	static_assert(TL::IsTypeList<vertexes>::value, "Passed vertexes are not in a TypeList");
	using vertexes_ = vertexes;  //!< All accounted vertexes in this graph

	/** 
	 * Default version of a suitable class.
	 * It's not necessary to use this one. In fact, it's encouraged to make your objects suitable to PointerStructureGraph.
	 * @param vertex_ Template parameter, vertex that this node represents
	 * @param children_ Template parameter, TypeList of Edges, showing who can be reached from this vertex.
	 */
	template<class vertex_, class children_>
	struct Node {
		static_assert(TL::IsTypeList<children_>::value, "Passed children are not in a TypeList");
		using vertex = vertex_;
		using children = children_;
	};

	/**
	 * Performs Depth-First Search, starting from passed vertex.
	 * It doesn't visit vertexes that have been visited already. 
	 * It returns visited edges in chronological order, from which it's easy to deduce DFS.
	 * It's more versatile than one may think)
	 * Also a variation of Composite pattern.
	 * @param starting_vertex Template parameter, starting vertex of DFS.
	 * @returns Parameter result, TypeList of visited edges in chronological order.
	*/
	template<class current_vertex, class unvisited_vertexes = vertexes_>
	struct DFS {
		using vertexes_to_visit = typename TL::Remove<unvisited_vertexes, current_vertex>::result;

		template<class current_children>
		struct IterateThroughChildren {

			template<bool is_visited>
			struct FilterByVisited;

			template<>
			struct FilterByVisited<true> {
				using dfs = DFS<typename current_children::Head, vertexes_to_visit>;
				using new_visited = typename dfs::new_visited;

				using result = typename TL::Concatenate<
					typename dfs::result,
					typename IterateThroughChildren<typename current_children::Tail>::result
				>::result;
			};

			template<>
			struct FilterByVisited<false> {
				using new_visited = vertexes_to_visit;
				using result = typename IterateThroughChildren<typename current_children::Tail>::result;
			};

			using filter_by_visited = typename FilterByVisited<
				TL::Contains<vertexes_to_visit, typename current_children::Head>::value
			>;
			using result = typename filter_by_visited::result;
			using new_visited = typename filter_by_visited::new_visited;
		};

		template<>
		struct IterateThroughChildren<EmptyTypeList> {
			using result = EmptyTypeList;
			using new_visited = vertexes_to_visit;
		};

		using iterate_through_children = typename IterateThroughChildren<typename current_vertex::children>;
		using new_visited = typename iterate_through_children::visited;
		using result = typename iterate_through_children::result;
	};

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
			PointerStructureGraph<vertexes>
		>::result;
	};
};
