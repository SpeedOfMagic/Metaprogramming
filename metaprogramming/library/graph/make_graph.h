#pragma once

#include "graph_type.h"
#include "graph.h"

#include "add_edge.h"
#include "../TL/type_list.h"
#include "../TL/type_at.h"
#include "../TL/generate_type_lists.h"
#include "../TL/size.h"

#include "add_edge.h"

namespace MakeGraph {
	template<GraphType graph_type, class vertexes, class edges>
	struct From;

	/* Edge list */

	template<class vertexes, class edge_list>
	struct From<EDGE_LIST, vertexes, edge_list> {
		using result = typename GLib::AddEdge<
			typename From<EDGE_LIST, vertexes, typename edge_list::Tail>::result,
			typename edge_list::Head
		>::result;
	};

	template<class vertexes>
	struct From<EDGE_LIST, vertexes, EmptyTypeList> {
		using result = Graph<
			vertexes,
			typename TL::GenerateTypeLists<TL::Size<vertexes>::size>::result
		>;
	};

	/* Adjacency list */

	template<class vertexes, class adjacency_list>
	struct From<ADJACENCY_LIST, vertexes, adjacency_list> {
		using result = Graph<vertexes, adjacency_list>;
	};

	/* Adjacency matrix */

	template<class vertexes, class adjacency_matrix, int ind>
	struct IterateThroughAdjacencyMatrix;

	template<class vertexes, class adjacency_matrix>
	struct From<ADJACENCY_MATRIX, vertexes, adjacency_matrix> {
		constexpr static size_t vertex_size = TL::Size<vertexes>::size;
		static_assert(TL::Size<vertexes>::size == TL::Size<adjacency_matrix>::size,
			 "Rows of adjacency matrix don't match with amount of vertexes");
		using result = typename IterateThroughAdjacencyMatrix<vertexes, adjacency_matrix, vertex_size * vertex_size - 1>::result;
	};

	template<class vertexes, class adjacency_matrix, int ind>
	struct IterateThroughAdjacencyMatrix {
		constexpr static size_t vertex_size = TL::Size<vertexes>::size;
		constexpr static size_t row = ind / vertex_size, col = ind % vertex_size;
		static_assert(row < vertex_size, "Index of a row is out of bounds");
		constexpr static bool has_edge = TL::TypeAt<
			typename TL::TypeAt<adjacency_matrix, row>::value,
			col
		>::value::value;

		using next_result = typename IterateThroughAdjacencyMatrix<vertexes, adjacency_matrix, ind - 1>::result;

		using result = std::conditional_t<has_edge,
			typename GLib::MakeEdge<
				next_result,
				typename TL::TypeAt<vertexes, row>::value,
				typename TL::TypeAt<vertexes, col>::value
			>::result,
			next_result
		>;
	};

	template<class vertexes, class adjacency_matrix>
	struct IterateThroughAdjacencyMatrix<vertexes, adjacency_matrix, -1> {
		using result = Graph<vertexes, typename TL::GenerateTypeLists<TL::Size<vertexes>::size>::result>;
	};
}

