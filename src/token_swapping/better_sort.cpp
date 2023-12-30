#include "token_swapping/better_sort.hpp"

#include <utility>
#include <vector>
#include <algorithm>

namespace TokenSwapping
{
	std::vector<std::pair<int, int>> BetterSort::getSolution(Instance instance)
	{
		std::vector<std::pair<int, int>> solution;
		if (instance.size() == 2) {
			instance.swap(0, 1);
			solution.push_back(std::pair<int, int>{0, 1});
			return solution;
		}
		bool makeOnlyTwoSwap = true;
		bool isSorted = false;
		while(true) {
			bool noneChanged = true;
			std::vector<std::pair<std::pair<int, int>, int>> swaps;
			for (int i = 1; i < instance.size() - 1; ++i)
			{
				if (instance[i - 1] <= instance[i] && instance[i] <= instance[i + 1]) {
					continue;
				}

				std::vector<int> permutation;
				std::vector<int> indexes;
				if (instance[i - 1] != i - 1) {
					permutation.push_back(instance[i - 1]);
					indexes.push_back(0);
				}
				if (instance[i] != i) {
					permutation.push_back(instance[i]);
					indexes.push_back(1);
				}
				if (instance[i + 1] != i + 1) {
					permutation.push_back(instance[i + 1]);
					indexes.push_back(2);
				}
				std::sort(permutation.begin(), permutation.end());

				int k = 0;
				std::vector<int> not_matching_tokens;
				for (int j : indexes) {
					if (permutation[k] != instance[i + j - 1]) {
						not_matching_tokens.push_back(i + j - 1);
					}
					k++;
				}

				if (not_matching_tokens.size() == 3) {
					if (instance[i - 1] > instance[i] && !makeOnlyTwoSwap) {
						swaps.push_back(std::pair<std::pair<int, int>, int>{
							std::pair<int, int>{i-1, i}, abs(i-1 - instance[i]) + abs(i - instance[i-1])});
					}
					if (instance[i - 1] > instance[i + 1]) {
						swaps.push_back(std::pair<std::pair<int, int>, int>{
							std::pair<int, int>{i - 1, i + 1}, abs(i - 1 - instance[i+1]) + abs(i+1 - instance[i - 1])});
					}
					if (instance[i] > instance[i + 1] && !makeOnlyTwoSwap) {
						swaps.push_back(std::pair<std::pair<int, int>, int>{
							std::pair<int, int>{i, i+1}, abs(i - instance[i+1]) + abs(i + 1 - instance[i])});
					}
				}
				else if (not_matching_tokens.size() == 2) {
					if (makeOnlyTwoSwap) {
						if (instance[not_matching_tokens[0]] > instance[not_matching_tokens[1]] && 
							abs(not_matching_tokens[0] - not_matching_tokens[1]) == 2) {
							swaps.push_back(std::pair<std::pair<int, int>, int>{
								std::pair<int, int>{not_matching_tokens[0], not_matching_tokens[1]},
									abs(not_matching_tokens[0] - instance[not_matching_tokens[1]]) + 
									abs(not_matching_tokens[1] - instance[not_matching_tokens[0]])});
						}
					}
					else {
						if (instance[not_matching_tokens[0]] > instance[not_matching_tokens[1]]) {
							swaps.push_back(std::pair<std::pair<int, int>, int>{
								std::pair<int, int>{not_matching_tokens[0], not_matching_tokens[1]},
									abs(not_matching_tokens[0] - instance[not_matching_tokens[1]]) +
									abs(not_matching_tokens[1] - instance[not_matching_tokens[0]])});
						}
					}
				}
			}
			if (swaps.size() > 0) {
				int min = INT_MAX;
				std::pair<int, int> swap_pair;
				for (int i = 0;i < swaps.size();i++) {
					if (swaps[i].second < min) {
						min = swaps[i].second;
						swap_pair = swaps[i].first;
					}
				}
				instance.swap(swap_pair.first, swap_pair.second);
				solution.push_back(swap_pair);
				noneChanged = false;
				if (abs(swap_pair.first - swap_pair.second) == 1)
					makeOnlyTwoSwap = true;
			}
			if (noneChanged && !makeOnlyTwoSwap)
				break;
			if(noneChanged)
				makeOnlyTwoSwap = false;
		}

		// Zamiana miejscami pozosta³ych niepasuj¹cych
		std::vector<int> not_on_place;
		for (int i = 0; i < instance.size();++i) {
			if (instance[i] != i) {
				not_on_place.push_back(instance[i]);
			}
		}

		if (not_on_place.size() == 0)
			return solution;

		std::vector<int> not_on_place_new = not_on_place;
		std::vector<int> temp = not_on_place;
		std::sort(temp.begin(), temp.end());

		for (int i = 0; i < not_on_place.size();++i) {
			for (int j = 0;j < not_on_place.size();++j) {
				if (not_on_place[i] == temp[j]) {
					not_on_place_new[i] = j;
					break;
				}
			}
		}

		Instance newInstance(not_on_place_new.size() > 2 ? 2 : 1, not_on_place_new);
		std::vector<std::pair<int, int>> swaps = getSolution(newInstance);
		for (std::pair<int, int> swap : swaps) {
			int idx1 = not_on_place[swap.first];
			int idx2 = not_on_place[swap.second];
			if (idx2 < idx1) {
				int temp = idx1;
				idx1 = idx2;
				idx2 = temp;
			}

			int distance = idx2 - idx1;
			int steps = distance / 2;
			int t = idx1;
			while (steps > 0) {
				instance.swap(t, t + 2);
				solution.push_back(std::pair<int, int>{t, t + 2});
				t = t + 2;
				steps--;
			}
			if (distance % 2 == 1) {
				instance.swap(t, t + 1);
				solution.push_back(std::pair<int, int>{t, t + 1});
				steps = distance / 2;
				while (steps > 0) {
					instance.swap(t - 2, t);
					solution.push_back(std::pair<int, int>{t - 2, t});
					t = t - 2;
					steps--;
				}
			}
			else {
				steps = distance / 2 - 1;
				t = t - 2;
				while (steps > 0) {
					instance.swap(t - 2, t);
					solution.push_back(std::pair<int, int>{t - 2, t});
					t = t - 2;
					steps--;
				}
			}
		}

		return solution;
	}
};
