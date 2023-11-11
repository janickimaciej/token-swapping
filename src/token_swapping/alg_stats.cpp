#include "token_swapping/alg_stats.hpp"

#include "token_swapping/database.hpp"
#include "token_swapping/instance.hpp"
#include "token_swapping/stats.hpp"
#include "utils.hpp"

#include <functional>
#include <utility>
#include <vector>

namespace TokenSwapping
{
	AlgStats::AlgStats(int power, int size,
		std::function<std::vector<std::pair<int, int>>(Instance)> function) :
		m_power{power},
		m_size{size},
		m_function{function},
		m_database{power, size}
	{ }

	void AlgStats::runTest()
	{
		Stats::iteratePermutations(m_power, m_size, *this);
	}

	int AlgStats::getOptimalCount() const
	{
		return m_optimalCount;
	}

	double AlgStats::getRatioAverage() const
	{
		return m_ratioCumulative / m_nonZeroCount;
	}

	void AlgStats::operator()(const Instance& instance)
	{
		int optimalSolutionLength = m_database.optimalSolutionLength(instance);
		int solutionLength = m_function(instance).size();
		if (solutionLength == optimalSolutionLength)
		{
			++m_optimalCount;
		}
		if (optimalSolutionLength != 0)
		{
			m_ratioCumulative += (double)solutionLength / optimalSolutionLength;
			++m_nonZeroCount;
		}
	}
};
