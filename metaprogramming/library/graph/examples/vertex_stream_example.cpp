#include <iostream>
#include "../graphs/adjacency_list_graph.h"

#include "../graphs/edge_list_graph.h"

#include "../GLib/filter.h"
#include "../GLib/for_each.h"

#include "../edge.h"
#include "../process_vertex.h"
#include "../objects.h"

// Returns true if number on a vertex is bigger than amount of edges in graph
template<class graph, typename vertex>
struct ProcessVertex<34, graph, vertex> { 
	constexpr static int number = vertex::value;
	constexpr static int edge_count = TL::Size<typename graph::edges_>::size;
	constexpr static bool result = number > edge_count;
};

// Converts vertex to its number
template<class graph, typename vertex>
struct ProcessVertex<42, graph, vertex> {
	constexpr static int result = vertex::value;
};

using Objects::Integer;

int main() {
	using vertexes = TypeList<Integer<1>, Integer<2>, Integer<4>>;
	using edges = TypeList<Edge<Integer<1>, Integer<2>>>;
	using graph = EdgeListGraph<vertexes, edges>;

	using filtered = typename GLib::Filter<34, graph>::result;  // fitlered contains vertexes 2 and 4
	using result = typename GLib::ForEach<42, graph, filtered>::result;
	// result contains two objects of type ProcessVertex<42, graph, ...>, their results are 2, 4

	std::cout << result::Head::result + result::Tail::Head::result << std::endl;  // 2 + 4 = 6

	return 0;
}

