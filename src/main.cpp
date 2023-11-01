#include "token_swapping/brute_force_sort.hpp"
#include "token_swapping/new_brute_force_sort.hpp"
#include "token_swapping/bubble_sort.hpp"
#include "token_swapping/instance.hpp"

#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

int main()
{
	TokenSwapping::Instance instance(2, std::vector<int>{1, 3, 0, 5, 4, 2});
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::vector<std::pair<int, int>>> solutions = TokenSwapping::BruteForceSort::sort(instance);
	auto stop = std::chrono::high_resolution_clock::now();

	auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << solutions.size() << " shortest solutions found in " << durationMs.count() << " ms\n\n";
	
	int solutionIndex = 0;
	std::cout << "solutions[" << solutionIndex << "]:\n";
	for (const std::pair<int, int>& edge : solutions[0])
	{
		std::cout << edge.first << " <-> " << edge.second << '\n';
	}
	return 0;
}
