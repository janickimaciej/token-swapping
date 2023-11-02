#include "token_swapping/brute_force_sort.hpp"
#include "token_swapping/bubble_sort.hpp"
#include "token_swapping/instance.hpp"

#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

void bruteForceTest();

int main()
{
	bruteForceTest();
	return 0;
}

void bruteForceTest()
{
	TokenSwapping::Instance instance{2, std::vector<int>{6, 2, 5, 3, 1, 4, 0}};
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::vector<std::pair<int, int>>> solutions = TokenSwapping::BruteForceSort::sort(instance);
	auto stop = std::chrono::high_resolution_clock::now();

	auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << solutions.size() << " shortest " << (solutions.size() == 1 ? "solution" : "solutions") <<
		" found in " << durationMs.count() << " ms\n\n";

	int solutionIndex = 0;
	std::cout << "solutions[" << solutionIndex << "]:\n";
	for (const std::pair<int, int>& edge : solutions[0])
	{
		std::cout << edge.first << " <-> " << edge.second << '\n';
	}
}
