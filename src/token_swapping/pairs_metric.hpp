#pragma once

#include "token_swapping/instance.hpp"

#include <utility>

namespace TokenSwapping
{
	class PairsMetric
	{
	public:
		PairsMetric() = delete;

		static int distanceFromSolved(const Instance& instance);
		static int changeInDistance(const Instance& instance, const std::pair<int, int>& move);

		~PairsMetric() = delete;
	};
};
