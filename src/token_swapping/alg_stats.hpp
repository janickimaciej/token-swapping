#pragma once

#include "token_swapping/database.hpp"
#include "token_swapping/instance.hpp"
#include "token_swapping/stats.hpp"
#include "token_swapping/reverse/algs/criteria_alg.hpp"
#include "token_swapping/reverse/criteria/criteria.hpp"
#include "token_swapping/utils.hpp"

#include <functional>
#include <utility>
#include <vector>

namespace TokenSwapping
{
	template <int size>
	class AlgStats
	{
	public:
		AlgStats(int power, std::function<std::vector<std::pair<int, int>>(Instance)> function);
		AlgStats(int power, const Criteria& criteria);
		void runTest();
		int getFailedCount() const;
		int getOptimalCount() const;
		double getRatioAverage() const;
		double getWorstRatio() const;
		void operator()(const Instance& instance);

	private:
		int m_power{};
		std::function<std::vector<std::pair<int, int>>(Instance)> m_function{};
		int m_failed = 0;
		int m_optimalCount = 0;
		double m_ratioCumulative = 0;
		int m_nonZeroCount = 0;
		double m_worstRatio = 1;
		Database<size> m_database;
	};

	template <int size>
	AlgStats<size>::AlgStats(int power,
		std::function<std::vector<std::pair<int, int>>(Instance)> function) :
		m_power{power},
		m_function{function},
		m_database{power}
	{ }

	template <int size>
	AlgStats<size>::AlgStats(int power, const Criteria& criteria) :
		m_power{power},
		m_function
		{
			[&criteria](Instance instance)
			{
				return CriteriaAlg::getSolution(instance, criteria);
			}
		},
		m_database{power}
	{ }

	template <int size>
	void AlgStats<size>::runTest()
	{
		Stats::iteratePermutations(m_power, size, *this);
	}

	template <int size>
	int AlgStats<size>::getFailedCount() const
	{
		return m_failed;
	}

	template <int size>
	int AlgStats<size>::getOptimalCount() const
	{
		return m_optimalCount;
	}

	template <int size>
	double AlgStats<size>::getRatioAverage() const
	{
		return m_nonZeroCount != 0 ? m_ratioCumulative / m_nonZeroCount : 1;
	}

	template <int size>
	double AlgStats<size>::getWorstRatio() const
	{
		return m_worstRatio;
	}

	template <int size>
	void AlgStats<size>::operator()(const Instance& instance)
	{
		int optimalSolutionLength = m_database.optimalSolutionLength(instance);
		std::vector<std::pair<int, int>> solution = m_function(instance);
		bool failed = !instance.isSolution(solution);
		if (failed)
		{
			++m_failed;
		}
		int solutionLength = solution.size();
		if (!failed && solutionLength == optimalSolutionLength)
		{
			++m_optimalCount;
		}
		//else // stop at first non-optimal
		//{
		//	solution.size();
		//}
		if (optimalSolutionLength != solutionLength)
		{
			double ratio = (double)solutionLength / optimalSolutionLength;
			m_ratioCumulative += ratio;
			++m_nonZeroCount;
			if (ratio > m_worstRatio)
			{
				m_worstRatio = ratio;
			}
		}
	}
};
