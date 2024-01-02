#include "token_swapping/reverse/criteria/independent_reverse_triplets.hpp"

#include <array>
#include <utility>
#include <vector>

namespace TokenSwapping
{
	int IndependentReverseTriplets::score(Instance instance, const std::pair<int, int>& move) const
	{
		instance.swap(move);
		std::vector<std::array<int, 3>> triplets;
		for (int i = 0; i < instance.size() - 2; ++i)
		{
			for (int j = i + 1; j < instance.size() - 1; ++j)
			{
				for (int k = j + 1; k < instance.size(); ++k)
				{
					if (instance[i] > instance[j] && instance[j] > instance[k])
					{
						bool exists = false;
						for (const std::array<int, 3>& triplet : triplets)
						{
							int similarity = 0;
							for (int l = 0; l < 3; l++)
							{
								if (triplet[l] == i || triplet[l] == j || triplet[l] == k)
								{
									++similarity;
								}
							}
							if (similarity == 2)
							{
								exists = true;
								break;
							}
						}
						if (!exists)
						{
							triplets.push_back(std::array<int, 3>{i, j, k});
						}
					}
				}
			}
		}
		return triplets.size();
	}

	bool IndependentReverseTriplets::isPositive() const
	{
		return true;
	}
};
