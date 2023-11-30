#include "token_swapping/reverse/algs/independent_reverse_triplets_sort.hpp"

#include "token_swapping/reverse/criteria/independent_reverse_triplets.hpp"
#include "token_swapping/reverse/criteria/reverse_pairs.hpp"

#include <climits>
#include <utility>
#include <vector>

namespace TokenSwapping
{
	std::vector<std::pair<int, int>> IndependentReverseTripletsSort::getSolution(Instance instance)
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

	void IndependentReverseTripletsSort::checkBestMove(const Instance& instance,
		const std::pair<int, int>& move, int changeInDistance, std::pair<int, int>& bestMove,
		int& maxChangeInReverseTriplets)
	{
		if (ReversePairs::changeInCount(instance, move) == changeInDistance)
		{
			int changeInReverseTriplets = IndependentReverseTriplets::changeInCount(instance, move);
			if (changeInReverseTriplets > maxChangeInReverseTriplets)
			{
				bestMove = move;
				maxChangeInReverseTriplets = changeInReverseTriplets;
			}
		}
	}
};
