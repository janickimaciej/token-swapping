#pragma once

#include "token_swapping/instance.hpp"
#include "token_swapping/reverse/algs/criteria_alg.hpp"
#include "token_swapping/reverse/criteria/criteria.hpp"
#include "token_swapping/reverse/criteria/criterion.hpp"
#include "token_swapping/reverse/criteria/reverse_pairs.hpp"
#include "token_swapping/reverse/criteria/reverse_triplets.hpp"

#include <memory>
#include <vector>

namespace TokenSwapping
{
	class ReverseTripletsSort
	{
	public:
		static inline std::vector<std::pair<int, int>> getSolution(Instance instance)
		{
			Criteria criteria;
			criteria.add<ReversePairs>();
			criteria.add<ReverseTriplets>();
			return CriteriaAlg::getSolution(instance, std::move(criteria));
		}
	};
};
