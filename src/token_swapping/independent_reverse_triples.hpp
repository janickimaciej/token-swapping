#pragma once

#include "token_swapping/instance.hpp"

#include <utility>

namespace TokenSwapping
{
	class IndependentReverseTriples
	{
	public:
		IndependentReverseTriples() = delete;

		static int count(const Instance& instance);
		static void allTriples(const Instance& instance,
			std::vector<std::array<int, 3>>& allTriples);
		static void countRecursive(int& maximum, int solution,
			const std::vector<std::array<int, 3>>& available);
		static int changeInCount(Instance instance, const std::pair<int, int>& move);

		~IndependentReverseTriples() = delete;
	};
};
