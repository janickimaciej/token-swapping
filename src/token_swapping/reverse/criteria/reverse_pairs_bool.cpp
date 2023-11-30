#include "token_swapping/reverse/criteria/reverse_pairs_bool.hpp"

#include "token_swapping/reverse/criteria/reverse_pairs.hpp"

#include <algorithm>
#include <utility>

namespace TokenSwapping
{
	int ReversePairsBool::score(Instance instance, const std::pair<int, int>& move) const
	{
		return ReversePairs::changeInDistance(instance, move) < 0 ? -1 : 1;
	}

	bool ReversePairsBool::isPositive() const
	{
		return false;
	}
};
