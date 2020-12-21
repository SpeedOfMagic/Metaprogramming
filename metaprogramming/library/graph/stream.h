#pragma once

#include <algorithm>
#include <vector>

/**
* Represents an analogue of std::ranges. Unlike std::ranges, this class is compatible with earlier standards.
* It was made specifically for indexes of vertexes, but it can be used for other purposes.
* If this is a stream of indexes of vertexes, then it's recommended to use functors in FunctorStreamType.
* @see FunctorStreamType
* @see java.util.stream.Stream
*/
template<typename T>
class Stream {
private:
	std::vector<T> stream_;

public:
	explicit Stream(std::vector<T> stream) : stream_(stream) {}

	/**
	* Performs passed action on every index in stream.
	* @param consumer Consumer, that takes object and performs an action.
	*/
	template<class Consumer>
	void ForEach(Consumer consumer) {
		for (T object : stream_) {
			consumer(object);
		}
	}

	/**
	* Removes elements from stream where predicate returns false.
	* @param predicate Predicate, that takes object and returns true or false.
	* @returns This stream, after modification.
	*/
	template<class Predicate>
	Stream& Filter(Predicate predicate) {
		stream_.resize(
			std::copy_if(stream_.begin(), stream_.end(), stream_.begin(), predicate) -
			stream_.begin()
		);
		return *this;
	}

	/**
	* Converts every object into another one.
	* @param function Function, that takes object and returns another object.
	* @returns New stream, after modification.
	*/
	template<class NewType, class Function>
	Stream<NewType> Map(Function function) {
		std::vector<NewType> new_vector(stream_.size());
		for (size_t i = 0; i < stream_.size(); ++i) {
			new_vector.push_back(function(stream_[i]));
		}
		return Stream<NewType>(new_vector);
	}

	/**
	* Adds up all objects by using specific BinaryOperation.
	* @param binary_operation BinaryOperation, that takes result and current object, and returns result.
	* @param default_value Starting result of binary_operation.
	* @returns Final result of binary_operation
	*/
	template<class NewType, class BinaryOperation>
	NewType Reduce(BinaryOperation binary_operation, NewType default_value) {
		for (T object : stream_) {
			default_value = binary_operation(default_value, object);
		}
		return default_value;
	}

	/**
	* Collects stream into a vector.
	* @returns Contents of a stream in a vector.
	*/
	std::vector<T> Collect() { return stream_; }
};