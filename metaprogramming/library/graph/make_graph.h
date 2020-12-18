#pragma once

#include "graph_type.h"
#include "graph.h"

#include "add_edge.h"
#include "edge.h"
#include "../TL/type_list.h"
#include "../TL/type_at.h"
#include "../TL/generate_type_lists.h"
#include "../TL/size.h"

/**
 * Methods to create graph from types, defined in @see GraphType
*/
namespace MakeGraph {
	/**
	 * Creates graph (V, E) with V = vertexes, E is defined by graph_type and edges
	 * @param graph_type Template parameter, how representation of edges looks like
	 * @param vertexes Template parameter, vertexes of a graph
	 * @param edge Template parameter, representation of edges
	 * @returns Parameter result, resulting graph
	*/
	template<GraphType graph_type, class vertexes, class edges>
	struct From;

	/**
	 * Creates graph from list of edges.
	 * @param vertexes Template parameter, vertexes of a graph
	 * @param edge Template parameter, TypeList of Edge
	 * @see Edge
	 * @returns Parameter result, resulting graph
	*/
	template<class vertexes, class edge_list>
	struct From<EDGE_LIST, vertexes, edge_list> {
		using result = typename GLib::AddEdge<
			typename From<EDGE_LIST, vertexes, typename edge_list::Tail>::result,
			typename edge_list::Head
		>::result;
	};

	/**
	 * @see From<EDGE_LIST, vertexes, edge_list>
	*/
	template<class vertexes>
	struct From<EDGE_LIST, vertexes, EmptyTypeList> {
		using result = Graph<
			vertexes,
			typename TL::GenerateTypeLists<TL::Size<vertexes>::size>::result
		>;
	};


	/**
	 * Creates graph from an adjacency list.
	 * @param vertexes Template parameter, vertexes of a graph
	 * @param edge Template parameter, adjacency list of a graph
	 * @returns Parameter result, resulting graph
	*/
	template<class vertexes, class adjacency_list>
	struct From<ADJACENCY_LIST, vertexes, adjacency_list> {
		using result = Graph<vertexes, adjacency_list>;
	};

	/**
	 * Creates graph from an adjacency matrix.
	 * @param vertexes Template parameter, vertexes of a graph
	 * @param adjacency_matrix Template parameter, adjacency matrix
	 *						   Recommended to be represented as a matrix of @see Objects::Boolean
	 * @returns Parameter result, resulting graph
	*/
	template<class vertexes, class adjacency_matrix>
	struct From<ADJACENCY_MATRIX, vertexes, adjacency_matrix> {
	private:
		template<int ind>
		struct IterateThroughAdjacencyMatrix {
			constexpr static size_t vertex_size = TL::Size<vertexes>::size;
			constexpr static size_t row = ind / vertex_size, col = ind % vertex_size;
			static_assert(row < vertex_size, "Index of a row is out of bounds");
			constexpr static bool has_edge = TL::TypeAt<
				typename TL::TypeAt<adjacency_matrix, row>::value,
				col
			>::value::value;

			using next_result = typename IterateThroughAdjacencyMatrix<ind - 1>::result;

			using result = std::conditional_t<has_edge,
				typename GLib::AddEdge<
				next_result,
				Edge<
				typename TL::TypeAt<vertexes, row>::value,
				typename TL::TypeAt<vertexes, col>::value
				>
				>::result,
				next_result
			>;
		};

		template<>
		struct IterateThroughAdjacencyMatrix<-1> {
			using result = Graph<vertexes, typename TL::GenerateTypeLists<TL::Size<vertexes>::size>::result>;
		};

		constexpr static size_t vertex_size = TL::Size<vertexes>::size;
		static_assert(TL::Size<vertexes>::size == TL::Size<adjacency_matrix>::size,
			"Rows of adjacency matrix don't match with amount of vertexes");
	public:
		using result = typename IterateThroughAdjacencyMatrix<vertex_size * vertex_size - 1>::result;
	};
}

