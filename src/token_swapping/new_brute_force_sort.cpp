#include "token_swapping/new_brute_force_sort.hpp"

#include "token_swapping/bubble_sort.hpp"

namespace TokenSwapping
{
	std::vector<std::vector<std::pair<int, int>>> NewBruteForceSort::sort(Instance instance)
	{
		int maxDepth = BubbleSort::sort(instance).size();
		std::vector<std::vector<std::pair<int, int>>> solutions;
		std::vector<std::pair<int, int>> solution;
		std::vector<Instance> visitedInstances;
		visitedInstances.push_back(instance);

		recursiveSort(instance, solutions, solution, maxDepth, visitedInstances);

		return solutions;
	}

	void NewBruteForceSort::recursiveSort(Instance& instance,
		std::vector<std::vector<std::pair<int, int>>>& solutions,
		std::vector<std::pair<int, int>>& solution, int& maxDepth,
		std::vector<Instance> visitedInstances)
	{
		if (instance.isSolved())
		{
			if (solution.size() < maxDepth)
			{
				solutions.clear();
				maxDepth = solution.size();
			}
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
				instance.swap(j, j + i);
				
				bool isUnique = true;
				for (const Instance& visitedInstance : visitedInstances)
				{
					if (instance == visitedInstance)
					{
						isUnique = false;
						break;
					}
				}

				if (isUnique)
				{
					solution.push_back(std::make_pair(j, j + i));
					visitedInstances.push_back(instance);
					recursiveSort(instance, solutions, solution, maxDepth, visitedInstances);
					solution.pop_back();
					visitedInstances.pop_back();
				}

				instance.swap(j, j + i);
			}
		}
	}
};
