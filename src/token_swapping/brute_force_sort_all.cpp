#include "token_swapping/brute_force_sort_all.hpp"

#include "token_swapping/bubble_sort.hpp"

namespace TokenSwapping
{
	std::vector<std::vector<std::pair<int, int>>> BruteForceSortAll::sort(Instance instance)
	{
		std::vector<std::vector<std::pair<int, int>>> solutions;
		std::vector<std::pair<int, int>> solution;

		for (int maxDepth = 0; solutions.size() == 0; ++maxDepth)
		{
			recursiveSort(instance, solutions, solution, maxDepth, std::make_pair(-1, -1));
		}

		return solutions;
	}

	void BruteForceSortAll::recursiveSort(Instance& instance,
		std::vector<std::vector<std::pair<int, int>>>& solutions,
		std::vector<std::pair<int, int>>& solution, int maxDepth,
		std::pair<int, int> lastSwap)
	{
		if (instance.isSolved())
		{
			solutions.push_back(solution);
			return;
		}
		if (solution.size() == maxDepth)
		{
			return;
		}
		for (int i = 1; i <= instance.power(); ++i)
		{
			for (int j = 0; j < instance.size() - instance.power(); ++j)
			{
				if (j == lastSwap.first && j + i == lastSwap.second)
				{
					continue;
				}
				instance.swap(j, j + i);
				solution.push_back(std::make_pair(j, j + i));
				recursiveSort(instance, solutions, solution, maxDepth,
					std::make_pair(j, j + i));
				instance.swap(j, j + i);
				solution.pop_back();
			}
		}
	}
};
