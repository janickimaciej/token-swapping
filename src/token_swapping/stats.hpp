#pragma once

#include "token_swapping/instance.hpp"

#include <vector>

namespace TokenSwapping
{
	int permutation2Index(const Instance& instance);
	int getPositionIndex(const std::vector<bool>& used, int element);
	int factorial(int n);

	template <typename Function>
	void iteratePermutations(int size, Function function);
	int getNext(const std::vector<bool>& used, int previous);

	template <typename Function>
	void iteratePermutations(int size, Function function)
	{
		std::vector<int> stack;
		std::vector<bool> used(size, false);
		int previous = -1;
		while (true)
		{
			if (stack.size() == size)
			{
				function(TokenSwapping::Instance{1, stack});
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
