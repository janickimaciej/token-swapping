#pragma once

#include "token_swapping/instance.hpp"

#include <utility>
#include <vector>

namespace TokenSwapping
{
	class NewBruteForceSort
	{
	public:
		NewBruteForceSort() = delete;

		static std::vector<std::vector<std::pair<int, int>>> sort(Instance instance);

		~NewBruteForceSort() = delete;

	private:
		static void recursiveSort(Instance& instance,
			std::vector<std::vector<std::pair<int, int>>>& solutions,
			std::vector<std::pair<int, int>>& solution, int& maxDepth,
			std::vector<Instance> instances);
	};
};
