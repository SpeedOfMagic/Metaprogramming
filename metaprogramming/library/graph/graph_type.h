#pragma once

/**
 * Types, by which graph can be created
 * During the documentation, let n be amount of vertexes in graph
*/
enum GraphType {
	ADJACENCY_MATRIX,  //!< Graph is represented as an adjacency matrix of size n \times n
	ADJACENCY_LIST,  //!< Graph is represented as an adjacency list of size n
	EDGE_LIST,  //!< Graph is represented by a collection of edges
	POINTER_STRUCTURE  //!< Graph is represented by a pointer structure
};