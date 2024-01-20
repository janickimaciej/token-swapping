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
	Node::~Node() {
		delete[] next;
	}

	void Node::addNewNeighbour(Node node) {
		Node* oldNext = next;
		Node* newNext = new Node[++numNeighbours];

		for (int i = 0; i < numNeighbours - 1; ++i) {
			newNext[i] = oldNext[i];
		}
		newNext[numNeighbours - 1] = node;

		delete[] oldNext;
	}

	std::pair<std::pair<std::vector<std::pair<int, int>>, int>, Node> Backtracking::getSolution(Instance instance, int maxDepth)
	{
		bool solutionFound = false;
		int minDistance = INT_MAX;
		std::vector<std::pair<int, int>> solution;
		Node head;
		head.distance = ReversePairs::distance(instance);

		getSolutionRecursive(instance, solutionFound, minDistance, head, solution, maxDepth,
			std::make_pair(-1, -1));

		return std::make_pair(std::make_pair(solution, minDistance), head);
	}

	void Backtracking::getSolutionRecursive(Instance& instance, bool& solutionFound, int& minDistance, Node& node,
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
				Node newNode;
				newNode.swap = std::make_pair(j, j+i);
				newNode.distance = ReversePairs::distance(instance);
				node.addNewNeighbour(newNode);
				getSolutionRecursive(instance, solutionFound, minDistance, node, solution, maxDepth,
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
