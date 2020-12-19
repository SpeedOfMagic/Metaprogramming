#pragma once

#include "graph_type.h"

template<GraphType From, GraphType To, class graph>
struct ConvertGraph {
	using result = int;
};

