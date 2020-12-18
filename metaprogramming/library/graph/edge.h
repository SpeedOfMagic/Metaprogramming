#pragma once

#include "../TL/null_type.h"

/**
 * Represents an edge in the graph.
 * @param from_ Template parameter, starting vertex of an edge
 * @param to_ Template parameter, ending vertex of an edge
 * @param weight_ Template parameter, additional property of an edge
*/
template<typename from_, typename to_, typename weight_ = NullType>
struct Edge {
	using from = from_;  //!< Starting vertex of an edge
	using to = to_;  //!< Ending vertex of an edge
	using weight = weight_;  //!< Additional property of an edge
};
