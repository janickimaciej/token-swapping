#include "token_swapping/less_greedy_sort.hpp"
#include "token_swapping/pairs_metric.hpp"
#include "token_swapping/reverse_triples.hpp"

#include <climits>
#include <utility>
#include <vector>

namespace TokenSwapping
{
	std::vector<std::pair<int, int>> LessGreedySort::getSolution(Instance instance)
	{
		std::vector<std::pair<int, int>> solution;
		while (!instance.isSolved())
		{
			int maxChangeInReverseTriples = INT_MIN;
			std::pair<int, int> bestMove;
			for (int i = 0; i < instance.size() - 2; ++i)
			{
				if (PairsMetric::changeInDistance(instance, std::make_pair(i, i + 2)) == -3)
				{
					int changeInReverseTriples = ReverseTriples::changeInCount(instance,
						std::make_pair(i, i + 2));
					if (changeInReverseTriples > maxChangeInReverseTriples)
					{
						bestMove = std::make_pair(i, i + 2);
						maxChangeInReverseTriples = changeInReverseTriples;
					}
				}
			}
			if (maxChangeInReverseTriples != INT_MIN)
			{
				instance.swap(bestMove);
				solution.push_back(bestMove);
				continue;
			}
			for (int i = 0; i < instance.size() - 1; ++i)
			{
				if (instance[i] > instance[i + 1])
				{
					int changeInReverseTriples = ReverseTriples::changeInCount(instance,
						std::make_pair(i, i + 1));
					if (changeInReverseTriples > maxChangeInReverseTriples)
					{
						bestMove = std::make_pair(i, i + 1);
						maxChangeInReverseTriples = changeInReverseTriples;
					}
				}
			}
			instance.swap(bestMove);
			solution.push_back(bestMove);
		}
		return solution;
	}
};
