#pragma once

#include "token_swapping/instance.hpp"

#include <utility>

namespace TokenSwapping
{
	class MaxIndependentReverseTriplets
	{
	public:
		MaxIndependentReverseTriplets() = delete;

		static int count(const Instance& instance);
		static void allTriplets(const Instance& instance,
			std::vector<std::array<int, 3>>& allTriples);
		static void countRecursive(int& maximum, int solution,
			const std::vector<std::array<int, 3>>& available);
		static int changeInCount(Instance instance, const std::pair<int, int>& move);

		~MaxIndependentReverseTriplets() = delete;
	};
};
