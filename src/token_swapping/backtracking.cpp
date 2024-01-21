#include "token_swapping/backtracking.hpp"
#include "token_swapping/bubble_sort.hpp"
#include "token_swapping/utils.hpp"
#include "reverse/criteria/reverse_pairs.hpp"

namespace TokenSwapping
{
	Node::Node() {
		numNeighbours = 0;
		swap = std::make_pair(-1, -1);
	}

	void Node::addNewNeighbour(Node* node) {
		next.push_back(node);
	}

	std::vector<std::pair<int, int>> Backtracking::getSolution(Instance instance)
	{
		bool solutionFound = false;
		int minDistance = INT_MAX;
		std::vector<std::pair<int, int>> solution;
		Node* head = new Node();
		head->distance = ReversePairs::distance(instance);
		Node* iterator = head;

		std::vector<std::pair<int, int>> finalSolution;
		while (ReversePairs::distance(instance) != 0) {
			getSolutionRecursive(instance, solutionFound, minDistance, iterator, solution, 3,
				std::make_pair(-1, -1));
			int minDist = INT_MAX;
			if (iterator->next.size() == 0)
				break;
			Node* nextNode = iterator->next[0];
			for (int i = 0; i < iterator->next.size();i++)
			{
				if (minDist > iterator->next[i]->distance) {
					minDist = iterator->next[i]->distance;
					nextNode = iterator->next[i];
				}
			}
			instance.swap(nextNode->swap);
			finalSolution.push_back(nextNode->swap);
			iterator = nextNode;
		}

		return finalSolution;
	}

	void Backtracking::getSolutionRecursive(Instance& instance, bool& solutionFound, int& minDistance, Node* node,
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
				Node* newNode = new Node();
				newNode->swap = std::make_pair(j, j+i);
				newNode->distance = ReversePairs::distance(instance);
				node->addNewNeighbour(newNode);
				getSolutionRecursive(instance, solutionFound, minDistance, newNode, solution, maxDepth,
					std::make_pair(j, j + i));
				//if (solutionFound)
				//{
				//	return;
				//}
				instance.swap(j, j + i);
				solution.pop_back();
			}
		}
	}
};
