#include <iostream>
#include "../library/graph/graph.h"
#include "../library/TL/type_list.h"
#include "../library/graph/add_edge.h"
#include "../library/graph/graph_type.h"
#include "../library/graph/make_graph.h"
#include "../library/graph/objects.h"
#include "../library/functor_type.h"
#include "../library/graph/vertex_stream.h"
#include "../library/functor.h"

#include "../library/graph/edge.h"

template<class Gr>
void print(Gr g, size_t ind) {
	std::cout << ind << std::endl;
}


using Objects::Integer;
using Objects::Boolean;

int main() {
	using vertexes = TypeList<char, short, int, long, long long, float, double>;
	using edges = TypeList<
		Edge<char, short>, Edge<short, int>, Edge<int, long>, Edge<long, long long>,
		Edge<short, float>, Edge<float, double>, Edge<int, double>
	>;
	using graph = MakeGraph::From<EDGE_LIST, vertexes, edges>::result;
	std::cout << graph().HasEdge<Edge<short, float>>() << std::endl;
	std::cout << graph().HasEdge<Edge<int, long long>>() << std::endl;
	using new_graph = typename GLib::AddEdge<graph, Edge<int, long long>>::result;
	new_graph g = new_graph();
	std::cout << 1 + new_graph().HasEdge<Edge<int, long long>>() << std::endl;

	using g2 = MakeGraph::From<ADJACENCY_MATRIX, TypeList<Integer<1>, Integer<2>, Integer<4>>, 
		TypeList<
			TypeList<Boolean<false>, Boolean<true>, Boolean<false>>,
			TypeList<Boolean<false>, Boolean<false>, Boolean<true>>,
			TypeList<Boolean<true>, Boolean<false>, Boolean<false>>
		>
	>::result;
	g2 gg = g2();
	std::cout << g2().HasEdge<Edge<Integer<2>, Integer<4>>>() << std::endl;
	std::cout << g2().HasEdge<Edge<Integer<4>, Integer<2>>>() << std::endl;





	Functor<void(Class<g2>, size_t)> f(print<Class<g2>>);
	VertexStream<g2::vertexes_, g2> str;
	str.ForEach(f);


	return 0;
}
