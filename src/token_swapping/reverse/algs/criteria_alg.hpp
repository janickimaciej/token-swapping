#pragma once

#include "token_swapping/instance.hpp"
#include "token_swapping/reverse/criteria/criteria.hpp"
#include "token_swapping/reverse/criteria/criterion.hpp"

#include <memory>
#include <utility>
#include <vector>

namespace TokenSwapping
{
	class CriteriaAlg
	{
	public:
		static std::vector<std::pair<int, int>> getSolution(Instance instance,
			const Criteria& criteria);

	private:
		static std::vector<std::pair<int, int>> getAllPossibleMoves(int instanceSize,
			int instancePower);
	};
};
