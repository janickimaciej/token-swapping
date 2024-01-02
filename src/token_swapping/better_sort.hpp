#pragma once

#include "token_swapping/instance.hpp"

#include <utility>
#include <vector>

namespace TokenSwapping
{
	class BetterSort
	{
	public:
		BetterSort() = delete;

		static std::vector<std::pair<int, int>> getSolution(Instance instance);

		~BetterSort() = delete;
	};
};
