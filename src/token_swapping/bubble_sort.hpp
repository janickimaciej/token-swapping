#pragma once

#include "token_swapping/instance.hpp"

#include <utility>
#include <vector>

namespace TokenSwapping
{
	class BubbleSort
	{
	public:
		BubbleSort() = delete;

		static std::vector<std::pair<int, int>> getSolution(Instance instance);

		~BubbleSort() = delete;
	};
};
