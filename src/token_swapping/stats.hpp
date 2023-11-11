#pragma once

#include "token_swapping/instance.hpp"

#include <vector>

namespace TokenSwapping
{
	class Stats
	{
	public:
		static int permutation2Index(const Instance& instance);
		template <typename Function>
		static void iteratePermutations(int power, int size, Function& function);

	private:
		static int getPositionIndex(const std::vector<bool>& used, int element);
		static int getNext(const std::vector<bool>& used, int previous);
	};

	template <typename Function>
	void Stats::iteratePermutations(int power, int size, Function& function)
	{
		std::vector<int> stack;
		std::vector<bool> used(size, false);
		int previous = -1;
		while (true)
		{
			if (stack.size() == size)
			{
				function(TokenSwapping::Instance{power, stack});
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
