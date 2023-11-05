#pragma once

#include "token_swapping/instance.hpp"

#include <utility>
#include <vector>

namespace TokenSwapping
{
	class GreedySort
	{
	public:
		GreedySort() = delete;

		static std::vector<std::pair<int, int>> getSolution(Instance instance);

		~GreedySort() = delete;
	};
};
