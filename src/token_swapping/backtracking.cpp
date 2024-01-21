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

	Node* Backtracking::calculateNextNode(Node* head, std::vector<Node*> minimalNodes) {
		
		Node* nextNode = NULL;
		std::vector<std::pair<Node*, int>> nodesWithPathLenghts;
		int minPathLength = INT_MAX;

		for (int i = 0;i < minimalNodes.size();i++) {
			Node* iterator = minimalNodes[i];
			int pathLength = 0;
			while (iterator->previous != head) {
				iterator = iterator->previous;
				pathLength++;
			}
			if (pathLength < minPathLength) {
				nextNode = minimalNodes[i];
				minPathLength = pathLength;
			}
		}

		return nextNode;
	}

	void Backtracking::appendSwaps(Node* head, Node* nextNode, Instance& instance, std::vector<std::pair<int,int>>& finalSolution) {
		Node* iterator = nextNode;
		std::vector<std::pair<int, int>> swaps;

		while (iterator != head) {
			swaps.push_back(iterator->swap);
			iterator = iterator->previous;
		}
		for (int i = swaps.size() - 1;i >= 0;i--) {
			instance.swap(swaps[i]);
			finalSolution.push_back(swaps[i]);
		}
	}

	std::vector<std::pair<int, int>> Backtracking::getSolution(Instance instance)
	{
		bool solutionFound = false;
		std::vector<std::pair<int, int>> solution;
		Node* head = new Node();
		head->distance = ReversePairs::distance(instance);
		Node* iterator = head;

		std::vector<std::pair<int, int>> finalSolution;
		while (ReversePairs::distance(instance) != 0) {
			int minDistance = INT_MAX;
			std::vector<Node*> minimalNodes;
			getSolutionRecursive(instance, solutionFound, minDistance, iterator, iterator, minimalNodes, solution, 3,
				iterator->swap);
			if (iterator->next.size() == 0)
				break;
			Node* nextNode = calculateNextNode(iterator, minimalNodes);
			appendSwaps(iterator, nextNode, instance, finalSolution);
			iterator = nextNode;
		}

		return finalSolution;
	}

	void Backtracking::getSolutionRecursive(Instance& instance, bool& solutionFound, int& minDistance, Node* head, Node* node, std::vector<Node*>& minimalNodes,
		std::vector<std::pair<int, int>>& solution, int maxDepth, std::pair<int, int> lastSwap)
	{

		if (minDistance == ReversePairs::distance(instance)) {
			minimalNodes.push_back(node);
		}
		else if (minDistance > ReversePairs::distance(instance) && ReversePairs::distance(instance) != head->distance) {
			minimalNodes.clear();
			minimalNodes.push_back(node);
			minDistance = ReversePairs::distance(instance);
		}

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
				newNode->previous = node;
				node->addNewNeighbour(newNode);
				getSolutionRecursive(instance, solutionFound, minDistance, head, newNode, minimalNodes, solution, maxDepth,
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
