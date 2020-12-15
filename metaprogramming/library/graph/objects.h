#pragma once

template<int integer>
struct Integer {
	constexpr static int value = integer;
};

template<bool boolean>
struct Boolean {
	constexpr static bool value = boolean;
};
