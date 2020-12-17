#pragma once

#include "../TL/type_list.h"

template<class stream_, class graph>
struct VertexStream {
	using stream = stream_;

	/* Executes VertexCallable on every vertex in stream */
	template<class callable>
	struct ForEach {
		callable::execute<stream::Head>();
		typename VertexStream<stream::Tail, graph>::ForEach<typename stream::Head>;
	};
};

template<class graph>
struct VertexStream<EmptyTypeList, graph> {
	using vertexes = EmptyTypeList;

	template<class callable>
	struct ForEach {};
};
