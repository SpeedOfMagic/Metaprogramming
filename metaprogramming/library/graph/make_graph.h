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
			typename TL::GenerateTypeLists<
			TL::Size<vertexes>::size
			>::result
		>;
	};

	/* Adjacency list */

	template<class vertexes, class adjacency_list>
	struct From<ADJACENCY_LIST, vertexes, adjacency_list> {
		using result = Graph<vertexes, adjacency_list>;
	};

	/* Adjacency matrix */

	template<class vertexes, class adjacency_matrix, size_t row, size_t col, bool has_edge>
	struct IterateThroughAdjacencyMatrix;

	template<class vertexes, class adjacency_matrix>
	struct From<ADJACENCY_MATRIX, vertexes, adjacency_matrix> {
		using result = typename IterateThroughAdjacencyMatrix<
			vertexes, adjacency_matrix,
			0, 0,
			typename TL::TypeAt<
				typename TL::TypeAt<adjacency_matrix, 0>::value, 
				0
			>::value
		>::result;
		static_assert(std::is_same<result, Graph>);
	};

	template<class vertexes, class adjacency_matrix, size_t row, size_t col>
	struct IterateThroughAdjacencyMatrix<vertexes, adjacency_matrix, row, col, true> {
		using result = typename GLib::MakeEdge<
			typename IterateThroughAdjacencyMatrix<
				vertexes, adjacency_matrix,
				row + (col + 1) / TL::Size<vertexes>::size, (col + 1) % TL::Size<vertexes>::size,
				typename TL::TypeAt<
					typename TL::TypeAt<adjacency_matrix, row>::value, 
					column + 1
				>::value
			>::result,
			typename TL::TypeAt<vertexes, row>::value,
			typename TL::TypeAt<vertexes, col>::value
		>::result;
	};

	template<class vertexes, class adjacency_matrix, size_t row, size_t col>
	struct IterateThroughAdjacencyMatrix<vertexes, adjacency_matrix, row, col, false> {
		using result = typename IterateThroughAdjacencyMatrix<
			vertexes,
			adjacency_matrix,
			row + (col + 1) / TL::Size<vertexes>::size, (col + 1) % TL::Size<vertexes>::size,
			typename TL::TypeAt<
				typename TL::TypeAt<
					adjacency_matrix, 
					row + (col + 1) / TL::Size<vertexes>::size
				>::value,
				(col + 1) % TL::Size<vertexes>::size
			>::value
		>::result;
	};

	template<class vertexes, class adjacency_matrix, size_t col, bool has_edge>
	struct IterateThroughAdjacencyMatrix<vertexes, adjacency_matrix, TL::Size<vertexes>::size, col, has_edge> {
		using result = Graph<vertexes, TL::GenerateTypeLists<TL::Size<vertexes>::size>>;
	};
}