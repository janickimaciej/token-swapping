#include "token_swapping/reverse/algs/max_independent_reverse_triplets_sort.hpp"

#include "token_swapping/reverse/criteria/max_independent_reverse_triplets.hpp"
#include "token_swapping/reverse/criteria/reverse_pairs.hpp"

#include <climits>
#include <utility>
#include <vector>

namespace TokenSwapping
{
	std::vector<std::pair<int, int>> MaxIndependentReverseTripletsSort::getSolution(Instance instance)
	{
		std::vector<std::pair<int, int>> solution;
		while (!instance.isSolved())
		{
			int maxChangeInReverseTriplets = INT_MIN;
			std::pair<int, int> bestMove;
			for (int i = 0; i < instance.size() - 2; ++i)
			{
				checkBestMove(instance, std::make_pair(i, i + 2), -3, bestMove,
					maxChangeInReverseTriplets);
			}
			if (maxChangeInReverseTriplets != INT_MIN)
			{
				instance.swap(bestMove);
				solution.push_back(bestMove);
				continue;
			}
			for (int i = 0; i < instance.size() - 1; ++i)
			{
				checkBestMove(instance, std::make_pair(i, i + 1), -1, bestMove,
					maxChangeInReverseTriplets);
			}
			for (int i = 0; i < instance.size() - 2; ++i)
			{
				checkBestMove(instance, std::make_pair(i, i + 2), -1, bestMove,
					maxChangeInReverseTriplets);
			}
			instance.swap(bestMove);
			solution.push_back(bestMove);
		}
		return solution;
	}

	void MaxIndependentReverseTripletsSort::checkBestMove(const Instance& instance, const std::pair<int, int>& move,
		int changeInDistance, std::pair<int, int>& bestMove, int& maxChangeInReverseTriplets)
	{
		if (ReversePairs::changeInCount(instance, move) == changeInDistance)
		{
			int changeInReverseTriples =
				MaxIndependentReverseTriplets::changeInCount(instance, move);
			if (changeInReverseTriples > maxChangeInReverseTriplets)
			{
				bestMove = move;
				maxChangeInReverseTriplets = changeInReverseTriples;
			}
		}
	}
};
