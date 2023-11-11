#pragma once

#include "token_swapping/database.hpp"
#include "token_swapping/instance.hpp"

#include <functional>
#include <utility>
#include <vector>

namespace TokenSwapping
{
	class AlgStats
	{
	public:
		AlgStats(int power, int size,
			std::function<std::vector<std::pair<int, int>>(Instance)> function);
		void runTest();
		int getOptimalCount() const;
		double getRatioAverage() const;
		void operator()(const Instance& instance);

	private:
		int m_power{};
		int m_size{};
		std::function<std::vector<std::pair<int, int>>(Instance)> m_function{};
		int m_optimalCount = 0;
		double m_ratioCumulative = 0;
		int m_nonZeroCount = 0;
		Database m_database;
	};
};
