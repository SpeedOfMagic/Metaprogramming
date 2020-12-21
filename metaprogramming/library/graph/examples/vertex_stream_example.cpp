#include <functional>
#include <iostream>

#include "../edge.h"
#include "../objects.h"
#include "../stream.h"

#include "../graphs/edge_list_graph.h"
#include "../stream_functor_type.h"
#include "../vertex_stream.h"
#include "../stream.h"

using Objects::Integer;

template<class graph>
bool IsAmongFirst3(size_t vertex_ind) {
	return vertex_ind < 3;
}

template<class graph>
int Add1(size_t vertex_ind) {
	return vertex_ind + 1;
}

int main() {
	using graph = AdjacencyListGraph<
		TypeList<Integer<1>, Integer<2>, Integer<3>, Integer<4>, Integer<5>>,
		TypeList<
		TypeList<Edge<Integer<1>, Integer<2>>>,
		TypeList<Edge<Integer<2>, Integer<1>>, Edge<Integer<2>, Integer<3>>>,
		TypeList<Edge<Integer<3>, Integer<4>>>,
		TypeList<Edge<Integer<4>, Integer<3>>, Edge<Integer<4>, Integer<5>>>,
		TypeList<Edge<Integer<5>, Integer<4>>>
		>
	>;


	StreamFunctorType::Predicate<graph> predicate(IsAmongFirst3<graph>);
	StreamFunctorType::Function<graph, int> function(Add1<graph>);

	using stream = VertexStream<typename graph::vertexes_, graph>;
	Stream<size_t> indexes = stream::MapVertexesToIndexes();
	int sum = indexes                       // indexes = {0, 1, 2, 3, 4}
		.Filter(predicate)                  // indexes = {0, 1, 2}
		.Map<int>(function)                 // sum = {1, 2, 3}
		.Reduce<int>(std::plus<int>(), 0);  // sum = 6
	std::cout << sum << std::endl;
}