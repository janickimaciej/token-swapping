#include "token_swapping/better_sort.hpp"

#include <utility>
#include <vector>
#include <algorithm>

namespace TokenSwapping
{
	std::vector<std::pair<int, int>> BetterSort::getSolution(Instance instance)
	{
		std::vector<std::pair<int, int>> solution;
		for (int n = 0; n < instance.size();++n) {
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
					if (instance[not_matching_tokens[0]] > instance[not_matching_tokens[1]]) {
						instance.swap(not_matching_tokens[0], not_matching_tokens[1]);
						solution.push_back(std::pair<int, int>{not_matching_tokens[0], not_matching_tokens[1]});
					}
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

		// Zamiana miejscami pozosta³ych niepasuj¹cych
		std::vector<int> not_on_place;
		for (int i = 0; i < instance.size();++i) {
			if (instance[i] != i)
				not_on_place.push_back(i);
		}

		std::vector<std::pair<int, int>> not_on_place_pairs;
		for (int k= 0;k < not_on_place.size();k++) {
			for (int l = 0;l < not_on_place.size();l++) {
				if (k == l)
					continue;
				if (not_on_place[k] == instance[not_on_place[l]] && not_on_place[l] == instance[not_on_place[k]]) {
					not_on_place_pairs.push_back(std::pair<int, int>{not_on_place[k], not_on_place[l]});
				}

			}
		}

		for (int j = 0; j < not_on_place_pairs.size();j++) {
			int idx1 = not_on_place_pairs[j].first;
			int idx2 = not_on_place_pairs[j].second;

			if (idx1 == instance[idx2] && idx2 == instance[idx1]) {
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
		}

		return solution;
	}
};
