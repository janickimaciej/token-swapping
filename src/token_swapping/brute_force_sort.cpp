#include "token_swapping/brute_force_sort.hpp"

#include "token_swapping/bubble_sort.hpp"

namespace TokenSwapping
{
	std::vector<std::pair<int, int>> BruteForceSort::getSolution(Instance instance)
	{
		bool solutionFound = false;
		std::vector<std::pair<int, int>> solution;

		for (int maxDepth = 0; !solutionFound; ++maxDepth)
		{
			getSolutionRecursive(instance, solutionFound, solution, maxDepth, std::make_pair(-1, -1));
		}

		return solution;
	}

	std::vector<std::vector<std::pair<int, int>>> BruteForceSort::getAllSolutions(Instance instance)
	{
		std::vector<std::vector<std::pair<int, int>>> solutions;
		std::vector<std::pair<int, int>> solution;

		for (int maxDepth = 0; solutions.size() == 0; ++maxDepth)
		{
			getAllSolutionsRecursive(instance, solutions, solution, maxDepth, std::make_pair(-1, -1));
		}

		return solutions;
	}

	void BruteForceSort::getSolutionRecursive(Instance& instance, bool& solutionFound,
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
				getSolutionRecursive(instance, solutionFound, solution, maxDepth,
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

	void BruteForceSort::getAllSolutionsRecursive(Instance& instance,
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
				getAllSolutionsRecursive(instance, solutions, solution, maxDepth,
					std::make_pair(j, j + i));
				instance.swap(j, j + i);
				solution.pop_back();
			}
		}
	}
};
