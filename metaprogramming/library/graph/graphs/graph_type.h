#pragma once

/**
 * Types, by which graph can be created.
 * For more details, see corresponding file.
 * @see AdjacencyMatrixGraph
 * @see AdjacencyListGraph
 * @see EdgeListGraph
 * @see PointerStructureGraph
 */
enum GraphType {
	ADJACENCY_MATRIX,  //!< Graph is represented as an adjacency matrix of booleans.
	ADJACENCY_LIST,  //!< Graph is represented as an adjacency list (TypeList of TypeLists of edges).
	EDGE_LIST,  //!< Graph is represented by a collection of edges.
	POINTER_STRUCTURE  //!< Graph is represented by a pointer structure.
};