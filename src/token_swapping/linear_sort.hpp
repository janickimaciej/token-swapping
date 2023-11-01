#pragma once

#include "token_swapping/instance.hpp"

#include <utility>
#include <vector>

namespace TokenSwapping
{
	class LinearSort
	{
	public:
		LinearSort() = delete;

		static std::vector<std::pair<int, int>> sort(Instance instance);

		~LinearSort() = delete;
	};
};
