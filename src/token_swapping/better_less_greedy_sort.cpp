#include "token_swapping/better_less_greedy_sort.hpp"
#include "token_swapping/better_reverse_triples.hpp"
#include "token_swapping/pairs_metric.hpp"

#include <climits>
#include <utility>
#include <vector>

namespace TokenSwapping
{
	std::vector<std::pair<int, int>> BetterLessGreedySort::getSolution(Instance instance)
	{
		std::vector<std::pair<int, int>> solution;
		while (!instance.isSolved())
		{
			int maxChangeInReverseTriples = INT_MIN;
			std::pair<int, int> bestMove;
			for (int i = 0; i < instance.size() - 2; ++i)
			{
				checkBestMove(instance, std::make_pair(i, i + 2), -3, bestMove,
					maxChangeInReverseTriples);
			}
			if (maxChangeInReverseTriples != INT_MIN)
			{
				instance.swap(bestMove);
				solution.push_back(bestMove);
				continue;
			}
			for (int i = 0; i < instance.size() - 1; ++i)
			{
				checkBestMove(instance, std::make_pair(i, i + 1), -1, bestMove,
					maxChangeInReverseTriples);
			}
			for (int i = 0; i < instance.size() - 2; ++i)
			{
				checkBestMove(instance, std::make_pair(i, i + 2), -1, bestMove,
					maxChangeInReverseTriples);
			}
			instance.swap(bestMove);
			solution.push_back(bestMove);
		}
		return solution;
	}

	void BetterLessGreedySort::checkBestMove(const Instance& instance, const std::pair<int, int>& move,
		int changeInDistance, std::pair<int, int>& bestMove, int& maxChangeInReverseTriples)
	{
		if (PairsMetric::changeInDistance(instance, move) == changeInDistance)
		{
			int changeInReverseTriples = BetterReverseTriples::changeInCount(instance, move);
			if (changeInReverseTriples > maxChangeInReverseTriples)
			{
				bestMove = move;
				maxChangeInReverseTriples = changeInReverseTriples;
			}
		}
	}
};
