#pragma once

#include "../TL/contains.h"
#include "../TL/index_of.h"
#include "../TL/size.h"
#include "../TL/type_at.h"
#include "../TL/type_list.h"

template<class vertexes_, class adjacency_list_>
struct Graph {
	using vertexes = vertexes_;
	using adjacency_list = adjacency_list_;
	static_assert(TL::Size<vertexes>::size == TL::Size<adjacency_list>::size, "Amount of vertexes and adjacency lists differ");

	constexpr int VertexCount() {
		return TL::Size<vertexes>::size;
	}

	template<typename from, typename to>
	constexpr bool HasEdge() {
		constexpr int vertex_num = TL::IndexOf<vertexes, from>::value;
		using adjacent_vertexes = typename TL::TypeAt<adjacency_list, vertex_num>::value;
		return TL::Contains<adjacent_vertexes, to>::result;
	}
};
