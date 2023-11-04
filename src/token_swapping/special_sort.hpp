#pragma once

#include "token_swapping/instance.hpp"

#include <utility>
#include <vector>

namespace TokenSwapping
{
	class SpecialSort
	{
	public:
		SpecialSort() = delete;

		static std::vector<std::pair<int, int>> sort(Instance instance);

		~SpecialSort() = delete;
	};
};
