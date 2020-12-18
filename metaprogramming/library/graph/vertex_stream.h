#pragma once

#include "../TL/type_list.h"
#include "../class.h"

template<class stream, class graph>
struct VertexStream {
	using stream_ = stream;

	template<class Functor>
	void ForEach(Functor functor) {
		constexpr size_t vertex_index = TL::IndexOf<typename graph::vertexes, typename stream::Head>::value;
		functor(Class<graph>(), vertex_index);
		VertexStream<typename stream::Tail, graph>().ForEach(functor);
	}
};

template<class graph>
struct VertexStream<EmptyTypeList, graph> {
	using stream = EmptyTypeList;

	template<class Functor>
	void ForEach(Functor functor) {}
};
