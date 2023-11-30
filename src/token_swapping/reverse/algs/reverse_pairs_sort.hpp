#pragma once

#include "token_swapping/instance.hpp"

#include <utility>
#include <vector>

namespace TokenSwapping
{
	class ReversePairsSort
	{
	public:
		ReversePairsSort() = delete;

		static std::vector<std::pair<int, int>> getSolution(Instance instance);

		~ReversePairsSort() = delete;
	};
};
