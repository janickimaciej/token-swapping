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
		Node();
		int distance;
		int numNeighbours;
		std::pair<int, int> swap;
		std::vector<Node*> next;

		void addNewNeighbour(Node* node);
	};

	class Backtracking
	{
	public:
		Backtracking() = delete;
		static std::vector<std::pair<int, int>> getSolution(Instance instance);
		~Backtracking() = delete;
	private:
		static void getSolutionRecursive(Instance& instance, bool& solutionFound, int& minDistance, Node* node,
			std::vector<std::pair<int, int>>& solution, int maxDepth, std::pair<int, int> lastSwap);
	};
	
};
