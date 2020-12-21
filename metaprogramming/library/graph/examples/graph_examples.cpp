#include "../graphs/adjacency_list_graph.h"
#include "../graphs/adjacency_matrix_graph.h"
#include "../graphs/edge_list_graph.h"
#include "../graphs/pointer_structure_graph.h"

#include "../edge.h"
#include "../objects.h"
#include "../graphs/pointer_structure_node.h"

using Objects::Boolean;

int main() {
	/* Graph looks like this:
	   ----> int ----|
	  /             \|/
	char --------> double
	  \             /|\
	   ---> float ---|
	*/

	using vertexes = TypeList<char, int, float, double>;

	// Adjacency list
	{
		using adjacency_list = TypeList<
			TypeList<Edge<char, int>, Edge<char, float>, Edge<char, double>>,
			TypeList<Edge<int, double>>,
			TypeList<Edge<float, double>>,
			TypeList<>
		>;
		using adjacency_list_graph = AdjacencyListGraph<vertexes, adjacency_list>;
	}

	// Adjacency matrix
	{
		using matrix = TypeList<
			TypeList<Boolean<false>, Boolean<true>,  Boolean<true>,  Boolean<true>>,
			TypeList<Boolean<false>, Boolean<false>, Boolean<false>, Boolean<true>>,
			TypeList<Boolean<false>, Boolean<false>, Boolean<false>, Boolean<true>>,
			TypeList<Boolean<false>, Boolean<false>, Boolean<false>, Boolean<false>>
		>;
		using adjacency_matrix_graph = AdjacencyMatrixGraph<vertexes, matrix>;
	}

	// Edge list
	{
		using edges = TypeList<
			Edge<char, int>, Edge<char, float>, Edge<char, double>,
			Edge<int, double>, Edge<float, double>
		>;
		using edge_list_graph = EdgeListGraph<vertexes, edges>;
	}

	// Pointer structure
	{
		using nodes = TypeList<
			PointerStructureNode<char, TypeList<Edge<char, int>, Edge<char, float>, Edge<char, double>>>,
			PointerStructureNode<int, TypeList<Edge<int, double>>>,
			PointerStructureNode<float, TypeList<Edge<float, double>>>,
			PointerStructureNode<double, TypeList<>>
		>;
		using pointer_structure_node = PointerStructureGraph<nodes>;
	}

	return 0;
}