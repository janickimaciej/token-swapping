#pragma once

#include "token_swapping/database_tree.hpp"
#include "token_swapping/instance.hpp"

#include <utility>
#include <vector>
#include <iostream>

namespace TokenSwapping
{
	class BruteForceSort
	{
	public:
		BruteForceSort() = delete;

		static std::vector<std::pair<int, int>> getSolution(Instance instance);
		template <int size>
		static int getSolution(Instance instance, DatabaseTree<size>& database);
		static std::vector<std::vector<std::pair<int, int>>> getAllSolutions(Instance instance);

		~BruteForceSort() = delete;

	private:
		static void getSolutionRecursive(Instance& instance, bool& solutionFound,
			std::vector<std::pair<int, int>>& solution, int maxDepth, std::pair<int, int> lastSwap);
		template <int size>
		static int getSolutionRecursive(Instance& instance, bool& solutionFound,
			std::vector<std::pair<int, int>>& solution, int maxDepth, std::pair<int, int> lastSwap,
			DatabaseTree<size>& database);
		static void getAllSolutionsRecursive(Instance& instance,
			std::vector<std::vector<std::pair<int, int>>>& solutions,
			std::vector<std::pair<int, int>>& solution, int maxDepth,
			std::pair<int, int> lastSwap);
	};

	
	template <int size>
	int BruteForceSort::getSolution(Instance instance, DatabaseTree<size>& database)
	{
		bool solutionFound = false;
		std::vector<std::pair<int, int>> solution;

		int solutionFromDatabase = database.read(instance);
		if (solutionFromDatabase != -1)
		{
			return solutionFromDatabase;
		}

		for (int maxDepth = 0; !solutionFound; ++maxDepth)
		{
			getSolutionRecursive<size>(instance, solutionFound, solution, maxDepth,
				std::make_pair(-1, -1), database);
		}
		return solution.size();
	}

	template <int size>
	int BruteForceSort::getSolutionRecursive(Instance& instance, bool& solutionFound,
		std::vector<std::pair<int, int>>& solution, int maxDepth, std::pair<int, int> lastSwap,
		DatabaseTree<size>& database)
	{
		if (instance.isSolved())
		{
			solutionFound = true;
			return solution.size();
		}
		if (solution.size() == maxDepth)
		{
			return -1;
		}
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
				int solutionSize = database.read(instance);
				if (solutionSize != -1 && solution.size() + solutionSize == maxDepth)
				{
					solutionFound = true;
					return solutionSize + 1;
				}
				solutionSize = getSolutionRecursive(instance, solutionFound, solution, maxDepth,
					std::make_pair(j, j + i), database);
				if (solutionFound)
				{
					database.write(instance, solutionSize);
					return solutionSize + 1;
				}
				instance.swap(j, j + i);
				solution.pop_back();
			}
		}
	}
};
