#include "token_swapping/bubble_sort.hpp"

#include <utility>
#include <vector>

namespace TokenSwapping
{
	std::vector<std::pair<int, int>> BubbleSort::sort(Instance instance)
	{
		std::vector<std::pair<int, int>> solution;
		for (int i = 1; i < instance.size(); i++)
		{
			bool swapped = false;
			for (int j = 0; j < instance.size() - i; j++)
			{
				if (instance[j] > instance[j + 1])
				{
					instance.swap(j, j + 1);
					solution.push_back(std::pair<int, int>{j, j + 1});
					swapped = true;
				}
			}
			if (!swapped)
			{
				break;
			}
		}
		return solution;
	}
};
