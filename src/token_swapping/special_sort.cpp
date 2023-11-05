#include "token_swapping/special_sort.hpp"

#include <utility>
#include <vector>

namespace TokenSwapping
{
	std::vector<std::pair<int, int>> SpecialSort::getSolution(Instance instance)
	{
		std::vector<std::pair<int, int>> solution;
		for (int j = 0; j < instance.size(); j++) {
			for (int i = 1; i < instance.size() - 1; i++)
			{
				if (instance[i - 1] > i - 1 &&
					instance[i + 1] < i + 1 &&
					instance[i - 1] != i &&
					instance[i + 1] != i
					) {
					instance.swap(i - 1, i + 1);
					solution.push_back(std::pair<int, int>{i - 1, i + 1});
				}
				else if (instance[i - 1] == i) {
					instance.swap(i - 1, i);
					solution.push_back(std::pair<int, int>{i - 1, i});
				}
				else if (instance[i + 1] == i) {
					instance.swap(i, i + 1);
					solution.push_back(std::pair<int, int>{i, i + 1});
				}
			}
		}
		return solution;
	}
};
