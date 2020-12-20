#include <iostream>
#include "../library/graph/graphs/graph.h"
#include "../library/graph/graphs/adjacency_list_graph.h"
#include "../library/TL/type_list.h"
#include "../library/graph/add_edge.h"
#include "../library/graph/graphs/graph_type.h"
#include "../library/graph/objects.h"
#include "../library/functor_type.h"
#include "../library/graph/graphs/edge_list_graph.h"
#include "../library/graph/vertex_stream.h"
#include "../library/functor.h"
#include "../library/graph/graphs/graph_type.h"
#include "../library/graph/graphs/convert_from_edge_list.h"
#include "../library/graph/graphs/convert_from_adjacency_list.h"
#include "../library/graph/graphs/convert_from_pointer_structure.h"
#include "../library/graph/edge.h"
#include "../library/graph/find_path.h"

template<class Gr>
void print(Gr g, size_t ind) {
	std::cout << ind + 1 << std::endl;
}



using Objects::Integer;
using Objects::Boolean;

using std::cout;
using std::endl;

int main() {
	using vertexes = TypeList<char, short, int, long, long long, float, double>;
	using edges = TypeList<
		Edge<char, short>, Edge<short, int>, Edge<int, long>, Edge<long, long long>,
		Edge<short, float>, Edge<float, double>, Edge<int, double>
	>;

	using graph = EdgeListGraph<vertexes, edges>;
	//std::cout << graph().HasEdge<Edge<short, float>>() << std::endl;

	using graph2 = EdgeListGraph<vertexes, edges>
		::ConvertTo<ADJACENCY_LIST>::result;

	using g3 = graph2
		::ConvertTo<POINTER_STRUCTURE>::result;
 
	graph2 g2; g3 gs;

	using path = typename GLib::FindPath<graph2, char, long>::path;
	cout << TL::Size<path>::size << endl;
	
		//::ConvertTo<ADJACENCY_MATRIX>::result
		//::ConvertTo<EDGE_LIST>::result
		//::ConvertTo<ADJACENCY_LIST>::result;

	//std::cout << graph2().HasEdge<Edge<float, double>>() << std::endl;

	return 0;
}
