#pragma once

#include "token_swapping/instance.hpp"
#include "token_swapping/reverse/criteria/criterion.hpp"

#include <utility>

namespace TokenSwapping
{
	class ReversePairs : public Criterion
	{
	public:
		virtual int score(Instance instance, const std::pair<int, int>& move) const override;
		virtual bool isPositive() const override;
		static int changeInDistance(const Instance& instance, const std::pair<int, int>& move);
		static int distance(const Instance& instance);
		virtual ~ReversePairs() = default;
	};
};
