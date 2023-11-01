#include "token_swapping/better_sort.hpp"

#include <utility>
#include <vector>
#include <algorithm>

namespace TokenSwapping
{
	std::vector<std::pair<int, int>> BetterSort::sort(Instance instance)
	{
		std::vector<std::pair<int, int>> solution;
		for (int n = 0; n < instance.size();++n) {
			for (int i = 1; i < instance.size() - 1; ++i)
			{
				if (instance[i - 1] <= instance[i] && instance[i] <= instance[i + 1]) {
					continue;
				}

				std::vector<int> permutation;
				permutation.push_back(instance[i - 1]);
				permutation.push_back(instance[i]);
				permutation.push_back(instance[i + 1]);

				std::sort(permutation.begin(), permutation.end());

				std::vector<int> not_matching_tokens;
				for (int j = 0;j < permutation.size();j++) {
					if (permutation[j] != instance[i + j - 1]) {
						not_matching_tokens.push_back(i + j - 1);
					}
				}

				if (not_matching_tokens.size() == 3) {
					if (instance[i - 1] > instance[i]) {
						instance.swap(i - 1, i);
						solution.push_back(std::pair<int, int>{i-1, i});
					}
					if (instance[i - 1] > instance[i + 1]) {
						instance.swap(i - 1, i + 1);
						solution.push_back(std::pair<int, int>{i - 1, i+1});
					}
					if (instance[i] > instance[i + 1]) {
						instance.swap(i, i + 1);
						solution.push_back(std::pair<int, int>{i, i + 1});
					}
				}
				else if (not_matching_tokens.size() == 2) {
					instance.swap(not_matching_tokens[0], not_matching_tokens[1]);
					solution.push_back(std::pair<int, int>{not_matching_tokens[0], not_matching_tokens[1]});
				}
			}
			bool isSorted = true;
			for (int h = 0;h < instance.size() - 1;h++) {
				if (instance[h] > instance[h + 1])
					isSorted = false;
			}
			if (isSorted)
				break;
		}
		return solution;
	}
};
