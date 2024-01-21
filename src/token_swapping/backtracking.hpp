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
		Node* previous;

		void addNewNeighbour(Node* node);
	};

	class Backtracking
	{
	public:
		Backtracking() = delete;
		static std::vector<std::pair<int, int>> getSolution(Instance instance);
		~Backtracking() = delete;
	private:
		static void appendSwaps(Node* head, Node* nextNode, Instance& instance, std::vector<std::pair<int, int>>& finalSolution);
		static Node* calculateNextNode(Node* head, std::vector<Node*> minimalNodes);
		static void getSolutionRecursive(Instance& instance, bool& solutionFound, int& minDistance, Node* head, Node* node, std::vector<Node*>& minimalNodes,
			std::vector<std::pair<int, int>>& solution, int maxDepth, std::pair<int, int> lastSwap);
	};
	
};
