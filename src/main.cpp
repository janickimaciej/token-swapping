#include "token_swapping/better_sort.hpp"
#include "token_swapping/brute_force_sort.hpp"
#include "token_swapping/bubble_sort.hpp"
#include "token_swapping/greedy_sort.hpp"
#include "token_swapping/instance.hpp"
#include "token_swapping/pairs_metric.hpp"
#include "token_swapping/special_sort.hpp"

#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

void printSolution(std::vector<std::pair<int, int>> solution);
void bruteForceTestOne();
void bruteForceTestAll();
void compareAlgs();

int main()
{
	compareAlgs();
	return 0;
}

void printSolution(std::vector<std::pair<int, int>> solution)
{
	std::cout << solution.size() << " moves" << '\n';
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

void compareAlgs()
{
	TokenSwapping::Instance instance{2, std::vector<int>{6, 2, 5, 3, 7, 1, 4, 0}};

	printSolution(TokenSwapping::BubbleSort::getSolution(instance));
	std::cout << '\n';
	printSolution(TokenSwapping::SpecialSort::getSolution(instance));
	std::cout << '\n';
	printSolution(TokenSwapping::BetterSort::getSolution(instance));
	std::cout << '\n';
	printSolution(TokenSwapping::GreedySort::getSolution(instance));
	std::cout << '\n';
	printSolution(TokenSwapping::BruteForceSort::getSolution(instance));
	std::cout << '\n';
}
