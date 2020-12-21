#pragma once

/**
* Processes vertex in a given graph.
* id represents unique key to implementation of this struct.
* Id is used to make specific implementation for ForEach function.
* @see ForEach
* @param id Template parameter, unique key for implementations of this struct.
* @param graph Template parameter
* @param vertex Template parameter
* @returns Implementation-defined.
*/
template<int id, class graph, typename vertex>
struct ProcessVertex;
/** \example vertex_stream_example.cpp
* An example of how to use ForEach and ProcessVertex.
*/
