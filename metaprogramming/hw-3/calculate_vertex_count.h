#pragma once

struct CalculateVertexCount {
	constexpr static size_t result = 0;

	template<typename vertex>
	constexpr static void execute() {
		++result;
	}
};