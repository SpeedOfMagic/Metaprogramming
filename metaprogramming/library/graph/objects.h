#pragma once

template<int integer>
struct Integer {
	constexpr int value = integer;
};

template<bool boolean>
struct Boolean {
	constexpr bool value = boolean;
};
