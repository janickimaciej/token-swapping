#include "token_swapping/reverse/criteria/generators.hpp"

#include "token_swapping/reverse/criteria/independent_reverse_triplets.hpp"

#include <algorithm>
#include <utility>

namespace TokenSwapping
{
	int Generators::score(Instance instance, const std::pair<int, int>& move) const
	{
		Instance instanceAfterMove = instance;
		instanceAfterMove.swap(move);
		IndependentReverseTriplets independentReverseTriplets{};
		int count = 0;
		for (int i = 0; i < instanceAfterMove.size() - 2; ++i)
		{
			for (int j = i + 1; j < instanceAfterMove.size() - 1; ++j)
			{
				for (int k = j + 1; k < instanceAfterMove.size(); ++k)
				{
					if (instanceAfterMove[i] < instanceAfterMove[j] &&
						instanceAfterMove[j] > instanceAfterMove[k] &&
						instanceAfterMove[k] < instanceAfterMove[i])
					{
						Instance unconstrainedInstance{instance.size() - 1, instance};
						int reverseTripletsBefore =
							independentReverseTriplets.score(unconstrainedInstance, move);
						unconstrainedInstance.swap(move);
						int reverseTripletsAfter =
							independentReverseTriplets.score(unconstrainedInstance, {i, k});
						if (reverseTripletsAfter > reverseTripletsBefore)
						{
							++count;
						}
					}
					if (instanceAfterMove[i] > instanceAfterMove[j] &&
						instanceAfterMove[j] < instanceAfterMove[k] &&
						instanceAfterMove[k] < instanceAfterMove[i])
					{
						Instance unconstrainedInstance{instance.size() - 1, instance};
						int reverseTripletsBefore =
							independentReverseTriplets.score(unconstrainedInstance, move);
						unconstrainedInstance.swap(move);
						int reverseTripletsAfter =
							independentReverseTriplets.score(unconstrainedInstance, {i, k});
						if (reverseTripletsAfter > reverseTripletsBefore)
						{
							++count;
						}
					}
				}
			}
		}
		return count;
	}

	bool Generators::isPositive() const
	{
		return true;
	}
};
