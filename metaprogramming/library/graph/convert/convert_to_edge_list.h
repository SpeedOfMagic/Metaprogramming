#pragma once

#include "convert_graph.h"

#include "../../TL/add.h"
#include "../../TL/concatenate.h"
#include "../../TL/size.h"
#include "../../TL/type_list.h"

#include "../GLib/add_edge.h"

#include "../graphs/adjacency_list_graph.h"
#include "../graphs/adjacency_matrix_graph.h"
#include "../graphs/edge_list_graph.h"
#include "../graphs/pointer_structure_graph.h"
#include "../graphs/graph_type.h"

#include "../edge.h"
#include "../objects.h"

/**
 * @see ConvertGraph
 */
template<class graph>
struct ConvertGraph<POINTER_STRUCTURE, EDGE_LIST, graph> {
	static_assert(POINTER_STRUCTURE == graph::TYPE, "Type of a graph must be equal to passed argument");

	template<class cur_nodes>
	struct IterateThroughNodes {
		using tail_call = IterateThroughNodes<typename cur_nodes::Tail>;
		using cur_node = typename cur_nodes::Head;
		static_assert(TL::Contains<typename graph::nodes_, cur_node>::value, "asdsd");

		using vertexes = typename TL::Add<
			typename cur_node::vertex,
			0,
			typename tail_call::vertexes
		>::result;

		using edges = typename TL::Concatenate<
			typename cur_node::children,
			typename tail_call::edges
		>::result;
	};

	template<>
	struct IterateThroughNodes<EmptyTypeList> {
		using vertexes = EmptyTypeList;
		using edges = EmptyTypeList;
	};

	using iterate_result = IterateThroughNodes<typename graph::nodes_>;

	using result = EdgeListGraph<
		typename iterate_result::vertexes,
		typename iterate_result::edges
	>;
};

/**
 * @see ConvertGraph
 */
template<class graph>
struct ConvertGraph<ADJACENCY_MATRIX, EDGE_LIST, graph> {
	static_assert(ADJACENCY_MATRIX == graph::TYPE, "Type of a graph must be equal to passed argument");

	using vertexes = typename graph::vertexes_;
	constexpr static int n = TL::Size<vertexes>::size;

	template<int cur_index>
	struct IterateThroughMatrix {
		constexpr static int row = cur_index / n, col = cur_index % n;

		using from = typename TL::TypeAt<vertexes, row>::value;
		using to = typename TL::TypeAt<vertexes, col>::value;

		using cell = typename TL::TypeAt<
			typename TL::TypeAt<typename graph::matrix_, row>::value,
			col
		>::value;
		using weight = std::conditional_t<
			std::is_same<Objects::Boolean<true>, cell>::value,
			NullType,
			cell
		>;

		using tail_result = typename IterateThroughMatrix<cur_index - 1>::result;

		using result = std::conditional_t<
			std::is_same<Objects::Boolean<false>, cell>::value,
			tail_result,
			typename TL::Add<
				Edge<from, to, weight>,
				0,
				tail_result
			>::result
		>;
	};

	template<>
	struct IterateThroughMatrix<-1> {
		using result = EmptyTypeList;
	};

	using edges = typename IterateThroughMatrix<n * n - 1>::result;
	using result = EdgeListGraph<vertexes, edges>;
};

