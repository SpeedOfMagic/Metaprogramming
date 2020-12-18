#pragma once

#include "../TL/type_list.h"
#include "../class.h"

template<class stream, class graph>
struct VertexStream {
	using stream_ = stream;

	template<class Functor>
	void ForEach(const Functor& functor) {
		functor(Class<stream::Head>(), Class<graph>());
		VertexStream<stream::Tail, graph>(functor);
	}
};

template<class graph>
struct VertexStream<EmptyTypeList, graph> {
	using stream = EmptyTypeList;

	template<class Functor>
	void ForEach(const Functor& functor) {}
};