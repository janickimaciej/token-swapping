#pragma once

#include "token_swapping/instance.hpp"

#include <utility>
#include <vector>

namespace TokenSwapping
{
	class BruteForceSort
	{
	public:
		BruteForceSort() = delete;

		static std::vector<std::pair<int, int>> getSolution(Instance instance);
		static std::vector<std::vector<std::pair<int, int>>> getAllSolutions(Instance instance);

		~BruteForceSort() = delete;

	private:
		static void getSolutionRecursive(Instance& instance, bool& solutionFound,
			std::vector<std::pair<int, int>>& solution, int maxDepth,
			std::pair<int, int> lastSwap);
		static void getAllSolutionsRecursive(Instance& instance,
			std::vector<std::vector<std::pair<int, int>>>& solutions,
			std::vector<std::pair<int, int>>& solution, int maxDepth,
			std::pair<int, int> lastSwap);
	};
};
