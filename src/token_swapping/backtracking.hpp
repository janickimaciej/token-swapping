#pragma once

#include "token_swapping/instance.hpp"
#include <utility>
#include <vector>
#include <iostream>

namespace TokenSwapping
{
	class Node
	{
	public:
		Node() = delete;
		~Node() = delete;
		int distance;
		Node** next;
		// TODO: Drzewo
	};

	class Backtracking
	{
	public:
		Backtracking() = delete;
		static std::pair<std::vector<std::pair<int, int>>, int> getSolution(Instance instance, int maxDepth);
		~Backtracking() = delete;
	private:
		static void getSolutionRecursive(Instance& instance, bool& solutionFound, int& minDistance,
			std::vector<std::pair<int, int>>& solution, int maxDepth, std::pair<int, int> lastSwap);
	};
	
};
