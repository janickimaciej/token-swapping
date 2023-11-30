#pragma once

#include "token_swapping/instance.hpp"

#include <utility>

namespace TokenSwapping
{
	class ReverseTriplets
	{
	public:
		ReverseTriplets() = delete;

		static int count(const Instance& instance);
		static int changeInCount(Instance instance, const std::pair<int, int>& move);

		~ReverseTriplets() = delete;
	};
};
