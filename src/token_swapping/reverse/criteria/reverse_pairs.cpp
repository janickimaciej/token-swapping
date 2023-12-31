#include "token_swapping/reverse/criteria/reverse_pairs.hpp"

#include <algorithm>
#include <utility>

namespace TokenSwapping
{
	int ReversePairs::score(Instance instance, const std::pair<int, int>& move) const
	{
		return changeInDistance(instance, move);
	}

	bool ReversePairs::isPositive() const
	{
		return false;
	}

	int ReversePairs::distance(const Instance& instance)
	{
		int distance = 0;
		for (int i = 0; i < instance.size() - 1; ++i)
		{
			for (int j = i + 1; j < instance.size(); ++j)
			{
				if (instance[i] > instance[j])
				{
					++distance;
				}
			}
		}
		return distance;
	}

	int ReversePairs::changeInDistance(const Instance& instance, const std::pair<int, int>& move)
	{
		int minIndex = std::min(move.first, move.second);
		int maxIndex = std::max(move.first, move.second);
		int change = 0;

		for (int i = minIndex + 1; i < maxIndex; ++i)
		{
			if (instance[minIndex] < instance[i])
			{
				++change;
			}
			else
			{
				--change;
			}

			if (instance[i] < instance[maxIndex])
			{
				++change;
			}
			else
			{
				--change;
			}
		}

		if (instance[minIndex] < instance[maxIndex])
		{
			++change;
		}
		else
		{
			--change;
		}

		return change;
	}
};
