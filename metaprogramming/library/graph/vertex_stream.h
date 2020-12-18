#pragma once

#include "../TL/type_list.h"
/*
template<class stream_, class graph>
struct VertexStream {
	using stream = stream_;

	
	template<class callable>
	struct ForEach {
		callable::typename execute<stream::Head>();
		typename VertexStream<typename stream::Tail, graph>::ForEach<typename stream::Head>;
	};
};

template<class graph>
struct VertexStream<EmptyTypeList, graph> {
	using stream = EmptyTypeList;

	template<class callable>
	struct ForEach {};
};
*//* Executes VertexCallable on every vertex in stream */