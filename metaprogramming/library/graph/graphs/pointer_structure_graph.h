#pragma once

#include "graph.h"

#include "../../TL/concatenate.h"
#include "../../TL/is_type_list.h"
#include "../../TL/remove.h"

/** 
 * Represents graph as a structure with pointers
 * Every vertex must be contained within node. Node must have a TypeList ''children'', 
 * which is a TypeList of Edges, showing who can be reached from this vertex.
 * Also node must have a field ''vertex'' ~--- the vertex this node contains.
 * @param vertexes Template parameter, vertexes in this graph
 */
template<class nodes>
struct PointerStructureGraph : public Graph {
	constexpr static GraphType TYPE = POINTER_STRUCTURE;

	static_assert(TL::IsTypeList<nodes>::value, "Passed vertexes are not in a TypeList");
	using nodes_ = nodes;  //!< All accounted vertexes in this graph

	/**
	 * Performs Depth-First Search, starting from passed vertex.
	 * It doesn't visit vertexes that have been visited already. 
	 * It returns visited edges in chronological order, from which it's easy to deduce DFS.
	 * It's more versatile than one may think)
	 * Also a variation of Composite pattern.
	 * @param starting_vertex Template parameter, starting vertex of DFS.
	 * @returns Parameter result, TypeList of visited edges in chronological order.
	*/
	template<class current_vertex, class unvisited_vertexes = nodes_>
	struct DFS {
		using vertexes_to_visit = typename TL::Remove<unvisited_vertexes, current_vertex>::result;

		template<class current_children, class cur_unvisited>
		struct IterateThroughChildren {
			using cur_edge = typename current_children::Head;
			using cur_child = typename cur_edge::to;

			template<bool is_visited>
			struct FilterByVisited;

			template<>
			struct FilterByVisited<true> {
				using dfs = DFS<cur_child, vertexes_to_visit>;
				using new_visited = typename dfs::new_visited;

				using result = typename TL::Concatenate<
					typename dfs::result,
					typename IterateThroughChildren<
						typename current_children::Tail,
						new_visited
					>::result
				>::result;
			};

			template<>
			struct FilterByVisited<false> {
				using new_visited = vertexes_to_visit;
				using result = typename IterateThroughChildren<
					typename current_children::Tail,
					new_visited
				>::result;
			};

			using filter_by_visited = FilterByVisited<
				TL::Contains<cur_unvisited, cur_child>::result
			>;
			using result = typename filter_by_visited::result;
			using new_visited = typename filter_by_visited::new_visited;
		};

		template<class cur_unvisited>
		struct IterateThroughChildren<EmptyTypeList, cur_unvisited> {
			using result = EmptyTypeList;
			using new_visited = vertexes_to_visit;
		};

		using iterate_through_children = IterateThroughChildren<
			typename current_vertex::children, 
			vertexes_to_visit
		>;
		using new_visited = typename iterate_through_children::new_visited;
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
			PointerStructureGraph<nodes>
		>::result;
	};

	/**
	 * Finds node corresponding to this vertex.
	 * @param vertex Template parameter, vertex, node of which to find.
	 * @param current_nodes Optional template parameter, TypeList of possible nodes. nodes_ by default.
	 * @returns Parameter result, required node if found, NullType otherwise.
	 */
	template<typename vertex, class current_nodes = nodes_>
	struct FindNodeByVertex {
		using current_node = typename current_nodes::Head;
		using result = std::conditional_t<
			std::is_same<vertex, typename current_node::vertex>::value,
			current_node,
			typename FindNodeByVertex<vertex, typename current_nodes::Tail>::result
		>;
	};

	template<typename vertex>
	struct FindNodeByVertex<vertex, EmptyTypeList> {
		using result = NullType;
	};
};
