#pragma once

#include "token_swapping/instance.hpp"

#include <utility>
#include <vector>

namespace TokenSwapping
{
	class LessGreedySort
	{
	public:
		LessGreedySort() = delete;

		static std::vector<std::pair<int, int>> getSolution(Instance instance);

		~LessGreedySort() = delete;

	private:
		static void checkBestMove(const Instance& instance, const std::pair<int, int>& move,
			int changeInDistance, std::pair<int, int>& bestMove, int& maxChangeInReverseTriples);
	};
};
