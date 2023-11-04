#include "token_swapping/brute_force_sort.hpp"
#include "token_swapping/bubble_sort.hpp"
#include "token_swapping/instance.hpp"

#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

void printSolution(std::vector<std::pair<int, int>> solution);
void bruteForceTestOne();
void bruteForceTestAll();

int main()
{
	bruteForceTestOne();
	return 0;
}

void printSolution(std::vector<std::pair<int, int>> solution)
{
	for (const std::pair<int, int>& edge : solution)
	{
		std::cout << edge.first << " <-> " << edge.second << '\n';
	}
}

void bruteForceTestOne()
{
	TokenSwapping::Instance instance{2, std::vector<int>{6, 2, 5, 3, 1, 4, 0}};
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::pair<int, int>> solution = TokenSwapping::BruteForceSort::getSolution(instance);
	auto stop = std::chrono::high_resolution_clock::now();

	auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "shortest solution found in " << durationMs.count() << " ms\n\n";

	std::cout << "solution:\n";
	printSolution(solution);
}

void bruteForceTestAll()
{
	TokenSwapping::Instance instance{2, std::vector<int>{6, 2, 5, 3, 1, 4, 0}};
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::vector<std::pair<int, int>>> solutions = TokenSwapping::BruteForceSort::getAllSolutions(instance);
	auto stop = std::chrono::high_resolution_clock::now();

	auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << solutions.size() << " shortest " << (solutions.size() == 1 ? "solution" : "solutions") <<
		" found in " << durationMs.count() << " ms\n\n";

	int solutionIndex = 0;
	std::cout << "solutions[" << solutionIndex << "]:\n";
	printSolution(solutions[0]);
}
