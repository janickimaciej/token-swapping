#include "token_swapping/brute_force_sort_one.hpp"

#include "token_swapping/bubble_sort.hpp"

namespace TokenSwapping
{
	std::vector<std::pair<int, int>> BruteForceSortOne::sort(Instance instance)
	{
		bool solutionFound = false;
		std::vector<std::pair<int, int>> solution;

		for (int maxDepth = 0; !solutionFound; ++maxDepth)
		{
			recursiveSort(instance, solutionFound, solution, maxDepth, std::make_pair(-1, -1));
		}

		return solution;
	}

	void BruteForceSortOne::recursiveSort(Instance& instance, bool& solutionFound,
		std::vector<std::pair<int, int>>& solution, int maxDepth,
		std::pair<int, int> lastSwap)
	{
		if (instance.isSolved())
		{
			solutionFound = true;
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
				recursiveSort(instance, solutionFound, solution, maxDepth,
					std::make_pair(j, j + i));
				if (solutionFound)
				{
					return;
				}
				instance.swap(j, j + i);
				solution.pop_back();
			}
		}
	}
};
