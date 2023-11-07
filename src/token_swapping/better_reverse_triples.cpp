#include "token_swapping/better_reverse_triples.hpp"

#include <array>
#include <utility>
#include <vector>

namespace TokenSwapping
{
	int BetterReverseTriples::count(const Instance& instance)
	{
		std::vector<std::array<int, 3>> triples;
		for (int i = 0; i < instance.size() - 2; ++i)
		{
			for (int j = i + 1; j < instance.size() - 1; ++j)
			{
				for (int k = j + 1; k < instance.size(); ++k)
				{
					if (instance[i] > instance[j] && instance[j] > instance[k])
					{
						bool exists = false;
						for (const std::array<int, 3>& triple : triples)
						{
							int similarity = 0;
							for (int l = 0; l < 3; l++)
							{
								if (triple[l] == i || triple[l] == j || triple[l] == k)
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
							triples.push_back(std::array<int, 3>{i, j, k});
						}
					}
				}
			}
		}
		return triples.size();
	}

	int BetterReverseTriples::changeInCount(Instance instance, const std::pair<int, int>& move)
	{
		int countBefore = count(instance);
		instance.swap(move);
		int countAfter = count(instance);
		return countAfter - countBefore;
	}
};
