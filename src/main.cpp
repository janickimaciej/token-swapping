#include "token_swapping/better_less_greedy_sort.hpp"
#include "token_swapping/better_sort.hpp"
#include "token_swapping/brute_force_sort.hpp"
#include "token_swapping/bubble_sort.hpp"
#include "token_swapping/less_greedy_sort.hpp"
#include "token_swapping/greedy_sort.hpp"
#include "token_swapping/instance.hpp"
#include "token_swapping/pairs_metric.hpp"
#include "token_swapping/special_sort.hpp"
#include "token_swapping/stats.hpp"

#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

void printSolution(const TokenSwapping::Instance& instance, std::vector<std::pair<int, int>> solution);
void bruteForceTestOne(const TokenSwapping::Instance& instance);
void bruteForceTestAll(const TokenSwapping::Instance& instance);
void compareAlgs(const TokenSwapping::Instance& instance);
void mostSimilarOptimalSolution(const TokenSwapping::Instance& instance);
int solutionWithOnlyNegativeMovesCount(const TokenSwapping::Instance& instance,
	const std::vector<std::vector<std::pair<int, int>>>& solutions);

void printPermutation(const TokenSwapping::Instance& instance)
{
	for (int i = 0; i < instance.size(); ++i)
	{
		std::cout << instance[i] << " ";
	}
	std::cout << '\n';
}

int main()
{
	TokenSwapping::Instance instance{2, {2, 0, 1, 3}};
	//TokenSwapping::Instance instance{2, {6, 1, 4, 2, 3, 0, 5}};
	TokenSwapping::iteratePermutations(5, printPermutation);
	return 0;
}

void printSolution(const TokenSwapping::Instance& instance, std::vector<std::pair<int, int>> solution)
{
	std::cout << solution.size() << " moves" << '\n';
	TokenSwapping::Instance instanceCopy = instance;
#if 0
	for (const std::pair<int, int>& move : solution)
	{
		std::cout << move.first << " <-> " << move.second << " : " <<
			TokenSwapping::PairsMetric::changeInDistance(instanceCopy, move) << '\n';
		instanceCopy.swap(move);
	}
#endif
	if (instance.isSolution(solution))
	{
		std::cout << "SUCCESS\n";
	}
	else
	{
		std::cout << "FAILURE\n";
	}
}

void bruteForceTestOne(const TokenSwapping::Instance& instance)
{
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::pair<int, int>> solution = TokenSwapping::BruteForceSort::getSolution(instance);
	auto stop = std::chrono::high_resolution_clock::now();

	auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "shortest solution found in " << durationMs.count() << " ms\n\n";

	std::cout << "solution:\n";
	printSolution(instance, solution);
}

void bruteForceTestAll(const TokenSwapping::Instance& instance)
{
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::vector<std::pair<int, int>>> solutions = TokenSwapping::BruteForceSort::getAllSolutions(instance);
	auto stop = std::chrono::high_resolution_clock::now();

	auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << solutions.size() << " shortest " << (solutions.size() == 1 ? "solution" : "solutions") <<
		" of length " << solutions[0].size() << " found in " << durationMs.count() << " ms\n";
	int count = solutionWithOnlyNegativeMovesCount(instance, solutions);
	std::cout << "of which " << count << " have only negative moves" << "\n\n";

	for (int i = 0; i < 0; ++i)
	{
		std::cout << "solutions[" << i << "]:\n";
		printSolution(instance, solutions[i]);
		std::cout << '\n';
	}
}

void compareAlgs(const TokenSwapping::Instance& instance)
{
	std::cout << "Bubble sort:" <<'\n';
	printSolution(instance, TokenSwapping::BubbleSort::getSolution(instance));
	std::cout << '\n';

	std::cout << "Greedy sort:" <<'\n';
	printSolution(instance, TokenSwapping::GreedySort::getSolution(instance));
	std::cout << '\n';

	std::cout << "Less greedy sort:" <<'\n';
	printSolution(instance, TokenSwapping::LessGreedySort::getSolution(instance));
	std::cout << '\n';

	std::cout << "Better sort:" <<'\n';
	printSolution(instance, TokenSwapping::BetterSort::getSolution(instance));
	std::cout << '\n';

	std::cout << "Better less greedy sort:" <<'\n';
	printSolution(instance, TokenSwapping::BetterLessGreedySort::getSolution(instance));
	std::cout << '\n';

	std::cout << "Brute force sort:" <<'\n';
	printSolution(instance, TokenSwapping::BruteForceSort::getSolution(instance));
	std::cout << '\n';
}

void mostSimilarOptimalSolution(const TokenSwapping::Instance& instance)
{
	std::vector<std::vector<std::pair<int, int>>> optimalSolutions =
		TokenSwapping::BruteForceSort::getAllSolutions(instance);
	std::vector<std::pair<int, int>> solution =
		TokenSwapping::BetterLessGreedySort::getSolution(instance);
	
	std::vector<std::pair<int, int>> mostSimilar;
	int similarity = -1;
	for (auto& optimalSolution : optimalSolutions)
	{
		int i = 0;
		for (; i < optimalSolution.size(); ++i)
		{
			if (optimalSolution[i] != solution[i])
			{
				break;
			}
		}
		if (i > similarity)
		{
			mostSimilar = optimalSolution;
			similarity = i;
		}
	}
	printSolution(instance, mostSimilar);
}

int solutionWithOnlyNegativeMovesCount(const TokenSwapping::Instance& instance,
	const std::vector<std::vector<std::pair<int, int>>>& solutions)
{
	int count = 0;
	for (auto& solution : solutions)
	{
		bool onlyNegative = true;
		TokenSwapping::Instance instanceCopy = instance;
		for (auto& move : solution)
		{
			int change = TokenSwapping::PairsMetric::changeInDistance(instanceCopy, move);
			if (change >= 0)
			{
				onlyNegative = false;
				break;
			}
			instanceCopy.swap(move);
		}
		if (onlyNegative)
		{
			++count;
		}
	}
	return count;
}
