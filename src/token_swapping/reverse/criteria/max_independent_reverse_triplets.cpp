#include "token_swapping/reverse/criteria/max_independent_reverse_triplets.hpp"

#include <array>
#include <utility>
#include <vector>

namespace TokenSwapping
{
	int MaxIndependentReverseTriplets::count(const Instance& instance)
	{
		int maximum = -1;
		int solution = 0;
		std::vector<std::array<int, 3>> available;
		allTriplets(instance, available);
		countRecursive(maximum, solution, available);
		return maximum;
	}

	void MaxIndependentReverseTriplets::allTriplets(const Instance& instance,
		std::vector<std::array<int, 3>>& allTriplets)
	{
		for (int i = 0; i < instance.size() - 2; ++i)
		{
			for (int j = i + 1; j < instance.size() - 1; ++j)
			{
				for (int k = j + 1; k < instance.size(); ++k)
				{
					if (instance[i] > instance[j] && instance[j] > instance[k])
					{
						allTriplets.push_back(std::array<int, 3>{i, j, k});
					}
				}
			}
		}
	}

	void MaxIndependentReverseTriplets::countRecursive(int& maximum, int solution,
		const std::vector<std::array<int, 3>>& available)
	{
		if (available.size() == 0 && solution > maximum)
		{
				maximum = solution;
		}
		for (int i = 0; i < available.size(); ++i)
		{
			std::vector<std::array<int, 3>> newAvailable = available;
			for (int j = newAvailable.size() - 1; j >= 0; --j)
			{
				int similarity = 0;
				for (int k = 0; k < 3; ++k)
				{
					for (int l = 0; l < 3; ++l)
					{
						if (available[i][k] == newAvailable[j][l])
						{
							++similarity;
						}
					}
				}
				if (similarity >= 2)
				{
					newAvailable.erase(newAvailable.begin() + j);
				}
			}
			countRecursive(maximum, solution + 1, newAvailable);
		}
	}

	int MaxIndependentReverseTriplets::changeInCount(Instance instance,
		const std::pair<int, int>& move)
	{
		int countBefore = count(instance);
		instance.swap(move);
		int countAfter = count(instance);
		return countAfter - countBefore;
	}
};
