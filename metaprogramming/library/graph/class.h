#pragma once

/**
* Represents wrapper of a class object.
* @param value_ Template parameter, value that should be wrapped
*/
template<typename value_>
struct Class {
	using value = value_;
};