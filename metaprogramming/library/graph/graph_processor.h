#pragma once

#include "../library/functor.h"

template<typename VertexType>
class GraphProcessor {
	virtual void GoTo(VertexType new_vertex) = 0;
};