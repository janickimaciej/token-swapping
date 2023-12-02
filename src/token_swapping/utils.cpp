#include "token_swapping/utils.hpp"

namespace TokenSwapping
{
	static int getPositionIndex(const std::vector<bool>& used, int element);

	int factorial(int n)
	{
		int factorial = 1;
		for (int i = 1; i <= n; ++i)
		{
			factorial *= i;
		}
		return factorial;
	}

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

	static int getPositionIndex(const std::vector<bool>& used, int element)
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
};
