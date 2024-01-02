#pragma once

#include "token_swapping/instance.hpp"
#include "token_swapping/reverse/criteria/criterion.hpp"

#include <utility>

namespace TokenSwapping
{
	class IndependentReverseTriplets : public Criterion
	{
	public:
		virtual int score(Instance instance, const std::pair<int, int>& move) const override;
		virtual bool isPositive() const override;
		virtual ~IndependentReverseTriplets() = default;
	};
};
