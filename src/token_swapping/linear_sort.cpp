#include "token_swapping/linear_sort.hpp"

#include <utility>
#include <vector>

namespace TokenSwapping
{
	std::vector<std::vector<int>> generatePermutations(std::vector<int>& arr, int startIndex) {
		std::vector<std::vector<int>> permutations;
		if (startIndex == arr.size() - 1) {
			std::vector<int> permutation;
			for (int num : arr) {
				permutation.push_back(num);
			}
			permutations.push_back(permutation);
		}
		else {
			for (int i = startIndex; i < arr.size(); ++i) {
				std::swap(arr[startIndex], arr[i]);
				generatePermutations(arr, startIndex + 1);
				std::swap(arr[startIndex], arr[i]);
			}
		}

		return permutations;
	}

	std::vector<std::pair<int, int>> LinearSort::sort(Instance instance)
	{
		std::vector<std::pair<int, int>> solution;
		for (int i = 1; i < instance.size()-1; ++i)
		{
			if (i-1 == instance[i-1] && 
				i == instance[i] && 
				i+1 == instance[i+1]) {
				i+=2;
				continue;
			}

			int score = 0;
			std::vector<int> a = { instance[i-1], instance[i], instance[i+1] };
			std::vector<std::vector<int>> permutations = generatePermutations(a, 0);
			std::vector<int> best_permutation;

			for (std::vector<int> permutation : permutations) {
				int new_score = 0;
				for (int j = 0;j < permutation.size();j++) {
					new_score += (instance[i] - i) - (permutation[i] - i);
				}
				if (new_score > score) {
					best_permutation = permutation;
					score = new_score;
				}
			}
			
			std::vector<int> not_matching_tokens;
			for (int j = 0;j < best_permutation.size();j++) {
				if (instance[i + j - 1] != best_permutation[j]) {
					not_matching_tokens.push_back(i + j - 1);
				}
			}

			for (int j = 0;j < not_matching_tokens.size() - 1;j++) {
				instance.swap(not_matching_tokens[j], not_matching_tokens[j + 1]);
				solution.push_back(std::make_pair(not_matching_tokens[j], not_matching_tokens[j + 1]));
			}
		}

		return solution;
	}
};
