#include "token_swapping/reverse/criteria/reverse_triplets.hpp"

#include <utility>

namespace TokenSwapping
{
	int ReverseTriplets::score(Instance instance, const std::pair<int, int>& move) const
	{
		instance.swap(move);
		int count = 0;
		for (int i = 0; i < instance.size() - 2; ++i)
		{
			for (int j = i + 1; j < instance.size() - 1; ++j)
			{
				for (int k = j + 1; k < instance.size(); ++k)
				{
					if (instance[i] > instance[j] && instance[j] > instance[k])
					{
						++count;
					}
				}
			}
		}
		return count;
	}

	bool ReverseTriplets::isPositive() const
	{
		return true;
	}
};
