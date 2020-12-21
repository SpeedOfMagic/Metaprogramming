#pragma once

#include "../graphs/graph_type.h"

/**
* An adapter to convert graph of type From to type To.
* Defined separate from its realizations in order to avoid cycle dependency.
* Before convertion, don't forget to include file of a required implementation.
* Is used as a visitor in Visitor pattern.
* @see GraphType
* @param From Template parameter
* @param To Template parameter
* @param graph Template parameter
* @returns Parameter result, resulting graph.
*/
template<GraphType From, GraphType To, class graph>
struct ConvertGraph;

template<GraphType type, class graph>
struct ConvertGraph<type, type, graph> {
	static_assert(type == graph::TYPE, "Type of a graph must be equal to passed argument");
	using result = graph;
};
