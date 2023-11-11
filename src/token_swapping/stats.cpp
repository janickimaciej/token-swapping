#include "token_swapping/stats.hpp"

#include "token_swapping/instance.hpp"

#include <vector>

namespace TokenSwapping
{
	int permutation2Index(const Instance& instance)
	{
		int n = instance.size();
		std::vector<bool> used(n, false);
		int index = 0;
		for (int i = 0; i < n; ++i)
		{
			int element = instance[i];
			int positionIndex = getPositionIndex(used, element);
			index += positionIndex * factorial(n - i - 1);
			used[element] = true;
		}
		return index;
	}

	int getPositionIndex(const std::vector<bool>& used, int element)
	{
		int index = 0;
		for (int i = 0; i < element; ++i)
		{
			if (!used[i])
			{
				++index;
			}
		}
		return index;
	}

	int factorial(int n)
	{
		int factorial = 1;
		for (int i = 1; i <= n; ++i)
		{
			factorial *= i;
		}
		return factorial;
	}

	int getNext(const std::vector<bool>& used, int previous)
	{
		int i = previous + 1;
		for (; i < used.size(); ++i)
		{
			if (!used[i])
			{
				return i;
			}
		}
		return -1;
	}
};
