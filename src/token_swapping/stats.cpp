#include "token_swapping/stats.hpp"

#include "token_swapping/instance.hpp"
#include "token_swapping/utils.hpp"

#include <vector>

namespace TokenSwapping
{
	int Stats::getNext(const std::vector<bool>& used, int previous)
	{
		int i = previous + 1;
		for (; i < used.size(); ++i)
		{
			if (!used[i])
			{
				return i;
			}
		}
		return -1;
	}
};
