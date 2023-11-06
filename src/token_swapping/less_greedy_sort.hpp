#pragma once

#include "token_swapping/instance.hpp"

#include <utility>
#include <vector>

namespace TokenSwapping
{
	class LessGreedySort
	{
	public:
		LessGreedySort() = delete;

		static std::vector<std::pair<int, int>> getSolution(Instance instance);

		~LessGreedySort() = delete;
	};
};
