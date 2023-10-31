#include "token_swapping/brute_force_sort.hpp"

#include "token_swapping/bubble_sort.hpp"

namespace TokenSwapping
{
	std::vector<std::vector<std::pair<int, int>>> BruteForceSort::sort(Instance instance)
	{
		int depth = BubbleSort::sort(instance).size();
		std::vector<std::vector<std::pair<int, int>>> solutions;
		std::vector<std::pair<int, int>> solution;

		recursiveSort(instance, solutions, solution, depth, std::pair<int, int>(-1, -1));

		return solutions;
	}

	void BruteForceSort::recursiveSort(Instance& instance,
		std::vector<std::vector<std::pair<int, int>>>& solutions,
		std::vector<std::pair<int, int>>& solution, int& maxDepth,
		std::pair<int, int> lastSwap)
	{
		if (solution.size() == maxDepth)
		{
			if (instance.isSolved())
			{
				solutions.push_back(solution);
			}
			return;
		}
		if (instance.isSolved())
		{
			solutions.clear();
			solutions.push_back(solution);
			maxDepth == solution.size();
		}
		for (int i = 1; i <= instance.power(); ++i)
		{
			for (int j = 0; j < instance.size() - instance.power(); ++j)
			{
				if (j == lastSwap.first && j + i == lastSwap.second)
				instance.swap(j, j + i);
				solution.push_back(std::pair<int, int>{j, j + i});
				recursiveSort(instance, solutions, solution, maxDepth,
					std::pair<int, int>{j, j + i});
				instance.swap(j, j + i);
				solution.pop_back();
			}
		}
	}
};
