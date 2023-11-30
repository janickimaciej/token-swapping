#include "token_swapping/reverse/algs/reverse_pairs_sort.hpp"

#include "token_swapping/reverse/criteria/reverse_pairs.hpp"

#include <utility>
#include <vector>

namespace TokenSwapping
{
	std::vector<std::pair<int,int>> ReversePairsSort::getSolution(Instance instance)
	{
		std::vector<std::pair<int, int>> solution;
		while (!instance.isSolved())
		{
			bool swapped = false;
			for (int i = 0; i < instance.size() - 2; ++i)
			{
				if (ReversePairs::changeInCount(instance, std::make_pair(i, i + 2)) == -3)
				{
					instance.swap(i, i + 2);
					solution.push_back(std::make_pair(i, i + 2));
					swapped = true;
					break;
				}
			}
			if (swapped)
			{
				continue;
			}
			for (int i = 0; i < instance.size() - 1; ++i)
			{
				if (instance[i] > instance[i + 1])
				{
					instance.swap(i, i + 1);
					solution.push_back(std::make_pair(i, i + 1));
					break;
				}
			}
		}
		return solution;
	}
};
