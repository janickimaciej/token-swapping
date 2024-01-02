#pragma once

#include "token_swapping/instance.hpp"
#include "token_swapping/reverse/algs/criteria_alg.hpp"
#include "token_swapping/reverse/criteria/criteria.hpp"
#include "token_swapping/reverse/criteria/criterion.hpp"
#include "token_swapping/reverse/criteria/max_independent_reverse_triplets.hpp"
#include "token_swapping/reverse/criteria/reverse_pairs.hpp"

#include <memory>
#include <vector>

namespace TokenSwapping
{
	class MaxIndependentReverseTripletsSort
	{
	public:
		static inline std::vector<std::pair<int, int>> getSolution(Instance instance)
		{
			Criteria criteria;
			criteria.add<ReversePairs>();
			criteria.add<MaxIndependentReverseTriplets>();
			return CriteriaAlg::getSolution(instance, std::move(criteria));
		}
	};
};
