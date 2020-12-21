#include <iostream>
#include "../library/graph/graphs/adjacency_list_graph.h"

#include "../library/graph/graphs/edge_list_graph.h"

#include "../library/graph/GLib/for_each.h"

#include "../library/graph/edge.h"
#include "../library/graph/process_vertex.h"
#include "../library/graph/objects.h"

template<class graph, typename vertex>
struct ProcessVertex<42, graph, vertex> {
	constexpr static int result = vertex::value;
};

using Objects::Integer;

int main() {
	using vertexes = TypeList<Integer<1>, Integer<2>, Integer<4>>;
	using edges = TypeList<TypeList<Integer<1>, Integer<2>>>;
	using graph = EdgeListGraph<vertexes, edges>;

	using result = typename GLib::ForEach<42, graph>::result;
	// result contains three objects of type ProcessVertex<42, graph, ...>, their results are 1, 2, 4

	std::cout << TL::TypeAt<result, 2>::value::result << std::endl;  // 4

	return 0;
}
