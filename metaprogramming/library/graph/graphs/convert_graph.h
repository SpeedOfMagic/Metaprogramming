#pragma once

#include "graph_type.h"

/**
* An adapter to convert graph of type From to type To.
* Defined separate from its realizations in order to avoid cycle dependency.
* Is used as a visitor in Visitor pattern.
* @see GraphType
* @param From Template parameter
* @param To Template parameter
* @param graph Template parameter
* @returns Parameter result, resulting graph.
*/
template<GraphType From, GraphType To, class graph>
struct ConvertGraph {};

template<GraphType type, class graph>
struct ConvertGraph<type, type, graph> {
	using result = graph;
};
