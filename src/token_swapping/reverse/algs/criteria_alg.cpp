#include "token_swapping/reverse/algs/criteria_alg.hpp"

#include "token_swapping/instance.hpp"
#include "token_swapping/reverse/criteria/criteria.hpp"
#include "token_swapping/reverse/criteria/criterion.hpp"

#include <climits>
#include <memory>
#include <utility>
#include <vector>
#include <iostream>

namespace TokenSwapping
{
	std::vector<std::pair<int, int>> CriteriaAlg::getSolution(Instance instance,
		const Criteria& criteria)
	{
		std::vector<std::pair<int, int>> solution;
		std::vector<std::pair<int, int>> allPossibleMoves = getAllPossibleMoves(instance.size(),
			instance.power());
		while (!instance.isSolved())
		{
			std::vector<std::pair<int, int>> bestMoves = allPossibleMoves;
			for (const std::unique_ptr<Criterion>& criterion : criteria.getVector())
			{
				int bestScore = criterion->isPositive() ? INT_MIN : INT_MAX;
				std::vector<std::pair<int, int>> newBestMoves;
				for (const std::pair<int, int>& move : bestMoves)
				{
					int score = criterion->score(instance, move);
					if (score == bestScore)
					{
						newBestMoves.push_back(move);
					}
					if (criterion->isPositive() ? score > bestScore : score < bestScore)
					{
						bestScore = score;
						newBestMoves.clear();
						newBestMoves.push_back(move);
					}
				}
				bestMoves = newBestMoves;
			}
			instance.swap(bestMoves.at(0));
			solution.push_back(bestMoves.at(0));
		}
		return solution;
	}

	std::vector<std::pair<int, int>> CriteriaAlg::getAllPossibleMoves(int instanceSize,
		int instancePower)
	{
		std::vector<std::pair<int, int>> allPossibleMoves;
		for (int power = 1; power <= instancePower; ++power)
		{
			for (int token = 0; token < instanceSize - power; ++token)
			{
				allPossibleMoves.push_back(std::make_pair(token, token + power));
			}
		}
		return allPossibleMoves;
	}
};
