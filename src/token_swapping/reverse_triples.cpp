#include "token_swapping/reverse_triples.hpp"

#include <utility>

namespace TokenSwapping
{
	int ReverseTriples::count(const Instance& instance)
	{
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

	int ReverseTriples::changeInCount(Instance instance, const std::pair<int, int>& move)
	{
		int countBefore = count(instance);
		instance.swap(move);
		int countAfter = count(instance);
		return countAfter - countBefore;
	}
};
