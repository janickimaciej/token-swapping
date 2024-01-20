#include "token_swapping/backtracking.hpp"
#include "token_swapping/bubble_sort.hpp"
#include "token_swapping/utils.hpp"
#include "reverse/criteria/reverse_pairs.hpp"

namespace TokenSwapping
{
	std::pair<std::vector<std::pair<int, int>>, int> Backtracking::getSolution(Instance instance, int maxDepth)
	{
		bool solutionFound = false;
		int minDistance = INT_MAX;
		std::vector<std::pair<int, int>> solution;
		getSolutionRecursive(instance, solutionFound, minDistance, solution, maxDepth,
			std::make_pair(-1, -1));

		return std::make_pair(solution, minDistance);
	}

	void Backtracking::getSolutionRecursive(Instance& instance, bool& solutionFound, int& minDistance,
		std::vector<std::pair<int, int>>& solution, int maxDepth, std::pair<int, int> lastSwap)
	{

		if (instance.isSolved())
		{
			solutionFound = true;
			minDistance = 0;
			return;
		}
		if (solution.size() == maxDepth)
		{
			return;
		}
		minDistance = std::min(minDistance, ReversePairs::distance(instance));
		for (int i = 1; i <= instance.power(); ++i)
		{
			for (int j = 0; j < instance.size() - i; ++j)
			{
				if (j == lastSwap.first && j + i == lastSwap.second)
				{
					continue;
				}
				instance.swap(j, j + i);
				solution.push_back(std::make_pair(j, j + i));
				getSolutionRecursive(instance, solutionFound, minDistance, solution, maxDepth,
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
