#include "token_swapping/bubble_sort.hpp"
#include "token_swapping/special_sort.hpp"
#include "token_swapping/instance.hpp"

#include <iostream>
#include <utility>
#include <vector>

int main()
{
	TokenSwapping::Instance instance(2, std::vector<int>{0, 4, 2, 3, 1});
	std::vector<std::pair<int, int>> solution = TokenSwapping::SpecialSort::sort(instance); // 4, 3, 2, 1, 0
	for (const std::pair<int, int>& edge : solution)
	{
		std::cout << edge.first << " <-> " << edge.second << std::endl;
	}

	return 0;
}
