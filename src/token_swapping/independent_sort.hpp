#pragma once

#include "token_swapping/instance.hpp"

#include <utility>
#include <vector>

namespace TokenSwapping
{
	class IndependentSort
	{
	public:
		IndependentSort() = delete;

		static std::vector<std::pair<int, int>> getSolution(Instance instance);

		~IndependentSort() = delete;

	private:
		static void checkBestMove(const Instance& instance, const std::pair<int, int>& move,
			int changeInDistance, std::pair<int, int>& bestMove, int& maxChangeInReverseTriples);
	};
};
