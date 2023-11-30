#pragma once

#include "token_swapping/instance.hpp"

#include <utility>

namespace TokenSwapping
{
	class ReversePairs
	{
	public:
		ReversePairs() = delete;

		static int distanceFromSolved(const Instance& instance);
		static int changeInCount(const Instance& instance, const std::pair<int, int>& move);

		~ReversePairs() = delete;
	};
};
