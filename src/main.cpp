#include "token_swapping/alg_stats.hpp"
#include "token_swapping/brute_force_sort.hpp"
#include "token_swapping/bubble_sort.hpp"
#include "token_swapping/database.hpp"
#include "token_swapping/instance.hpp"
#include "token_swapping/reverse/algs/criteria_alg.hpp"
#include "token_swapping/reverse/algs/independent_reverse_triplets_sort.hpp"
#include "token_swapping/reverse/algs/max_independent_reverse_triplets_sort.hpp"
#include "token_swapping/reverse/algs/reverse_pairs_sort.hpp"
#include "token_swapping/reverse/algs/reverse_triplets_sort.hpp"
#include "token_swapping/reverse/criteria/independent_reverse_triplets.hpp"
#include "token_swapping/reverse/criteria/generators.hpp"
#include "token_swapping/reverse/criteria/max_independent_reverse_triplets.hpp"
#include "token_swapping/reverse/criteria/reverse_pairs_bool.hpp"
#include "token_swapping/reverse/criteria/reverse_pairs.hpp"
#include "token_swapping/reverse/criteria/reverse_triplets.hpp"
#include "token_swapping/stats.hpp"
#include "token_swapping/triplets/better_sort.hpp"
#include "token_swapping/utils.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

void runTest();
void printSolution(const TokenSwapping::Instance& instance,
	std::vector<std::pair<int, int>> solution);
void bruteForceTestOne(const TokenSwapping::Instance& instance);
void bruteForceTestAll(const TokenSwapping::Instance& instance);
void compareAlgs(const TokenSwapping::Instance& instance);
void mostSimilarOptimalSolution(const TokenSwapping::Instance& instance);
int solutionWithOnlyNegativeMovesCount(const TokenSwapping::Instance& instance,
	const std::vector<std::vector<std::pair<int, int>>>& solutions);

int main()
{
	//TokenSwapping::Instance instance{2, {2, 3, 5, 0, 4, 1}};
	//TokenSwapping::Database<9> database{2};
	//database.generate();
	runTest();
	return 0;
}

void runTest()
{
	constexpr int power = 2;
	constexpr int size = 7;
	
	TokenSwapping::Criteria criteria;
	criteria.add<TokenSwapping::ReversePairs>();
	criteria.add<TokenSwapping::IndependentReverseTriplets>();
	//criteria.add<TokenSwapping::MaxIndependentReverseTriplets>();
	//criteria.add<TokenSwapping::Generators>();
	//TokenSwapping::AlgStats<size> algStats{power, criteria};

	TokenSwapping::AlgStats<size> algStats{power, TokenSwapping::BetterSort::getSolution};

	algStats.runTest();
	std::cout << algStats.getFailedCount() << " / " << TokenSwapping::factorial(size) <<
		" failed\n";
	std::cout << algStats.getOptimalCount() << " / " << TokenSwapping::factorial(size) <<
		" are optimal\n";
	std::cout << algStats.getRatioAverage() <<
		" times worse than optimal on average on non-optimal solutions\n";
	std::cout << algStats.getWorstRatio() <<
		" times worse than optimal in the worst case\n";
}

void printSolution(const TokenSwapping::Instance& instance,
	std::vector<std::pair<int, int>> solution)
{
	std::cout << solution.size() << " moves" << '\n';
	TokenSwapping::Instance instanceCopy = instance;
#if 1
	for (const std::pair<int, int>& move : solution)
	{
		std::cout << move.first << " <-> " << move.second << " : " <<
			TokenSwapping::ReversePairs::changeInDistance(instanceCopy, move) << '\n';
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
	std::vector<std::pair<int, int>> solution =
		TokenSwapping::BruteForceSort::getSolution(instance);
	auto stop = std::chrono::high_resolution_clock::now();

	auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "shortest solution found in " << durationMs.count() << " ms\n\n";

	std::cout << "solution:\n";
	printSolution(instance, solution);
}

void bruteForceTestAll(const TokenSwapping::Instance& instance)
{
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::vector<std::pair<int, int>>> solutions =
		TokenSwapping::BruteForceSort::getAllSolutions(instance);
	auto stop = std::chrono::high_resolution_clock::now();

	auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << solutions.size() << " shortest " <<
		(solutions.size() == 1 ? "solution" : "solutions") << " of length " <<
		solutions[0].size() << " found in " << durationMs.count() << " ms\n";
	int count = solutionWithOnlyNegativeMovesCount(instance, solutions);
	std::cout << "of which " << count << " have only negative moves" << "\n\n";

	constexpr int maxDisplayed = 10;
	int displayed = solutions.size() < maxDisplayed ? solutions.size() : maxDisplayed;
	for (int i = 0; i < displayed; ++i)
	{
		std::cout << "solutions[" << i << "]:\n";
		printSolution(instance, solutions[i]);
		std::cout << '\n';
	}
}

void compareAlgs(const TokenSwapping::Instance& instance)
{
	std::cout << "Bubble sort:\n";
	printSolution(instance, TokenSwapping::BubbleSort::getSolution(instance));
	std::cout << '\n';

	std::cout << "ReversePairs:\n";
	printSolution(instance, TokenSwapping::ReversePairsSort::getSolution(instance));
	std::cout << '\n';

	std::cout << "ReversePairs + ReverseTriplets:\n";
	printSolution(instance, TokenSwapping::ReverseTripletsSort::getSolution(instance));
	std::cout << '\n';
	
	std::cout << "ReversePairs + IndependentReverseTriplets:\n";
	printSolution(instance, TokenSwapping::IndependentReverseTripletsSort::getSolution(instance));
	std::cout << '\n';
	
	std::cout << "ReversePairs + MaxIndependentReverseTriplets:\n";
	printSolution(instance, TokenSwapping::MaxIndependentReverseTripletsSort::getSolution(instance));
	std::cout << '\n';

	std::cout << "Better sort:\n";
	printSolution(instance, TokenSwapping::BetterSort::getSolution(instance));
	std::cout << '\n';

	std::cout << "Brute force sort:\n";
	printSolution(instance, TokenSwapping::BruteForceSort::getSolution(instance));
	std::cout << '\n';

	std::cout << "Experimental:\n";
	TokenSwapping::Criteria criteria;
	criteria.add<TokenSwapping::ReversePairs>();
	criteria.add<TokenSwapping::MaxIndependentReverseTriplets>();
	criteria.add<TokenSwapping::Generators>();
	printSolution(instance, TokenSwapping::CriteriaAlg::getSolution(instance, criteria));
}

void mostSimilarOptimalSolution(const TokenSwapping::Instance& instance)
{
	std::vector<std::vector<std::pair<int, int>>> optimalSolutions =
		TokenSwapping::BruteForceSort::getAllSolutions(instance);
	
	std::vector<std::pair<int, int>> solution =
		TokenSwapping::MaxIndependentReverseTripletsSort::getSolution(instance);
	
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
		TokenSwapping::ReversePairs reversePairs;
		for (auto& move : solution)
		{
			if (reversePairs.score(instanceCopy, move) >= 0)
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
