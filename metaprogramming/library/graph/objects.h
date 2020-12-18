#pragma once

/**
 * Represents class holders of different objects
*/
namespace Objects {
	template<int integer>
	struct Integer {
		constexpr static int value = integer;
	};

	template<bool boolean>
	struct Boolean {
		constexpr static bool value = boolean;
	};
}