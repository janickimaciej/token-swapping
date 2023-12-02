#pragma once

#include "token_swapping/instance.hpp"
#include "token_swapping/utils.hpp"

#include <climits>
#include <vector>

namespace TokenSwapping
{
	class Stats
	{
	public:
		template <typename Function>
		static void iteratePermutations(int power, int size, Function& function, int from = 0,
			int to = INT_MAX);

	private:
		static int getNext(const std::vector<bool>& used, int previous);
	};

	template <typename Function>
	void Stats::iteratePermutations(int power, int size, Function& function, int from, int to)
	{
		std::vector<int> stack;
		std::vector<bool> used(size, false);
		int previous = -1;
		while (true)
		{
			if (stack.size() == size)
			{
				Instance instance{power, stack};
				instance.print();
				int permutationIndex = permutation2Index(instance);
				if (permutationIndex >= to)
				{
					return;
				}
				if (permutationIndex >= from)
				{
					function(instance);
				}
				previous = stack.back();
				stack.pop_back();
				used[previous] = false;
				continue;
			}
			int next = getNext(used, previous);
			if (next == -1)
			{
				if (stack.size() == 0)
				{
					return;
				}
				previous = stack.back();
				stack.pop_back();
				used[previous] = false;
				continue;
			}
			stack.push_back(next);
			used[next] = true;
			previous = -1;
		}
	}
};
