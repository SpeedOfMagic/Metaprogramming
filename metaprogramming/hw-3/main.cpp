#include <iostream>
#include "../library/graph/graphs/graph.h"
#include "../library/graph/graphs/adjacency_list_graph.h"
#include "../library/graph/edge.h"
#include "../library/graph/graphs/edge_list_graph.h"
#include "../library/graph/GLib/get_reached_vertexes.h"
#include "../library/graph/convert/convert_to_adjacency_list.h"
#include "../library/graph/convert/convert_to_adjacency_matrix.h"
#include "../library/graph/convert/convert_to_edge_list.h"
#include "../library/graph/convert/convert_to_pointer_structure.h"
#include "../library/graph/GLib/get_nodes_from_roots.h"

#include "../library/TL/type_list.h"

int main() {
	using vertexes = TypeList<char, short, int, long, long long, float, double>;
	using edges = TypeList<
		Edge<char, short>, Edge<short, int>, Edge<int, long>, Edge<long, long long>,
		Edge<short, float>, Edge<float, double>, Edge<int, double>
	>;

	using v = TypeList<int, short, char>;
	using e = TypeList<
		Edge<char, short>, Edge<short, int>, Edge<int, char>
	>;
	using G = EdgeListGraph<v, e>;
	using GG = typename ConvertGraph<EDGE_LIST, ADJACENCY_MATRIX, G>::result;

	using g1 = EdgeListGraph<vertexes, edges>::ConvertTo<ADJACENCY_LIST>;
	using g2 = g1::result;
	using g3 = g2::ConvertTo<POINTER_STRUCTURE>;
	using g = g3::result;
	using gg = typename ConvertGraph<POINTER_STRUCTURE, EDGE_LIST, g>::result;
	using ggg = typename ConvertGraph<ADJACENCY_MATRIX, EDGE_LIST, GG>::result;

	gg go;
	ggg ggo;

	return 0;
}
