#include "token_swapping/reverse/algs/reverse_triplets_sort.hpp"

#include "token_swapping/reverse/criteria/reverse_pairs.hpp"
#include "token_swapping/reverse/criteria/reverse_triplets.hpp"

#include <climits>
#include <utility>
#include <vector>

namespace TokenSwapping
{
	std::vector<std::pair<int, int>> ReverseTripletsSort::getSolution(Instance instance)
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

	void ReverseTripletsSort::checkBestMove(const Instance& instance, const std::pair<int, int>& move,
		int changeInCount, std::pair<int, int>& bestMove, int& maxChangeInReverseTriplets)
	{
		if (ReversePairs::changeInCount(instance, move) == changeInCount)
		{
			int changeInReverseTriples = ReverseTriplets::changeInCount(instance, move);
			if (changeInReverseTriples > maxChangeInReverseTriplets)
			{
				bestMove = move;
				maxChangeInReverseTriplets = changeInReverseTriples;
			}
		}
	}
};
