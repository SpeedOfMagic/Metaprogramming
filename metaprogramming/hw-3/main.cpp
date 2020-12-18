#include <iostream>
#include "../library/graph/graph.h"
#include "../library/TL/type_list.h"
#include "../library/graph/add_edge.h"
#include "../library/graph/graph_type.h"
#include "../library/graph/make_graph.h"
#include "../library/graph/objects.h"
#include "calculate_vertex_count.h"
#include "../library/graph/vertex_stream.h"
#include "../library/functor.h"

int f(int a, int b) { return a + b; }


struct Obj {
	int d = 0;

	void Add() { ++d; }
};

int main() {
	Obj o1, o2;


	Functor<void(Obj)> f(&Obj::Add);
	f(&o1); f(&o1); f(&o2);
	std::cout << o1.d << " " << o2.d << std::endl;

	using vertexes = TypeList<char, short, int, long, long long, float, double>;
	using edges = TypeList<
		TypeList<char, short>, TypeList<short, int>, TypeList<int, long>, TypeList<long, long long>,
		TypeList<short, float>, TypeList<float, double>, TypeList<int, double>
	>;
	using graph = MakeGraph::From<EDGE_LIST, vertexes, edges>::result;
	std::cout << graph().VertexCount() << std::endl;
	std::cout << graph().HasEdge<short, float>() << std::endl;
	std::cout << graph().HasEdge<int, long long>() << std::endl;
	using new_graph = typename GLib::MakeEdge<graph, int, long long>::result;
	new_graph g = new_graph();
	std::cout << 1 + new_graph().HasEdge<int, long long>() << std::endl;

	using g2 = MakeGraph::From<ADJACENCY_MATRIX, TypeList<Integer<1>, Integer<2>, Integer<4>>, 
		TypeList<
			TypeList<Boolean<false>, Boolean<true>, Boolean<false>>,
			TypeList<Boolean<false>, Boolean<false>, Boolean<true>>,
			TypeList<Boolean<true>, Boolean<false>, Boolean<false>>
		>
	>::result;
	g2 gg = g2();
	std::cout << g2().HasEdge<Integer<2>, Integer<4>>() << std::endl;
	std::cout << g2().HasEdge<Integer<4>, Integer<2>>() << std::endl;

	//using calc = CalculateVertexCount::execute;
	//VertexStream<g2::vertexes, g2>::ForEach<calc>;

	//std::cout << calc::result << std::endl;

	return 0;
}
