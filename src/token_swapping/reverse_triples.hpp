#pragma once

#include "token_swapping/instance.hpp"

#include <utility>

namespace TokenSwapping
{
	class ReverseTriples
	{
	public:
		ReverseTriples() = delete;

		static int count(const Instance& instance);
		static int changeInCount(Instance instance, const std::pair<int, int>& move);

		~ReverseTriples() = delete;
	};
};
