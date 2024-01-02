#pragma once

#include "token_swapping/instance.hpp"

#include <utility>

namespace TokenSwapping
{
	class Criterion
	{
	public:
		virtual int score(Instance instance, const std::pair<int, int>& move) const = 0;
		virtual bool isPositive() const = 0;
		virtual ~Criterion() = default;
	};
};
