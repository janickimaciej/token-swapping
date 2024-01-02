#pragma once

#include "token_swapping/instance.hpp"
#include "token_swapping/reverse/criteria/criterion.hpp"

#include <utility>

namespace TokenSwapping
{
	class MaxIndependentReverseTriplets : public Criterion
	{
	public:
		virtual int score(Instance instance, const std::pair<int, int>& move) const override;
		virtual bool isPositive() const override;
		virtual ~MaxIndependentReverseTriplets() = default;

	private:
		static void allTriplets(const Instance& instance,
			std::vector<std::array<int, 3>>& allTriples);
		static void countRecursive(int& maximum, int solution,
			const std::vector<std::array<int, 3>>& available);
	};
};
